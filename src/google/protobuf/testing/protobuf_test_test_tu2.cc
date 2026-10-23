// Protocol Buffers - Google's data interchange format
// Copyright 2026 Google Inc.  All rights reserved.
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd

#include <cstdint>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "absl/strings/str_cat.h"
#include "google/protobuf/testing/protobuf_test.h"

// Skew `__COUNTER__` before including the shared fixture header so the two TUs
// have different `__COUNTER__` offsets, and verify that `PB_TEST_CHOOSE_VALUE`
// in the shared header does not consume `__COUNTER__`.
constexpr int kCounterBeforeSharedFixture = __COUNTER__;
#include "google/protobuf/testing/protobuf_test_test_fixture.h"  // NOLINT(build/include_order)
static_assert(__COUNTER__ == kCounterBeforeSharedFixture + 1,
              "Shared fixture header must not depend on __COUNTER__");

namespace google {
namespace protobuf {
namespace internal {
namespace {

PB_TEST_F(ProtobufSharedFixture, SecondTu) {
  using T = PB_TEST_CHOOSE_TYPE((int32_t, int64_t));
  int body = PB_TEST_CHOOSE_VALUE((100), "body");
  constexpr int kScale = PB_TEST_CHOOSE_CONSTEXPR((1, 2), "scale");
  const auto* info = ::testing::UnitTest::GetInstance()->current_test_info();
  SharedFixtureRuns().push_back(
      absl::StrCat("2:", base_, ":", b_, ":", dep_, ":", sizeof(T), ":", body,
                   ":", kScale, ":", info->type_param(), ":", info->name()));
}

}  // namespace
}  // namespace internal
}  // namespace protobuf
}  // namespace google
