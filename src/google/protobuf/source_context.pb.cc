// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: google/protobuf/source_context.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include <google/protobuf/source_context.pb.h>

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace google {
namespace protobuf {
class SourceContextDefaultTypeInternal : public ::google::protobuf::internal::ExplicitlyConstructed<SourceContext> {};
SourceContextDefaultTypeInternal _SourceContext_default_instance_;

namespace {

::google::protobuf::Metadata file_level_metadata[1];

}  // namespace


void protobuf_AssignDesc_google_2fprotobuf_2fsource_5fcontext_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AssignDesc_google_2fprotobuf_2fsource_5fcontext_2eproto() {
  protobuf_AddDesc_google_2fprotobuf_2fsource_5fcontext_2eproto();
  static const ::google::protobuf::uint32 offsets[] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SourceContext, file_name_),
  };
  static const ::google::protobuf::internal::ReflectionSchema schemas[] = {
    { reinterpret_cast<const   ::google::protobuf::Message*>(&_SourceContext_default_instance_),
      offsets + 0,
      NULL,
      -1,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SourceContext, _internal_metadata_),
        -1,
      NULL,
      -1,
      sizeof(SourceContext),
    },
  };
  (void)offsets;  // suppress unused variable warning
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "google/protobuf/source_context.proto", schemas, factory,
      file_level_metadata, NULL, NULL);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_google_2fprotobuf_2fsource_5fcontext_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 1);
}

}  // namespace

void protobuf_ShutdownFile_google_2fprotobuf_2fsource_5fcontext_2eproto() {
  _SourceContext_default_instance_.Shutdown();
  delete file_level_metadata[0].reflection;
}

void protobuf_InitDefaults_google_2fprotobuf_2fsource_5fcontext_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::internal::InitProtobufDefaults();
  _SourceContext_default_instance_.DefaultConstruct();
}

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_InitDefaults_google_2fprotobuf_2fsource_5fcontext_2eproto_once_);
void protobuf_InitDefaults_google_2fprotobuf_2fsource_5fcontext_2eproto() {
  ::google::protobuf::GoogleOnceInit(&protobuf_InitDefaults_google_2fprotobuf_2fsource_5fcontext_2eproto_once_,
                 &protobuf_InitDefaults_google_2fprotobuf_2fsource_5fcontext_2eproto_impl);
}
void protobuf_AddDesc_google_2fprotobuf_2fsource_5fcontext_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  protobuf_InitDefaults_google_2fprotobuf_2fsource_5fcontext_2eproto();
  static const char descriptor[] = {
      "\n$google/protobuf/source_context.proto\022\017"
      "google.protobuf\"\"\n\rSourceContext\022\021\n\tfile"
      "_name\030\001 \001(\tB\225\001\n\023com.google.protobufB\022Sou"
      "rceContextProtoP\001ZAgoogle.golang.org/gen"
      "proto/protobuf/source_context;source_con"
      "text\242\002\003GPB\252\002\036Google.Protobuf.WellKnownTy"
      "pesb\006proto3"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 251);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "google/protobuf/source_context.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_google_2fprotobuf_2fsource_5fcontext_2eproto);
}

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_google_2fprotobuf_2fsource_5fcontext_2eproto_once_);
void protobuf_AddDesc_google_2fprotobuf_2fsource_5fcontext_2eproto() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_google_2fprotobuf_2fsource_5fcontext_2eproto_once_,
                 &protobuf_AddDesc_google_2fprotobuf_2fsource_5fcontext_2eproto_impl);
}
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_google_2fprotobuf_2fsource_5fcontext_2eproto {
  StaticDescriptorInitializer_google_2fprotobuf_2fsource_5fcontext_2eproto() {
    protobuf_AddDesc_google_2fprotobuf_2fsource_5fcontext_2eproto();
  }
} static_descriptor_initializer_google_2fprotobuf_2fsource_5fcontext_2eproto_;

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int SourceContext::kFileNameFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

SourceContext::SourceContext()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_InitDefaults_google_2fprotobuf_2fsource_5fcontext_2eproto();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:google.protobuf.SourceContext)
}
SourceContext::SourceContext(const SourceContext& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  file_name_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.file_name().size() > 0) {
    file_name_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.file_name_);
  }
  // @@protoc_insertion_point(copy_constructor:google.protobuf.SourceContext)
}

