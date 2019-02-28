// Protocol Buffers - Google's data interchange format
// Copyright 2008 Google Inc.  All rights reserved.
// https://developers.google.com/protocol-buffers/
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef GOOGLE_PROTOBUF_PARSE_CONTEXT_H__
#define GOOGLE_PROTOBUF_PARSE_CONTEXT_H__

#include <cstring>
#include <string>

#include <google/protobuf/parse_context.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/implicit_weak_message.h>
#include <google/protobuf/port.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/stubs/strutil.h>

#include <google/protobuf/port_def.inc>


namespace google {
namespace protobuf {

class UnknownFieldSet;
class DescriptorPool;
class MessageFactory;

namespace internal {

// Template code below needs to know about the existence of these functions.
PROTOBUF_EXPORT void WriteVarint(uint32 num, uint64 val, std::string* s);
PROTOBUF_EXPORT void WriteLengthDelimited(uint32 num, StringPiece val,
                                          std::string* s);
// Inline because it is just forwarding to s->WriteVarint
inline void WriteVarint(uint32 num, uint64 val, UnknownFieldSet* s);
inline void WriteLengthDelimited(uint32 num, StringPiece val,
                                 UnknownFieldSet* s);


// The basic abstraction the parser is designed for is a slight modification
// of the ZeroCopyInputStream (ZCIS) abstraction. A ZCIS presents a serialized
// stream as a series of buffers that concatenate to the full stream.
// Pictorially a ZCIS presents a stream in chunks like so
// [---------------------------------------------------------------]
// [---------------------] chunk 1
//                      [----------------------------] chunk 2
//                                          chunk 3 [--------------]
//
// Where the '-' represent the bytes which are vertically lined up with the
// bytes of the stream. The proto parser requires its input to be presented
// similarily with the extra
// property that each chunk has kSlopBytes past its end that overlaps with the
// first kSlopBytes of the next chunk, or if there is no next chunk at least its
// still valid to read those bytes. Again, pictorially, we now have
//
// [---------------------------------------------------------------]
// [-------------------....] chunk 1
//                    [------------------------....] chunk 2
//                                    chunk 3 [------------------..**]
//                                                      chunk 4 [--****]
// Here '-' mean the bytes of the stream or chunk and '.' means bytes past the
// chunk that match up with the start of the next chunk. Above each chunk has
// 4 '.' after the chunk. In the case these 'overflow' bytes represents bytes
// past the stream, indicated by '*' above, their values are unspecified. It is
// still legal to read them (ie. should not segfault). Reading past the
// end should be detected by the user and indicated as an error.
//
// The reason for this, admittedly, unconventional invariant is to ruthlessly
// optimize the protobuf parser. Having an overlap helps in two important ways.
// Firstly it alleviates having to performing bounds checks if a piece of code
// is guaranteed to not read more than kSlopBytes. Secondly, and more
// importantly, the protobuf wireformat is such that reading a key/value pair is
// always less than 16 bytes. This removes the need to change to next buffer in
// the middle of reading primitive values. Hence there is no need to store and
// load the current position.

class PROTOBUF_EXPORT EpsCopyInputStream {
 public:
  enum { kSlopBytes = 16 };

  explicit EpsCopyInputStream(bool enable_aliasing)
      : aliasing_(enable_aliasing ? kOnPatch : kNoAliasing) {}

  void BackUp(const char* ptr) {
    GOOGLE_DCHECK(ptr <= buffer_end_ + kSlopBytes);
    int count;
    if (next_chunk_ == buffer_) {
      count = buffer_end_ + kSlopBytes - ptr;
    } else {
      count = size_ + (buffer_end_ - ptr);
    }
    if (count > 0) zcis_->BackUp(count);
  }

