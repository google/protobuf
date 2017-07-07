<?php
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: google/protobuf/descriptor.proto

namespace Google\Protobuf\Internal;

use Google\Protobuf\Internal\GPBType;
use Google\Protobuf\Internal\GPBWire;
use Google\Protobuf\Internal\RepeatedField;
use Google\Protobuf\Internal\InputStream;
use Google\Protobuf\Internal\GPBUtil;

/**
 * Describes a message type.
 *
 * Generated from protobuf message <code>google.protobuf.DescriptorProto</code>
 */
class DescriptorProto extends \Google\Protobuf\Internal\Message
{
    /**
     * Generated from protobuf field <code>optional string name = 1;</code>
     */
    private $name = '';
    private $has_name = false;
    /**
     * Generated from protobuf field <code>repeated .google.protobuf.FieldDescriptorProto field = 2;</code>
     */
    private $field;
    private $has_field = false;
    /**
     * Generated from protobuf field <code>repeated .google.protobuf.FieldDescriptorProto extension = 6;</code>
     */
    private $extension;
    private $has_extension = false;
    /**
     * Generated from protobuf field <code>repeated .google.protobuf.DescriptorProto nested_type = 3;</code>
     */
    private $nested_type;
    private $has_nested_type = false;
    /**
     * Generated from protobuf field <code>repeated .google.protobuf.EnumDescriptorProto enum_type = 4;</code>
     */
    private $enum_type;
    private $has_enum_type = false;
    /**
     * Generated from protobuf field <code>repeated .google.protobuf.DescriptorProto.ExtensionRange extension_range = 5;</code>
     */
    private $extension_range;
    private $has_extension_range = false;
    /**
     * Generated from protobuf field <code>repeated .google.protobuf.OneofDescriptorProto oneof_decl = 8;</code>
     */
    private $oneof_decl;
    private $has_oneof_decl = false;
    /**
     * Generated from protobuf field <code>optional .google.protobuf.MessageOptions options = 7;</code>
     */
    private $options = null;
    private $has_options = false;
    /**
     * Generated from protobuf field <code>repeated .google.protobuf.DescriptorProto.ReservedRange reserved_range = 9;</code>
     */
    private $reserved_range;
    private $has_reserved_range = false;
    /**
     * Reserved field names, which may not be used by fields in the same message.
     * A given name may only be reserved once.
     *
     * Generated from protobuf field <code>repeated string reserved_name = 10;</code>
     */
    private $reserved_name;
    private $has_reserved_name = false;

    public function __construct() {
        \GPBMetadata\Google\Protobuf\Internal\Descriptor::initOnce();
        parent::__construct();
    }

    /**
     * Generated from protobuf field <code>optional string name = 1;</code>
     * @return string
     */
    public function getName()
    {
        return $this->name;
    }

    /**
     * Generated from protobuf field <code>optional string name = 1;</code>
     * @param string $var
     * @return $this
     */
    public function setName($var)
    {
        GPBUtil::checkString($var, True);
        $this->name = $var;
        $this->has_name = true;

        return $this;
    }

    public function hasName()
    {
        return $this->has_name;
    }

    /**
     * Generated from protobuf field <code>repeated .google.protobuf.FieldDescriptorProto field = 2;</code>
     * @return \Google\Protobuf\Internal\RepeatedField
     */
    public function getField()
    {
        return $this->field;
    }

    /**
     * Generated from protobuf field <code>repeated .google.protobuf.FieldDescriptorProto field = 2;</code>
     * @param \Google\Protobuf\Internal\FieldDescriptorProto[]|\Google\Protobuf\Internal\RepeatedField $var
     * @return $this
     */
    public function setField($var)
    {
        $arr = GPBUtil::checkRepeatedField($var, \Google\Protobuf\Internal\GPBType::MESSAGE, \Google\Protobuf\Internal\FieldDescriptorProto::class);
        $this->field = $arr;
        $this->has_field = true;

        return $this;
    }

    public function hasField()
    {
        return $this->has_field;
    }

    /**
     * Generated from protobuf field <code>repeated .google.protobuf.FieldDescriptorProto extension = 6;</code>
     * @return \Google\Protobuf\Internal\RepeatedField
     */
    public function getExtension()
    {
        return $this->extension;
    }

    /**
     * Generated from protobuf field <code>repeated .google.protobuf.FieldDescriptorProto extension = 6;</code>
     * @param \Google\Protobuf\Internal\FieldDescriptorProto[]|\Google\Protobuf\Internal\RepeatedField $var
     * @return $this
     */
    public function setExtension($var)
    {
        $arr = GPBUtil::checkRepeatedField($var, \Google\Protobuf\Internal\GPBType::MESSAGE, \Google\Protobuf\Internal\FieldDescriptorProto::class);
        $this->extension = $arr;
        $this->has_extension = true;

        return $this;
    }

    public function hasExtension()
    {
        return $this->has_extension;
    }

    /**
     * Generated from protobuf field <code>repeated .google.protobuf.DescriptorProto nested_type = 3;</code>
     * @return \Google\Protobuf\Internal\RepeatedField
     */
    public function getNestedType()
    {
        return $this->nested_type;
    }

    /**
     * Generated from protobuf field <code>repeated .google.protobuf.DescriptorProto nested_type = 3;</code>
     * @param \Google\Protobuf\Internal\DescriptorProto[]|\Google\Protobuf\Internal\RepeatedField $var
     * @return $this
     */
    public function setNestedType($var)
    {
        $arr = GPBUtil::checkRepeatedField($var, \Google\Protobuf\Internal\GPBType::MESSAGE, \Google\Protobuf\Internal\DescriptorProto::class);
        $this->nested_type = $arr;
        $this->has_nested_type = true;

        return $this;
    }

