// Protocol Buffers - Google's data interchange format
// Copyright 2026 Google Inc.  All rights reserved.
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd

#include "google/protobuf/testing/get_type_name.h"

#include <cstddef>
#include <string>
#include <vector>

#include "absl/strings/ascii.h"
#include "absl/strings/match.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_replace.h"
#include "absl/strings/string_view.h"
#include "absl/types/optional.h"
#include "absl/types/span.h"

namespace google {
namespace protobuf {
namespace internal {
namespace {

// Uses `RawPrettyFunction::Get<double>()` as a probe to determine the
// compiler-specific prefix and suffix in `RawPrettyFunction` output.
absl::optional<absl::string_view> ExtractRaw(
    absl::optional<absl::string_view> raw) {
  absl::optional<absl::string_view> probe = RawPrettyFunction::Get<double>();
  if (!raw.has_value() || !probe.has_value()) return absl::nullopt;
  constexpr absl::string_view kTarget = "double";
  size_t prefix = probe->find(kTarget);
  if (prefix == absl::string_view::npos) return absl::nullopt;
  size_t suffix = probe->size() - prefix - kTarget.size();
  if (raw->size() < prefix + suffix) return absl::nullopt;
  raw->remove_prefix(prefix);
  raw->remove_suffix(suffix);
  return *raw;
}

// Strips the trailing `<...>` template argument list from a template
// instantiation name, or returns `absl::nullopt` if none is balanced at the
// end.
absl::optional<absl::string_view> StripTrailingTemplateArgs(
    absl::string_view str) {
  str = absl::StripTrailingAsciiWhitespace(str);
  if (str.empty() || str.back() != '>') return absl::nullopt;
  std::vector<char> to_open = {'<'};
  for (size_t i = str.size() - 1; i-- > 0;) {
    char c = str[i];
    if (c == ')') {
      to_open.push_back('(');
    } else if (c == '}') {
      to_open.push_back('{');
    } else if (c == ']') {
      to_open.push_back('[');
    } else if (c == '(' || c == '{' || c == '[') {
      if (to_open.back() != c) return absl::nullopt;
      to_open.pop_back();
    } else if (to_open.back() == '<') {
      if (c == '>' && (i == 0 || str[i - 1] != '-')) {
        to_open.push_back('<');
      } else if (c == '<') {
        to_open.pop_back();
        if (to_open.empty()) {
          return i > 0 ? absl::make_optional(str.substr(0, i)) : absl::nullopt;
        }
      }
    }
  }
  return absl::nullopt;
}

absl::optional<std::string> CleanTypeName(absl::string_view str) {
  // Reject names that still contain template arguments we couldn't decompose
  // (e.g. non-type template parameters or nested types inside templates).
  if (absl::StrContains(str, '<')) return absl::nullopt;
  // Strip MSVC tag keywords, anonymous namespace markers, and standard library
  // inline namespaces.
  return absl::StrReplaceAll(absl::StripAsciiWhitespace(str),
                             {{"class ", ""},
                              {"struct ", ""},
                              {"enum ", ""},
                              {"union ", ""},
                              {"(anonymous namespace)::", ""},
                              {"{anonymous}::", ""},
                              {"`anonymous namespace'::", ""},
                              {"`anonymous-namespace'::", ""},
                              {"std::__u::", "std::"},
                              {"std::__1::", "std::"},
                              {"std::__cxx11::", "std::"}});
}

}  // namespace

absl::optional<std::string> CleanRawTypeName(
    absl::optional<absl::string_view> raw) {
  absl::optional<absl::string_view> extracted = ExtractRaw(raw);
  if (!extracted.has_value()) return absl::nullopt;
  return CleanTypeName(*extracted);
}

absl::optional<std::string> FormatTemplateTypeName(
    absl::optional<absl::string_view> raw,
    absl::Span<const absl::optional<std::string>> args) {
  absl::optional<absl::string_view> extracted = ExtractRaw(raw);
  if (!extracted.has_value()) return absl::nullopt;
  absl::optional<absl::string_view> base_raw =
      StripTrailingTemplateArgs(*extracted);
  if (!base_raw.has_value()) return absl::nullopt;
  absl::optional<std::string> base = CleanTypeName(*base_raw);
  if (!base.has_value()) return absl::nullopt;

  std::vector<absl::string_view> unwrapped_args;
  unwrapped_args.reserve(args.size());
  for (const auto& arg : args) {
    if (!arg.has_value()) return absl::nullopt;
    unwrapped_args.push_back(*arg);
  }
  return absl::StrCat(*base, "<", absl::StrJoin(unwrapped_args, ", "), ">");
}

}  // namespace internal
}  // namespace protobuf
}  // namespace google