void SourceContext::SharedCtor() {
  file_name_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  _cached_size_ = 0;
}

SourceContext::~SourceContext() {
  // @@protoc_insertion_point(destructor:google.protobuf.SourceContext)
  SharedDtor();
}

void SourceContext::SharedDtor() {
  file_name_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void SourceContext::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* SourceContext::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return file_level_metadata[0].descriptor;
}

const SourceContext& SourceContext::default_instance() {
  protobuf_InitDefaults_google_2fprotobuf_2fsource_5fcontext_2eproto();
  return *internal_default_instance();
}

SourceContext* SourceContext::New(::google::protobuf::Arena* arena) const {
  SourceContext* n = new SourceContext;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void SourceContext::Clear() {
// @@protoc_insertion_point(message_clear_start:google.protobuf.SourceContext)
  file_name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

bool SourceContext::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:google.protobuf.SourceContext)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // string file_name = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_file_name()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->file_name().data(), this->file_name().length(),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "google.protobuf.SourceContext.file_name"));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:google.protobuf.SourceContext)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:google.protobuf.SourceContext)
  return false;
#undef DO_
}

void SourceContext::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:google.protobuf.SourceContext)
  // string file_name = 1;
  if (this->file_name().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->file_name().data(), this->file_name().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "google.protobuf.SourceContext.file_name");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->file_name(), output);
  }

  // @@protoc_insertion_point(serialize_end:google.protobuf.SourceContext)
}

::google::protobuf::uint8* SourceContext::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:google.protobuf.SourceContext)
  // string file_name = 1;
  if (this->file_name().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->file_name().data(), this->file_name().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "google.protobuf.SourceContext.file_name");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->file_name(), target);
  }

  // @@protoc_insertion_point(serialize_to_array_end:google.protobuf.SourceContext)
  return target;
}

size_t SourceContext::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:google.protobuf.SourceContext)
  size_t total_size = 0;

  // string file_name = 1;
  if (this->file_name().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->file_name());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void SourceContext::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:google.protobuf.SourceContext)
  GOOGLE_DCHECK_NE(&from, this);
  const SourceContext* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const SourceContext>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:google.protobuf.SourceContext)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:google.protobuf.SourceContext)
    MergeFrom(*source);
  }
}

void SourceContext::MergeFrom(const SourceContext& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:google.protobuf.SourceContext)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  if (from.file_name().size() > 0) {

    file_name_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.file_name_);
  }
}

void SourceContext::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:google.protobuf.SourceContext)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void SourceContext::CopyFrom(const SourceContext& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:google.protobuf.SourceContext)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool SourceContext::IsInitialized() const {
  return true;
}

void SourceContext::Swap(SourceContext* other) {
  if (other == this) return;
  InternalSwap(other);
}
void SourceContext::InternalSwap(SourceContext* other) {
  file_name_.Swap(&other->file_name_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata SourceContext::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  return file_level_metadata[0];
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// SourceContext

// string file_name = 1;
void SourceContext::clear_file_name() {
  file_name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
const ::std::string& SourceContext::file_name() const {
  // @@protoc_insertion_point(field_get:google.protobuf.SourceContext.file_name)
  return file_name_.GetNoArena();
}
void SourceContext::set_file_name(const ::std::string& value) {
  
  file_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:google.protobuf.SourceContext.file_name)
}
void SourceContext::set_file_name(const char* value) {
  
  file_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:google.protobuf.SourceContext.file_name)
}
void SourceContext::set_file_name(const char* value, size_t size) {
  
  file_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:google.protobuf.SourceContext.file_name)
}
::std::string* SourceContext::mutable_file_name() {
  
  // @@protoc_insertion_point(field_mutable:google.protobuf.SourceContext.file_name)
  return file_name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
::std::string* SourceContext::release_file_name() {
  // @@protoc_insertion_point(field_release:google.protobuf.SourceContext.file_name)
  
  return file_name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void SourceContext::set_allocated_file_name(::std::string* file_name) {
  if (file_name != NULL) {
    
  } else {
    
  }
  file_name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), file_name);
  // @@protoc_insertion_point(field_set_allocated:google.protobuf.SourceContext.file_name)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)