    public function hasNestedType()
    {
        return $this->has_nested_type;
    }

    /**
     * Generated from protobuf field <code>repeated .google.protobuf.EnumDescriptorProto enum_type = 4;</code>
     * @return \Google\Protobuf\Internal\RepeatedField
     */
    public function getEnumType()
    {
        return $this->enum_type;
    }

    /**
     * Generated from protobuf field <code>repeated .google.protobuf.EnumDescriptorProto enum_type = 4;</code>
     * @param \Google\Protobuf\Internal\EnumDescriptorProto[]|\Google\Protobuf\Internal\RepeatedField $var
     * @return $this
     */
    public function setEnumType($var)
    {
        $arr = GPBUtil::checkRepeatedField($var, \Google\Protobuf\Internal\GPBType::MESSAGE, \Google\Protobuf\Internal\EnumDescriptorProto::class);
        $this->enum_type = $arr;
        $this->has_enum_type = true;

        return $this;
    }

    public function hasEnumType()
    {
        return $this->has_enum_type;
    }

    /**
     * Generated from protobuf field <code>repeated .google.protobuf.DescriptorProto.ExtensionRange extension_range = 5;</code>
     * @return \Google\Protobuf\Internal\RepeatedField
     */
    public function getExtensionRange()
    {
        return $this->extension_range;
    }

    /**
     * Generated from protobuf field <code>repeated .google.protobuf.DescriptorProto.ExtensionRange extension_range = 5;</code>
     * @param \Google\Protobuf\Internal\DescriptorProto_ExtensionRange[]|\Google\Protobuf\Internal\RepeatedField $var
     * @return $this
     */
    public function setExtensionRange($var)
    {
        $arr = GPBUtil::checkRepeatedField($var, \Google\Protobuf\Internal\GPBType::MESSAGE, \Google\Protobuf\Internal\DescriptorProto_ExtensionRange::class);
        $this->extension_range = $arr;
        $this->has_extension_range = true;

        return $this;
    }

    public function hasExtensionRange()
    {
        return $this->has_extension_range;
    }

    /**
     * Generated from protobuf field <code>repeated .google.protobuf.OneofDescriptorProto oneof_decl = 8;</code>
     * @return \Google\Protobuf\Internal\RepeatedField
     */
    public function getOneofDecl()
    {
        return $this->oneof_decl;
    }

    /**
     * Generated from protobuf field <code>repeated .google.protobuf.OneofDescriptorProto oneof_decl = 8;</code>
     * @param \Google\Protobuf\Internal\OneofDescriptorProto[]|\Google\Protobuf\Internal\RepeatedField $var
     * @return $this
     */
    public function setOneofDecl($var)
    {
        $arr = GPBUtil::checkRepeatedField($var, \Google\Protobuf\Internal\GPBType::MESSAGE, \Google\Protobuf\Internal\OneofDescriptorProto::class);
        $this->oneof_decl = $arr;
        $this->has_oneof_decl = true;

        return $this;
    }

    public function hasOneofDecl()
    {
        return $this->has_oneof_decl;
    }

    /**
     * Generated from protobuf field <code>optional .google.protobuf.MessageOptions options = 7;</code>
     * @return \Google\Protobuf\Internal\MessageOptions
     */
    public function getOptions()
    {
        return $this->options;
    }

    /**
     * Generated from protobuf field <code>optional .google.protobuf.MessageOptions options = 7;</code>
     * @param \Google\Protobuf\Internal\MessageOptions $var
     * @return $this
     */
    public function setOptions(\Google\Protobuf\Internal\MessageOptions $var = null)
    {
        GPBUtil::checkMessage($var, \Google\Protobuf\Internal\MessageOptions::class);
        $this->options = $var;
        $this->has_options = true;

        return $this;
    }

    public function hasOptions()
    {
        return $this->has_options;
    }

    /**
     * Generated from protobuf field <code>repeated .google.protobuf.DescriptorProto.ReservedRange reserved_range = 9;</code>
     * @return \Google\Protobuf\Internal\RepeatedField
     */
    public function getReservedRange()
    {
        return $this->reserved_range;
    }

    /**
     * Generated from protobuf field <code>repeated .google.protobuf.DescriptorProto.ReservedRange reserved_range = 9;</code>
     * @param \Google\Protobuf\Internal\DescriptorProto_ReservedRange[]|\Google\Protobuf\Internal\RepeatedField $var
     * @return $this
     */
    public function setReservedRange($var)
    {
        $arr = GPBUtil::checkRepeatedField($var, \Google\Protobuf\Internal\GPBType::MESSAGE, \Google\Protobuf\Internal\DescriptorProto_ReservedRange::class);
        $this->reserved_range = $arr;
        $this->has_reserved_range = true;

        return $this;
    }

    public function hasReservedRange()
    {
        return $this->has_reserved_range;
    }

    /**
     * Reserved field names, which may not be used by fields in the same message.
     * A given name may only be reserved once.
     *
     * Generated from protobuf field <code>repeated string reserved_name = 10;</code>
     * @return \Google\Protobuf\Internal\RepeatedField
     */
    public function getReservedName()
    {
        return $this->reserved_name;
    }

    /**
     * Reserved field names, which may not be used by fields in the same message.
     * A given name may only be reserved once.
     *
     * Generated from protobuf field <code>repeated string reserved_name = 10;</code>
     * @param string[]|\Google\Protobuf\Internal\RepeatedField $var
     * @return $this
     */
    public function setReservedName($var)
    {
        $arr = GPBUtil::checkRepeatedField($var, \Google\Protobuf\Internal\GPBType::STRING);
        $this->reserved_name = $arr;
        $this->has_reserved_name = true;

        return $this;
    }

    public function hasReservedName()
    {
        return $this->has_reserved_name;
    }

}

