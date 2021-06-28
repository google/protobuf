#!/bin/bash
#
# Build file to set up and run tests
set -ex

# Install Bazel 4.0.0.
use_bazel.sh 4.0.0
bazel version

function run_tests {
  bazel test \
    --test_summary=testcase \
    --test_output=errors \
      //:build_files_updated_unittest \
      //java/... \
      //:protoc \
      //:protobuf \
      //:protobuf_python \
      //:protobuf_test \
      @com_google_protobuf//:cc_proto_blacklist_test \
    $@
}

# Change to repo root
cd $(dirname $0)/../../..

run_tests "--//:with_abseil=false"
run_tests "--//:with_abseil=true"

cd examples
bazel build //...