  // If return value is negative it's an error
  PROTOBUF_MUST_USE_RESULT int PushLimit(const char* ptr, int limit) {
    GOOGLE_DCHECK(limit >= 0);
    limit += ptr - buffer_end_;
    if (limit < 0) limit_end_ = buffer_end_ + limit;
    auto old_limit = limit_;
    limit_ = limit;
    return old_limit - limit;
  }

  void PopLimit(int delta) {
    // Ensure not to forget to check PushLimit return value
    GOOGLE_DCHECK(delta >= 0);
    // In a correct parse this addition can never overflow because all Pop's
    // are paired with a Push. However on an incorrect parse this might not
    // be the case. We use unsigned to prevent UB.
    limit_ =
        static_cast<unsigned int>(limit_) + static_cast<unsigned int>(delta);
    limit_end_ = buffer_end_ + (std::min)(0, limit_);
  }

  PROTOBUF_MUST_USE_RESULT const char* Skip(const char* ptr, int size) {
    if (size <= buffer_end_ + kSlopBytes - ptr) {
      return ptr + size;
    }
    return SkipFallback(ptr, size);
  }
  PROTOBUF_MUST_USE_RESULT const char* ReadString(const char* ptr, int size,
                                                  std::string* s) {
    if (size <= buffer_end_ + kSlopBytes - ptr) {
      s->assign(ptr, size);
      return ptr + size;
    }
    return ReadStringFallback(ptr, size, s);
  }
  PROTOBUF_MUST_USE_RESULT const char* AppendString(const char* ptr, int size,
                                                    std::string* s) {
    if (size <= buffer_end_ + kSlopBytes - ptr) {
      s->append(ptr, size);
      return ptr + size;
    }
    return AppendStringFallback(ptr, size, s);
  }

  template <typename Tag, typename T>
  PROTOBUF_MUST_USE_RESULT const char* ReadRepeatedFixed(const char* ptr,
                                                         Tag expected_tag,
                                                         RepeatedField<T>* out);

  template <typename T>
  PROTOBUF_MUST_USE_RESULT const char* ReadPackedFixed(const char* ptr,
                                                       int size,
                                                       RepeatedField<T>* out);
  template <typename T, typename Add>
  PROTOBUF_MUST_USE_RESULT const char* ReadPackedVarint(const char* ptr,
                                                        Add add);

  int ConsecutiveBytes(const char* ptr) const { return limit_end_ - ptr; }
  int BytesUntilLimit(const char* ptr) const {
    return buffer_end_ - ptr + limit_;
  }
  bool AtLimit(const char* ptr) const {
    return (ptr - buffer_end_ == limit_) ||
           (next_chunk_ == nullptr && limit_ > 0 && ptr == buffer_end_);
  }

 protected:
  // Returns true is limit (either an explicit limit or end of stream) is
  // reached. It aligns *ptr across buffer seams.
  // If limit is exceeded it returns true and ptr is set to null.
  bool DoneWithCheck(const char** ptr, int d) {
    GOOGLE_DCHECK(*ptr);
    if (PROTOBUF_PREDICT_TRUE(*ptr < limit_end_)) return false;
    // No need to fetch buffer if we ended on a limit in the slop region
    if ((*ptr - buffer_end_) == limit_) return true;
    auto res = DoneFallback(*ptr, d);
    *ptr = res.first;
    return res.second;
  }

  const char* InitFrom(StringPiece flat) {
    if (flat.size() > kSlopBytes) {
      limit_ = kSlopBytes;
      limit_end_ = buffer_end_ = flat.end() - kSlopBytes;
      if (aliasing_ == kOnPatch) aliasing_ = kNoDelta;
      return flat.begin();
    } else {
      std::memcpy(buffer_, flat.begin(), flat.size());
      limit_ = 0;
      limit_end_ = buffer_end_ = buffer_ + flat.size();
      next_chunk_ = nullptr;
      if (aliasing_ == kOnPatch) {
        aliasing_ = reinterpret_cast<std::uintptr_t>(flat.data()) -
                    reinterpret_cast<std::uintptr_t>(buffer_);
      }
      return buffer_;
    }
  }

