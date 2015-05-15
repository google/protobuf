#!/bin/bash
# Generates C# source files from .proto files.
# You first need to make sure protoc has been built (see instructions on
# building protoc in root of this repository)

set -ex

# cd to repository root
cd $(dirname $0)/..

# Protocol buffer compiler to use. If the PROTOC variable is set,
# use that. Otherwise, probe for expected locations under both
# Windows and Unix.
if [ -z "$PROTOC" ]; then
  # TODO(jonskeet): Use an array and a for loop instead?
  if [ -x vsprojects/Debug/protoc.exe ]; then
    PROTOC=vsprojects/Debug/protoc.exe
  elif [ -x vsprojects/Release/protoc.exe ]; then
    PROTOC=vsprojects/Release/protoc.exe
  elif [ -x src/protoc ]; then
    PROTOC=src/protoc
  else
    echo "Unable to find protocol buffer compiler."
    exit 1
  fi
fi

# Descriptor proto
# Temporary manual fixup...
cp src/google/protobuf/descriptor.proto src/google/protobuf/descriptor_proto_file.proto
$PROTOC -Isrc --csharp_out=csharp/src/ProtocolBuffers/DescriptorProtos \
    src/google/protobuf/descriptor_proto_file.proto
rm src/google/protobuf/descriptor_proto_file.proto


# ProtocolBuffers.Test protos
$PROTOC -Isrc --csharp_out=csharp/src/ProtocolBuffers.Test/TestProtos \
    src/google/protobuf/unittest.proto \
    src/google/protobuf/unittest_custom_options.proto \
    src/google/protobuf/unittest_drop_unknown_fields.proto \
    src/google/protobuf/unittest_enormous_descriptor.proto \
    src/google/protobuf/unittest_import.proto \
    src/google/protobuf/unittest_import_public.proto \
    src/google/protobuf/unittest_mset.proto \
    src/google/protobuf/unittest_optimize_for.proto \
    src/google/protobuf/unittest_no_field_presence.proto \
    src/google/protobuf/unknown_enum_test.proto

$PROTOC -Icsharp/protos/extest --csharp_out=csharp/src/ProtocolBuffers.Test/TestProtos \
    csharp/protos/extest/unittest_extras_xmltest.proto \
    csharp/protos/extest/unittest_issues.proto

$PROTOC -Ibenchmarks --csharp_out=csharp/src/ProtocolBuffers.Test/TestProtos \
    benchmarks/google_size.proto \
    benchmarks/google_speed.proto

# ProtocolBuffersLite.Test protos
$PROTOC -Isrc --csharp_out=csharp/src/ProtocolBuffersLite.Test/TestProtos \
    src/google/protobuf/unittest.proto \
    src/google/protobuf/unittest_import.proto \
    src/google/protobuf/unittest_import_lite.proto \
    src/google/protobuf/unittest_import_public.proto \
    src/google/protobuf/unittest_import_public_lite.proto \
    src/google/protobuf/unittest_lite.proto \
    src/google/protobuf/unittest_lite_imports_nonlite.proto

$PROTOC -Icsharp/protos/extest --csharp_out=csharp/src/ProtocolBuffersLite.Test/TestProtos \
    csharp/protos/extest/unittest_extras_full.proto \
    csharp/protos/extest/unittest_extras_lite.proto

# Temporary fixup of test protos
sed -i -e 's/RepeatedFieldsGenerator\.Group/RepeatedFieldsGenerator.Types.Group/g' \
    csharp/src/ProtocolBuffers.Test/TestProtos/Unittest.cs \
    csharp/src/ProtocolBuffersLite.Test/TestProtos/Unittest.cs \
    csharp/src/ProtocolBuffersLite.Test/TestProtos/UnittestLite.cs

sed -i -e 's/DescriptorProtos\.Descriptor\./DescriptorProtos.DescriptorProtoFile./g' \
    csharp/src/ProtocolBuffers.Test/TestProtos/UnittestCustomOptions.cs

# AddressBook sample protos
$PROTOC -Iexamples --csharp_out=csharp/src/AddressBook \
    examples/addressbook.proto
