// Protocol Buffers - Google's data interchange format
// Copyright 2026 Google LLC
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd

#ifndef GOOGLE_PROTOBUF_PRIVATE_ACCESS_H__
#define GOOGLE_PROTOBUF_PRIVATE_ACCESS_H__

#include <type_traits>

namespace google {
namespace protobuf {

class Arena;
class MessageLite;

namespace internal {

struct ClassData;
class ExtensionSet;
class ThreadSafeArena;

template <bool kHasCreatorFunc, bool kHasIsInitialized>
struct MessageGlobalsOptionalFuncs {};

template <>
struct MessageGlobalsOptionalFuncs<true, false> {
  void* (*creator_func)(const void*, void*, Arena*);
};

template <>
struct MessageGlobalsOptionalFuncs<false, true> {
  bool (*is_initialized)(const MessageLite&);
};

template <>
struct MessageGlobalsOptionalFuncs<true, true> {
  void* (*creator_func)(const void*, void*, Arena*);
  bool (*is_initialized)(const MessageLite&);
};

template <typename ParseTableT, bool kHasCreatorFunc, bool kHasIsInitialized>
struct MessageGlobalsParseTableWrapper
    : MessageGlobalsOptionalFuncs<kHasCreatorFunc, kHasIsInitialized>,
      ParseTableT {};

// The struct PrivateAccess is used to provide access to private members of
// message classes without making them public. This is useful for highly
// optimized code paths that need to access internals.
struct PrivateAccess {
  template <typename T, int number>
  static constexpr bool IsLazyField() {
    constexpr auto l =
        [](auto& msg) -> decltype(msg._lazy_internal_mutable(
                          std::integral_constant<int, number>{})) {};
    return std::is_invocable_v<decltype(l), T&>;
  }

  template <int number, typename T>
  static auto& MutableLazy(T& msg) {
    return msg._lazy_internal_mutable(std::integral_constant<int, number>{});
  }

  template <typename MessageT>
  static auto& GetInternalMetadata(MessageT& msg) {
    return msg._internal_metadata_;
  }

  template <typename T>
  static auto& GetExtensionSet(T& msg) {
    return msg._impl_._extensions_;
  }

  // Defined in extension_set.cc
  static ExtensionSet* GetExtensionSet(MessageLite& msg);
  static const ExtensionSet* GetExtensionSet(const MessageLite& msg);

  template <typename T>
  static void TrackerOnGetMetadata() {
    T::Impl_::TrackerOnGetMetadata();
  }

  template <typename T>
  static constexpr auto GenerateClassData() {
    return T::_Internal::GenerateClassData();
  }

  template <typename T>
  static constexpr auto GenerateParseTable(
      const ::google::protobuf::internal::ClassData* class_data) {
    constexpr auto cd = GenerateClassData<T>();
    constexpr bool kHasCreatorFunc =
        static_cast<int>(cd.message_creator.tag()) < 0;
    constexpr bool kHasIsInit = cd.has_is_initialized != 0;
    using ParseTableT = decltype(T::_Internal::GenerateParseTable(class_data));
    if constexpr (!kHasCreatorFunc && !kHasIsInit) {
      return T::_Internal::GenerateParseTable(class_data);
    } else if constexpr (kHasCreatorFunc && !kHasIsInit) {
      return MessageGlobalsParseTableWrapper<ParseTableT, true, false>{
          {&T::_Internal::PlacementNew},
          T::_Internal::GenerateParseTable(class_data),
      };
    } else if constexpr (!kHasCreatorFunc && kHasIsInit) {
      return MessageGlobalsParseTableWrapper<ParseTableT, false, true>{
          {&T::IsInitializedImpl},
          T::_Internal::GenerateParseTable(class_data),
      };
    } else {
      return MessageGlobalsParseTableWrapper<ParseTableT, true, true>{
          {&T::_Internal::PlacementNew, &T::IsInitializedImpl},
          T::_Internal::GenerateParseTable(class_data),
      };
    }
  }

  template <typename T>
  static constexpr decltype(auto) FullMessageName() {
    return T::FullMessageName();
  }

  // Defined in arena.h
  static constexpr ThreadSafeArena& GetThreadSafeArena(Arena& arena);

  template <typename T>
  using ImplTForTesting = typename T::Impl_;
};

}  // namespace internal
}  // namespace protobuf
}  // namespace google

#endif  // GOOGLE_PROTOBUF_PRIVATE_ACCESS_H__