  const char* InitFrom(io::ZeroCopyInputStream* zcis);

  const char* InitFrom(io::ZeroCopyInputStream* zcis, int limit) {
    auto res = InitFrom(zcis);
    limit_ = limit - (buffer_end_ - res);
    limit_end_ = buffer_end_ + (std::min)(0, limit_);
    return res;
  }

 private:
  const char* limit_end_ =
      buffer_ + kSlopBytes;  // buffer_end_ + min(limit_, 0)
  const char* buffer_end_ = buffer_ + kSlopBytes;
  const char* next_chunk_ = buffer_;
  int size_;
  int limit_ = INT_MAX;  // relative to buffer_end_;
  io::ZeroCopyInputStream* zcis_ = nullptr;
  char buffer_[2 * kSlopBytes] = {};
  enum { kNoAliasing = 0, kOnPatch = 1, kNoDelta = 2 };
  std::uintptr_t aliasing_ = kNoAliasing;

  std::pair<const char*, bool> DoneFallback(const char* ptr, int d);
  const char* Next(int overrun, int d);
  const char* SkipFallback(const char* ptr, int size);
  const char* AppendStringFallback(const char* ptr, int size, std::string* str);
  const char* ReadStringFallback(const char* ptr, int size, std::string* str);

  template <typename A>
  const char* AppendSize(const char* ptr, int size, const A& append) {
    int chunk_size = buffer_end_ + kSlopBytes - ptr;
    if (size > buffer_end_ - ptr + limit_) return nullptr;
    do {
      GOOGLE_DCHECK(size > chunk_size);
      append(ptr, chunk_size);
      ptr += chunk_size;
      size -= chunk_size;
      auto res = DoneFallback(ptr, -1);
      if (res.second) {
        return nullptr;  // If done we passed the limit
      }
      ptr = res.first;
      chunk_size = buffer_end_ + kSlopBytes - ptr;
    } while (size > chunk_size);
    append(ptr, size);
    return ptr + size;
  }

  template <typename A>
  const char* AppendUntilEnd(const char* ptr, const A& append) {
    while (!DoneWithCheck(&ptr, -1)) {
      append(ptr, limit_end_ - ptr);
      ptr = limit_end_;
    }
    return ptr;
  }

