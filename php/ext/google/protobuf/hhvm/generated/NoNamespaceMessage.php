<?php
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: proto/test_no_namespace.proto

use Google\Protobuf\Internal\GPBType;
use Google\Protobuf\Internal\RepeatedField;
use Google\Protobuf\Internal\GPBUtil;

/**
 * Generated from protobuf message <code>NoNamespaceMessage</code>
 */
class NoNamespaceMessage extends \Google\Protobuf\Internal\Message
{
    /**
     * Generated from protobuf field <code>int32 a = 1;</code>
     */
    private $a = 0;
    /**
     * Generated from protobuf field <code>.NoNamespaceMessage.NestedEnum b = 2;</code>
     */
    private $b = 0;
    /**
     * Generated from protobuf field <code>repeated .NoNamespaceMessage.NestedEnum c = 3;</code>
     */
    private $c;

    public function __construct() {
        \GPBMetadata\Proto\TestNoNamespace::initOnce();
        parent::__construct();
    }

    /**
     * Generated from protobuf field <code>int32 a = 1;</code>
     * @return int
     */
    public function getA()
    {
        return $this->a;
    }

    /**
     * Generated from protobuf field <code>int32 a = 1;</code>
     * @param int $var
     * @return $this
     */
    public function setA($var)
    {
        GPBUtil::checkInt32($var);
        $this->a = $var;

        return $this;
    }

    /**
     * Generated from protobuf field <code>.NoNamespaceMessage.NestedEnum b = 2;</code>
     * @return int
     */
    public function getB()
    {
        return $this->b;
    }

    /**
     * Generated from protobuf field <code>.NoNamespaceMessage.NestedEnum b = 2;</code>
     * @param int $var
     * @return $this
     */
    public function setB($var)
    {
        GPBUtil::checkEnum($var, \NoNamespaceMessage_NestedEnum::class);
        $this->b = $var;

        return $this;
    }

    /**
     * Generated from protobuf field <code>repeated .NoNamespaceMessage.NestedEnum c = 3;</code>
     * @return \Google\Protobuf\Internal\RepeatedField
     */
    public function getC()
    {
        return $this->c;
    }

    /**
     * Generated from protobuf field <code>repeated .NoNamespaceMessage.NestedEnum c = 3;</code>
     * @param int[]|\Google\Protobuf\Internal\RepeatedField $var
     * @return $this
     */
    public function setC($var)
    {
        $arr = GPBUtil::checkRepeatedField($var, \Google\Protobuf\Internal\GPBType::ENUM, \NoNamespaceMessage_NestedEnum::class);
        $this->c = $arr;

        return $this;
    }

}

