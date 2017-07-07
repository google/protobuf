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
 * Generated from protobuf message <code>google.protobuf.EnumOptions</code>
 */
class EnumOptions extends \Google\Protobuf\Internal\Message
{
    /**
     * Set this option to true to allow mapping different tag names to the same
     * value.
     *
     * Generated from protobuf field <code>optional bool allow_alias = 2;</code>
     */
    private $allow_alias = false;
    private $has_allow_alias = false;
    /**
     * Is this enum deprecated?
     * Depending on the target platform, this can emit Deprecated annotations
     * for the enum, or it will be completely ignored; in the very least, this
     * is a formalization for deprecating enums.
     *
     * Generated from protobuf field <code>optional bool deprecated = 3 [default = false];</code>
     */
    private $deprecated = false;
    private $has_deprecated = false;
    /**
     * The parser stores options it doesn't recognize here. See above.
     *
     * Generated from protobuf field <code>repeated .google.protobuf.UninterpretedOption uninterpreted_option = 999;</code>
     */
    private $uninterpreted_option;
    private $has_uninterpreted_option = false;

    public function __construct() {
        \GPBMetadata\Google\Protobuf\Internal\Descriptor::initOnce();
        parent::__construct();
    }

    /**
     * Set this option to true to allow mapping different tag names to the same
     * value.
     *
     * Generated from protobuf field <code>optional bool allow_alias = 2;</code>
     * @return bool
     */
    public function getAllowAlias()
    {
        return $this->allow_alias;
    }

    /**
     * Set this option to true to allow mapping different tag names to the same
     * value.
     *
     * Generated from protobuf field <code>optional bool allow_alias = 2;</code>
     * @param bool $var
     * @return $this
     */
    public function setAllowAlias($var)
    {
        GPBUtil::checkBool($var);
        $this->allow_alias = $var;
        $this->has_allow_alias = true;

        return $this;
    }

    public function hasAllowAlias()
    {
        return $this->has_allow_alias;
    }

    /**
     * Is this enum deprecated?
     * Depending on the target platform, this can emit Deprecated annotations
     * for the enum, or it will be completely ignored; in the very least, this
     * is a formalization for deprecating enums.
     *
     * Generated from protobuf field <code>optional bool deprecated = 3 [default = false];</code>
     * @return bool
     */
    public function getDeprecated()
    {
        return $this->deprecated;
    }

    /**
     * Is this enum deprecated?
     * Depending on the target platform, this can emit Deprecated annotations
     * for the enum, or it will be completely ignored; in the very least, this
     * is a formalization for deprecating enums.
     *
     * Generated from protobuf field <code>optional bool deprecated = 3 [default = false];</code>
     * @param bool $var
     * @return $this
     */
    public function setDeprecated($var)
    {
        GPBUtil::checkBool($var);
        $this->deprecated = $var;
        $this->has_deprecated = true;

        return $this;
    }

    public function hasDeprecated()
    {
        return $this->has_deprecated;
    }

    /**
     * The parser stores options it doesn't recognize here. See above.
     *
     * Generated from protobuf field <code>repeated .google.protobuf.UninterpretedOption uninterpreted_option = 999;</code>
     * @return \Google\Protobuf\Internal\RepeatedField
     */
    public function getUninterpretedOption()
    {
        return $this->uninterpreted_option;
    }

    /**
     * The parser stores options it doesn't recognize here. See above.
     *
     * Generated from protobuf field <code>repeated .google.protobuf.UninterpretedOption uninterpreted_option = 999;</code>
     * @param \Google\Protobuf\Internal\UninterpretedOption[]|\Google\Protobuf\Internal\RepeatedField $var
     * @return $this
     */
    public function setUninterpretedOption(&$var)
    {
        $arr = GPBUtil::checkRepeatedField($var, GPBType::MESSAGE, \Google\Protobuf\Internal\UninterpretedOption::class);
        $this->uninterpreted_option = $arr;
        $this->has_uninterpreted_option = true;

        return $this;
    }

    public function hasUninterpretedOption()
    {
        return $this->has_uninterpreted_option;
    }

}

