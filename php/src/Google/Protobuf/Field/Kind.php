<?php
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: google/protobuf/type.proto

namespace Google\Protobuf\Field;

use Google\Protobuf\Internal\EnumTrait;

/**
 * Basic field types.
 *
 * Protobuf type <code>google.protobuf.Field.Kind</code>
 */
class Kind
{
    use EnumTrait;

    /**
     * Field type unknown.
     *
     * Generated from protobuf enum <code>TYPE_UNKNOWN = 0;</code>
     */
    const TYPE_UNKNOWN = 0;
    /**
     * Field type double.
     *
     * Generated from protobuf enum <code>TYPE_DOUBLE = 1;</code>
     */
    const TYPE_DOUBLE = 1;
    /**
     * Field type float.
     *
     * Generated from protobuf enum <code>TYPE_FLOAT = 2;</code>
     */
    const TYPE_FLOAT = 2;
    /**
     * Field type int64.
     *
     * Generated from protobuf enum <code>TYPE_INT64 = 3;</code>
     */
    const TYPE_INT64 = 3;
    /**
     * Field type uint64.
     *
     * Generated from protobuf enum <code>TYPE_UINT64 = 4;</code>
     */
    const TYPE_UINT64 = 4;
    /**
     * Field type int32.
     *
     * Generated from protobuf enum <code>TYPE_INT32 = 5;</code>
     */
    const TYPE_INT32 = 5;
    /**
     * Field type fixed64.
     *
     * Generated from protobuf enum <code>TYPE_FIXED64 = 6;</code>
     */
    const TYPE_FIXED64 = 6;
    /**
     * Field type fixed32.
     *
     * Generated from protobuf enum <code>TYPE_FIXED32 = 7;</code>
     */
    const TYPE_FIXED32 = 7;
    /**
     * Field type bool.
     *
     * Generated from protobuf enum <code>TYPE_BOOL = 8;</code>
     */
    const TYPE_BOOL = 8;
    /**
     * Field type string.
     *
     * Generated from protobuf enum <code>TYPE_STRING = 9;</code>
     */
    const TYPE_STRING = 9;
    /**
     * Field type group. Proto2 syntax only, and deprecated.
     *
     * Generated from protobuf enum <code>TYPE_GROUP = 10;</code>
     */
    const TYPE_GROUP = 10;
    /**
     * Field type message.
     *
     * Generated from protobuf enum <code>TYPE_MESSAGE = 11;</code>
     */
    const TYPE_MESSAGE = 11;
    /**
     * Field type bytes.
     *
     * Generated from protobuf enum <code>TYPE_BYTES = 12;</code>
     */
    const TYPE_BYTES = 12;
    /**
     * Field type uint32.
     *
     * Generated from protobuf enum <code>TYPE_UINT32 = 13;</code>
     */
    const TYPE_UINT32 = 13;
    /**
     * Field type enum.
     *
     * Generated from protobuf enum <code>TYPE_ENUM = 14;</code>
     */
    const TYPE_ENUM = 14;
    /**
     * Field type sfixed32.
     *
     * Generated from protobuf enum <code>TYPE_SFIXED32 = 15;</code>
     */
    const TYPE_SFIXED32 = 15;
    /**
     * Field type sfixed64.
     *
     * Generated from protobuf enum <code>TYPE_SFIXED64 = 16;</code>
     */
    const TYPE_SFIXED64 = 16;
    /**
     * Field type sint32.
     *
     * Generated from protobuf enum <code>TYPE_SINT32 = 17;</code>
     */
    const TYPE_SINT32 = 17;
    /**
     * Field type sint64.
     *
     * Generated from protobuf enum <code>TYPE_SINT64 = 18;</code>
     */
    const TYPE_SINT64 = 18;

    private static $valueToName = [
        self::TYPE_UNKNOWN => 'TYPE_UNKNOWN',
        self::TYPE_DOUBLE => 'TYPE_DOUBLE',
        self::TYPE_FLOAT => 'TYPE_FLOAT',
        self::TYPE_INT64 => 'TYPE_INT64',
        self::TYPE_UINT64 => 'TYPE_UINT64',
        self::TYPE_INT32 => 'TYPE_INT32',
        self::TYPE_FIXED64 => 'TYPE_FIXED64',
        self::TYPE_FIXED32 => 'TYPE_FIXED32',
        self::TYPE_BOOL => 'TYPE_BOOL',
        self::TYPE_STRING => 'TYPE_STRING',
        self::TYPE_GROUP => 'TYPE_GROUP',
        self::TYPE_MESSAGE => 'TYPE_MESSAGE',
        self::TYPE_BYTES => 'TYPE_BYTES',
        self::TYPE_UINT32 => 'TYPE_UINT32',
        self::TYPE_ENUM => 'TYPE_ENUM',
        self::TYPE_SFIXED32 => 'TYPE_SFIXED32',
        self::TYPE_SFIXED64 => 'TYPE_SFIXED64',
        self::TYPE_SINT32 => 'TYPE_SINT32',
        self::TYPE_SINT64 => 'TYPE_SINT64',
    ];
}

// Adding a class alias for backwards compatibility with the previous class name.
class_alias(Kind::class, \Google\Protobuf\Field_Kind::class);

