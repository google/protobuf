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
 * Describes an enum type.
 *
 * Generated from protobuf message <code>google.protobuf.EnumDescriptorProto</code>
 */
class EnumDescriptorProto extends \Google\Protobuf\Internal\Message
{
    /**
     * Generated from protobuf field <code>optional string name = 1;</code>
     */
    private $name = '';
    private $has_name = false;
    /**
     * Generated from protobuf field <code>repeated .google.protobuf.EnumValueDescriptorProto value = 2;</code>
     */
    private $value;
    private $has_value = false;
    /**
     * Generated from protobuf field <code>optional .google.protobuf.EnumOptions options = 3;</code>
     */
    private $options = null;
    private $has_options = false;

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
     * Generated from protobuf field <code>repeated .google.protobuf.EnumValueDescriptorProto value = 2;</code>
     * @return \Google\Protobuf\Internal\RepeatedField
     */
    public function getValue()
    {
        return $this->value;
    }

    /**
     * Generated from protobuf field <code>repeated .google.protobuf.EnumValueDescriptorProto value = 2;</code>
     * @param \Google\Protobuf\Internal\EnumValueDescriptorProto[]|\Google\Protobuf\Internal\RepeatedField $var
     * @return $this
     */
    public function setValue($var)
    {
        $arr = GPBUtil::checkRepeatedField($var, \Google\Protobuf\Internal\GPBType::MESSAGE, \Google\Protobuf\Internal\EnumValueDescriptorProto::class);
        $this->value = $arr;
        $this->has_value = true;

        return $this;
    }

    public function hasValue()
    {
        return $this->has_value;
    }

    /**
     * Generated from protobuf field <code>optional .google.protobuf.EnumOptions options = 3;</code>
     * @return \Google\Protobuf\Internal\EnumOptions
     */
    public function getOptions()
    {
        return $this->options;
    }

    /**
     * Generated from protobuf field <code>optional .google.protobuf.EnumOptions options = 3;</code>
     * @param \Google\Protobuf\Internal\EnumOptions $var
     * @return $this
     */
    public function setOptions(\Google\Protobuf\Internal\EnumOptions $var = null)
    {
        GPBUtil::checkMessage($var, \Google\Protobuf\Internal\EnumOptions::class);
        $this->options = $var;
        $this->has_options = true;

        return $this;
    }

    public function hasOptions()
    {
        return $this->has_options;
    }

}

