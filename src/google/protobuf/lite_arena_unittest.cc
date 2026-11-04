// Protocol Buffers - Google's data interchange format
// Copyright 2008 Google Inc.  All rights reserved.
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd

#include <memory>
#include <string>

#include "absl/log/absl_check.h"
#include "absl/strings/str_cat.h"
#include "google/protobuf/arena.h"
#include "google/protobuf/map_lite_unittest.pb.h"
#include "google/protobuf/map_test_util.h"
#include "google/protobuf/unittest_lite.pb.h"

#include <gtest/gtest.h>


namespace google {
namespace protobuf {
namespace {

using proto2_unittest::TestAllTypesLite;
using proto2_unittest::TestParsingMergeLite;

class LiteArenaTest : public testing::Test {
 protected:
  LiteArenaTest() {
    ArenaOptions options;
    options.start_block_size = 128 * 1024;
    options.max_block_size = 128 * 1024;
    arena_.reset(new Arena(options));
    // Trigger the allocation of the first arena block, so that further use of
    // the arena will not require any heap allocations.
    (void)Arena::CreateArray<char>(arena_.get(), 1);
  }

  Arena* arena() { return arena_.get(); }

  std::unique_ptr<Arena> arena_;
};

TEST_F(LiteArenaTest, MapNoHeapAllocation) {
  std::string data;
  data.reserve(128 * 1024);

  {
    // TODO: Enable no heap check when ArenaStringPtr is used in
    // Map.
    // internal::NoHeapChecker no_heap;

    proto2_unittest::TestArenaMapLite* from =
        Arena::Create<proto2_unittest::TestArenaMapLite>(arena());
    MapTestUtil::SetArenaMapFields(from);
    ABSL_CHECK(from->SerializeToString(&data));

    proto2_unittest::TestArenaMapLite* to =
        Arena::Create<proto2_unittest::TestArenaMapLite>(arena());
    ABSL_CHECK(to->ParseFromString(data));
    MapTestUtil::ExpectArenaMapFieldsSet(*to);
  }
}

TEST_F(LiteArenaTest, UnknownFieldMemLeak) {
  proto2_unittest::ForeignMessageArenaLite* message =
      Arena::Create<proto2_unittest::ForeignMessageArenaLite>(arena());
  std::string data = "\012\000";
  int original_capacity = data.capacity();
  while (data.capacity() <= original_capacity) {
    data.append("a");
  }
  data[1] = data.size() - 2;
  ABSL_CHECK(message->ParseFromString(data));
}

// Parsing into an existing extension on the heap under an arena-allocated
// parent must allocate the extension's new fields on the heap, and then
// resume allocating on the parent's arena for the parent's subsequent fields.
TEST_F(LiteArenaTest, ParseIntoExtensionOnHeap) {
  auto* parent = Arena::Create<TestParsingMergeLite>(arena());
  auto* child = Arena::Create<TestAllTypesLite>(nullptr);
  parent->SetAllocatedExtension(TestParsingMergeLite::optional_ext, child);

  TestParsingMergeLite data;
  data.MutableExtension(TestParsingMergeLite::optional_ext)
      ->mutable_optional_nested_message();
  TestParsingMergeLite after;
  after.mutable_required_all_types();
  ASSERT_TRUE(parent->MergeFromString(absl::StrCat(
      data.SerializePartialAsString(), after.SerializeAsString())));

  EXPECT_EQ(child->optional_nested_message().GetArena(), nullptr);
  EXPECT_EQ(parent->required_all_types().GetArena(), arena());
}

}  // namespace
}  // namespace protobuf
}  // namespace google