  PROTOBUF_MUST_USE_RESULT const char* AppendString(const char* ptr,
                                                    std::string* str) {
    return AppendUntilEnd(ptr,
                          [str](const char* p, int s) { str->append(p, s); });
  }
  friend class ImplicitWeakMessage;
};

// ParseContext holds all data that is global to the entire parse. Most
// importantly it contains the input stream, but also recursion depth and also
// stores the end group tag, in case a parser ended on a endgroup, to verify
// matching start/end group tags.
class PROTOBUF_EXPORT ParseContext
    : public EpsCopyInputStream {
 public:
  struct Data {
    const DescriptorPool* pool = nullptr;
    MessageFactory* factory = nullptr;
  };

  template <typename... T>
  ParseContext(int depth, bool aliasing, const char** start, T&&... args)
      : EpsCopyInputStream(aliasing), depth_(depth) {
    *start = InitFrom(std::forward<T>(args)...);
  }

  void TrackCorrectEnding() { group_depth_ = 0; }

  bool Done(const char** ptr) { return DoneWithCheck(ptr, group_depth_); }
  bool DoneNoSlopCheck(const char** ptr) { return DoneWithCheck(ptr, -1); }

  int depth() const { return depth_; }
  void SetLastTag(uint32 tag) { last_tag_minus_1_ = tag - 1; }
  uint32 LastTagMinus1() const { return last_tag_minus_1_; }

  bool AtLegitimateEnd(const char* ptr) const {
    return ptr && AtLimit(ptr) && last_tag_minus_1_ == 0;
  }

  Data& data() { return data_; }
  const Data& data() const { return data_; }

  template <typename T>
  PROTOBUF_MUST_USE_RESULT const char* ParseMessage(T* msg, const char* ptr);

  template <typename T>
  PROTOBUF_MUST_USE_RESULT const char* ParseGroup(T* msg, const char* ptr,
                                                  uint32 tag) {
    if (--depth_ < 0) return nullptr;
    group_depth_++;
    ptr = msg->_InternalParse(ptr, this);
    group_depth_--;
    depth_++;
    if (last_tag_minus_1_ != tag) return nullptr;
    last_tag_minus_1_ = 0;
    return ptr;
  }

 private:
  // The context keeps an internal stack to keep track of the recursive
  // part of the parse state.
  // Current depth of the active parser, depth counts down.
  // This is used to limit recursion depth (to prevent overflow on malicious
  // data), but is also used to index in stack_ to store the current state.
  int depth_;
  // Unfortunately necessary for the fringe case of ending on 0 or end-group tag
  // in the last kSlopBytes of a ZeroCopyInputStream chunk.
  int group_depth_ = INT_MIN;
  uint32 last_tag_minus_1_ = 0;
  Data data_;
};

template <typename T>
T UnalignedLoad(const void* p) {
  T res;
  memcpy(&res, p, sizeof(T));
  return res;
}

// TODO(gerbens) Experiment with best implementation.
// Clang unrolls loop and generating pretty good code on O2, gcc doesn't.
// Unclear if we want 64 bit parse loop unrolled, inlined or opaque function
// call. Hence experimentation is needed.
// Important guarantee is that it doesn't read more than size bytes from p.
template <int size, typename T>
PROTOBUF_MUST_USE_RESULT const char* VarintParse(const char* p, T* out) {
  T res = 1;
  for (int i = 0; i < size; i++) {
    T byte = static_cast<uint8>(p[i]);
    res += (byte - 1) << (i * 7);
    int j = i + 1;
    if (PROTOBUF_PREDICT_TRUE(byte < 128)) {
      *out = res;
      return p + j;
    }
  }
  *out = 0;
  return nullptr;
}

// Decode 2 consecutive bytes of a varint. Two bytes must be available from
// ptr. Returns ptr + 1 or ptr + 2 depending if the first byte had continuation
// bit set. Stores The value of the varint shifted left by one.
// If bit 15 of *res is set (equivalent to the continuation bits of both bytes
// being set) the varint continues, otherwise the parse is done. On x86
// movzx eax, word ptr [rdi]
// movsx edx, al
// and eax, edx
// add eax, edx
// adc rdi, 1
inline const char* DecodeTwoBytes(const char* ptr, uint32* res) {
  uint32_t y = UnalignedLoad<uint16>(ptr);
  // Sign extend the low byte continuation bit
  uint32_t x = static_cast<int8_t>(y);
  y &= x;  // Mask out the high byte iff no continuation
  // This add is an amazing operation, it cancels the low byte continuation bit
  // from y transferring it to the carry. Simultaneously it also shifts the 7
  // LSB left by one tightly against high byte varint bits. Hence y now
  // contains the unpacked value shifted left by 1.
  y += x;
  *res = y;
  // If the addition above carried the high byte was part of the varint. Alas
  // in c we don't have access to the carry, but a good optimizer compiles this
  // down to a "adc" instruction.
  return ptr + (y < x ? 2 : 1);
}

inline uint32 ReadSmallVarint(const char** ptr) {
  uint32 res;
  *ptr = DecodeTwoBytes(*ptr, &res);
  return res >> 1;
}

std::pair<const char*, uint32> Parse32Fallback(const char* p, uint32 res);

inline const char* _Parse32(const char* p, uint32* out) {
  return VarintParse<5>(p, out);
}

inline const char* ReadTagOne(const char* p, uint32* out) {
  *out = static_cast<uint8>(*p);
  return p + 1;
}

inline const char* ReadTagTwo(const char* p, uint32* out) {
  uint32 res = static_cast<uint8>(p[0]);
  if (res < 128) { *out = res; return p + 1; }
  uint32 byte = static_cast<uint8>(p[1]);
  res += (byte << 7) - 128;
  *out = res;
  return p + 2;
}

inline const char* FinishReadTagOne(const char* p, uint32* tag) {
  if (*tag & 128) {
    uint32 tmp;
    p = VarintParse<4>(p, &tmp);
    *tag += ((tmp - 1) << 7);
  }
  return p;
}

inline const char* FinishReadTagTwo(const char* p, uint32* tag) {
  if (*tag & (1 << 14)) {
    uint32 tmp;
    p = VarintParse<3>(p, &tmp);
    *tag += ((tmp - 1) << 14);
  }
  return p;
}

// Used for tags, could read up to 5 bytes which must be available.
// Caller must ensure its safe to call.
inline const char* ReadTag(const char* p, uint32* out) {
  return _Parse32(p, out);
}

std::pair<const char*, uint64> ParseVarint64Fallback(const char* p, uint64 res);

// Used for reading varint wiretype values, could read up to 10 bytes.
// Caller must ensure its safe to call.
inline const char* ParseVarint64(const char* p, uint64* out) {
  std::uint32_t tmp;
  p = DecodeTwoBytes(p, &tmp);
  if (PROTOBUF_PREDICT_TRUE(static_cast<int16>(tmp) >= 0)) {
    *out = tmp >> 1;
    return p;
  }
  auto x = ParseVarint64Fallback(p, tmp);
  *out = x.second;
  return x.first;
}

std::pair<const char*, int32> ReadSizeFallback(const char* p, uint32 first);
// Used for tags, could read up to 5 bytes which must be available. Additionally
// it makes sure the unsigned value fits a int32, otherwise returns nullptr.
// Caller must ensure its safe to call.
inline uint32 ReadSize(const char** pp) {
  auto p = *pp;
  uint32 res = static_cast<uint8>(p[0]);
  if (res < 128) {
    *pp = p + 1;
    return res;
  }
  auto x = ReadSizeFallback(p, res);
  *pp = x.first;
  return x.second;
}

// Some convenience functions to simplify the generated parse loop code.
// Returning the value and updating the buffer pointer allows for nicer
// function composition. We rely on the compiler to inline this.
// Also in debug compiles having local scoped variables tend to generated
// stack frames that scale as O(num fields).
inline uint64 ReadVarint(const char** p) {
  uint64 tmp;
  *p = ParseVarint64(*p, &tmp);
  return tmp;
}

inline int64 ReadVarintZigZag64(const char** p) {
  uint64 tmp;
  *p = ParseVarint64(*p, &tmp);
  return WireFormatLite::ZigZagDecode64(tmp);
}

inline int32 ReadVarintZigZag32(const char** p) {
  uint64 tmp;
  *p = ParseVarint64(*p, &tmp);
  return WireFormatLite::ZigZagDecode32(tmp);
}

template <typename T>
PROTOBUF_MUST_USE_RESULT const char* ParseContext::ParseMessage(
    T* msg, const char* ptr) {
  int size = ReadSize(&ptr);
  if (!ptr) return nullptr;
  auto old = PushLimit(ptr, size);
  if (--depth_ < 0 || old < 0) return nullptr;
  ptr = msg->_InternalParse(ptr, this);
  depth_++;
  PopLimit(old);
  if (last_tag_minus_1_ != 0) return nullptr;
  return ptr;
}

template <typename T, typename Add>
PROTOBUF_MUST_USE_RESULT const char* EpsCopyInputStream::ReadPackedVarint(
    const char* ptr, Add add) {
  int size = ReadSize(&ptr);
  if (ptr == nullptr) return nullptr;
  auto old = PushLimit(ptr, size);
  if (old < 0) return nullptr;
  while (!DoneWithCheck(&ptr, -1)) {
    uint64 varint;
    ptr = ParseVarint64(ptr, &varint);
    if (!ptr) return nullptr;
    add(varint);
  }
  PopLimit(old);
  return ptr;
}

// Helper for verification of utf8
PROTOBUF_EXPORT
bool VerifyUTF8(StringPiece s, const char* field_name);

// All the string parsers with or without UTF checking and for all CTypes.
inline PROTOBUF_MUST_USE_RESULT const char* InlineGreedyStringParser(
    std::string* s, const char* ptr, ParseContext* ctx) {
  int size = ReadSize(&ptr);
  if (!ptr) return nullptr;
  return ctx->ReadString(ptr, size, s);
}

PROTOBUF_MUST_USE_RESULT const char* InlineGreedyStringParserUTF8(
    std::string* s, const char* ptr, ParseContext* ctx, const char* field_name);
PROTOBUF_MUST_USE_RESULT const char* InlineGreedyStringParserUTF8Verify(
    std::string* s, const char* ptr, ParseContext* ctx, const char* field_name);


// Add any of the following lines to debug which parse function is failing.

#define GOOGLE_PROTOBUF_ASSERT_RETURN(predicate, ret) \
  if (!(predicate)) {                                  \
    /*  ::raise(SIGINT);  */                           \
    /*  GOOGLE_LOG(ERROR) << "Parse failure";  */             \
    return ret;                                        \
  }

#define GOOGLE_PROTOBUF_PARSER_ASSERT(predicate) \
    GOOGLE_PROTOBUF_ASSERT_RETURN(predicate, nullptr)

template <typename T>
PROTOBUF_MUST_USE_RESULT const char* FieldParser(uint64 tag, T& field_parser,
                                                 const char* ptr,
                                                 ParseContext* ctx) {
  uint32 number = tag >> 3;
  GOOGLE_PROTOBUF_PARSER_ASSERT(number != 0);
  using WireType = internal::WireFormatLite::WireType;
  switch (tag & 7) {
    case WireType::WIRETYPE_VARINT: {
      uint64 value;
      ptr = ParseVarint64(ptr, &value);
      GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
      field_parser.AddVarint(number, value);
      break;
    }
    case WireType::WIRETYPE_FIXED64: {
      uint64 value = UnalignedLoad<uint64>(ptr);
      ptr += 8;
      field_parser.AddFixed64(number, value);
      break;
    }
    case WireType::WIRETYPE_LENGTH_DELIMITED: {
      ptr = field_parser.ParseLengthDelimited(number, ptr, ctx);
      GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
      break;
    }
    case WireType::WIRETYPE_START_GROUP: {
      ptr = field_parser.ParseGroup(number, ptr, ctx);
      GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
      break;
    }
    case WireType::WIRETYPE_END_GROUP: {
      GOOGLE_LOG(FATAL) << "Can't happen";
      break;
    }
    case WireType::WIRETYPE_FIXED32: {
      uint32 value = UnalignedLoad<uint32>(ptr);
      ptr += 4;
      field_parser.AddFixed32(number, value);
      break;
    }
    default:
      return nullptr;
  }
  return ptr;
}

template <typename T>
PROTOBUF_MUST_USE_RESULT const char* WireFormatParser(T& field_parser,
                                                      const char* ptr,
                                                      ParseContext* ctx) {
  while (!ctx->Done(&ptr)) {
    uint32 tag;
    ptr = ReadTag(ptr, &tag);
    GOOGLE_PROTOBUF_PARSER_ASSERT(ptr != nullptr);
    if (tag == 0 || (tag & 7) == 4) {
      ctx->SetLastTag(tag);
      return ptr;
    }
    ptr = FieldParser(tag, field_parser, ptr, ctx);
    GOOGLE_PROTOBUF_PARSER_ASSERT(ptr != nullptr);
  }
  return ptr;
}

// The packed parsers parse repeated numeric primitives directly into  the
// corresponding field

// These are packed varints
PROTOBUF_EXPORT PROTOBUF_MUST_USE_RESULT const char* PackedInt32Parser(
    void* object, const char* ptr, ParseContext* ctx);
PROTOBUF_EXPORT PROTOBUF_MUST_USE_RESULT const char* PackedUInt32Parser(
    void* object, const char* ptr, ParseContext* ctx);
PROTOBUF_EXPORT PROTOBUF_MUST_USE_RESULT const char* PackedInt64Parser(
    void* object, const char* ptr, ParseContext* ctx);
PROTOBUF_EXPORT PROTOBUF_MUST_USE_RESULT const char* PackedUInt64Parser(
    void* object, const char* ptr, ParseContext* ctx);
PROTOBUF_EXPORT PROTOBUF_MUST_USE_RESULT const char* PackedSInt32Parser(
    void* object, const char* ptr, ParseContext* ctx);
PROTOBUF_EXPORT PROTOBUF_MUST_USE_RESULT const char* PackedSInt64Parser(
    void* object, const char* ptr, ParseContext* ctx);
PROTOBUF_EXPORT PROTOBUF_MUST_USE_RESULT const char* PackedEnumParser(
    void* object, const char* ptr, ParseContext* ctx);
PROTOBUF_EXPORT PROTOBUF_MUST_USE_RESULT const char* PackedEnumParser(
    void* object, const char* ptr, ParseContext* ctx, bool (*is_valid)(int),
    std::string* unknown, int field_num);
PROTOBUF_EXPORT PROTOBUF_MUST_USE_RESULT const char* PackedEnumParserArg(
    void* object, const char* ptr, ParseContext* ctx,
    bool (*is_valid)(const void*, int), const void* data, std::string* unknown,
    int field_num);

PROTOBUF_EXPORT PROTOBUF_MUST_USE_RESULT const char* PackedBoolParser(
    void* object, const char* ptr, ParseContext* ctx);
PROTOBUF_EXPORT PROTOBUF_MUST_USE_RESULT const char* PackedFixed32Parser(
    void* object, const char* ptr, ParseContext* ctx);
PROTOBUF_EXPORT PROTOBUF_MUST_USE_RESULT const char* PackedSFixed32Parser(
    void* object, const char* ptr, ParseContext* ctx);
PROTOBUF_EXPORT PROTOBUF_MUST_USE_RESULT const char* PackedFixed64Parser(
    void* object, const char* ptr, ParseContext* ctx);
PROTOBUF_EXPORT PROTOBUF_MUST_USE_RESULT const char* PackedSFixed64Parser(
    void* object, const char* ptr, ParseContext* ctx);
PROTOBUF_EXPORT PROTOBUF_MUST_USE_RESULT const char* PackedFloatParser(
    void* object, const char* ptr, ParseContext* ctx);
PROTOBUF_EXPORT PROTOBUF_MUST_USE_RESULT const char* PackedDoubleParser(
    void* object, const char* ptr, ParseContext* ctx);

// This is the only recursive parser.
PROTOBUF_EXPORT PROTOBUF_MUST_USE_RESULT const char* UnknownGroupLiteParse(
    std::string* unknown, const char* ptr, ParseContext* ctx);
// This is a helper to for the UnknownGroupLiteParse but is actually also
// useful in the generated code. It uses overload on string* vs
// UnknownFieldSet* to make the generated code isomorphic between full and lite.
PROTOBUF_EXPORT PROTOBUF_MUST_USE_RESULT const char* UnknownFieldParse(
    uint32 tag, std::string* unknown, const char* ptr, ParseContext* ctx);

}  // namespace internal
}  // namespace protobuf
}  // namespace google

#include <google/protobuf/port_undef.inc>

#endif  // GOOGLE_PROTOBUF_PARSE_CONTEXT_H__
