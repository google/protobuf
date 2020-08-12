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
 * Describes a method of a service.
 *
 * Generated from protobuf message <code>google.protobuf.MethodDescriptorProto</code>
 */
class MethodDescriptorProto extends \Google\Protobuf\Internal\Message
{
    /**
     * Generated from protobuf field <code>optional string name = 1;</code>
     */
    protected $name = null;
    private $has_name = false;
    /**
     * Input and output type names.  These are resolved in the same way as
     * FieldDescriptorProto.type_name, but must refer to a message type.
     *
     * Generated from protobuf field <code>optional string input_type = 2;</code>
     */
    protected $input_type = null;
    private $has_input_type = false;
    /**
     * Generated from protobuf field <code>optional string output_type = 3;</code>
     */
    protected $output_type = null;
    private $has_output_type = false;
    /**
     * Generated from protobuf field <code>optional .google.protobuf.MethodOptions options = 4;</code>
     */
    protected $options = null;
    private $has_options = false;
    /**
     * Identifies if client streams multiple client messages
     *
     * Generated from protobuf field <code>optional bool client_streaming = 5 [default = false];</code>
     */
    protected $client_streaming = null;
    private $has_client_streaming = false;
    /**
     * Identifies if server streams multiple server messages
     *
     * Generated from protobuf field <code>optional bool server_streaming = 6 [default = false];</code>
     */
    protected $server_streaming = null;
    private $has_server_streaming = false;

    /**
     * Constructor.
     *
     * @param array $data {
     *     Optional. Data for populating the Message object.
     *
     *     @type string $name
     *     @type string $input_type
     *           Input and output type names.  These are resolved in the same way as
     *           FieldDescriptorProto.type_name, but must refer to a message type.
     *     @type string $output_type
     *     @type \Google\Protobuf\Internal\MethodOptions $options
     *     @type bool $client_streaming
     *           Identifies if client streams multiple client messages
     *     @type bool $server_streaming
     *           Identifies if server streams multiple server messages
     * }
     */
    public function __construct($data = NULL) {
        \GPBMetadata\Google\Protobuf\Internal\Descriptor::initOnce();
        parent::__construct($data);
    }

    /**
     * Generated from protobuf field <code>optional string name = 1;</code>
     * @return string
     */
    public function getName()
    {
        return isset($this->name) ? $this->name : '';
    }

    public function hasName()
    {
        return isset($this->name);
    }

    public function clearName()
    {
        unset($this->name);
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
     * Input and output type names.  These are resolved in the same way as
     * FieldDescriptorProto.type_name, but must refer to a message type.
     *
     * Generated from protobuf field <code>optional string input_type = 2;</code>
     * @return string
     */
    public function getInputType()
    {
        return isset($this->input_type) ? $this->input_type : '';
    }

    public function hasInputType()
    {
        return isset($this->input_type);
    }

    public function clearInputType()
    {
        unset($this->input_type);
    }

    /**
     * Input and output type names.  These are resolved in the same way as
     * FieldDescriptorProto.type_name, but must refer to a message type.
     *
     * Generated from protobuf field <code>optional string input_type = 2;</code>
     * @param string $var
     * @return $this
     */
    public function setInputType($var)
    {
        GPBUtil::checkString($var, True);
        $this->input_type = $var;
        $this->has_input_type = true;

        return $this;
    }

    public function hasInputType()
    {
        return $this->has_input_type;
    }

    /**
     * Generated from protobuf field <code>optional string output_type = 3;</code>
     * @return string
     */
    public function getOutputType()
    {
        return isset($this->output_type) ? $this->output_type : '';
    }

    public function hasOutputType()
    {
        return isset($this->output_type);
    }

    public function clearOutputType()
    {
        unset($this->output_type);
    }

    /**
     * Generated from protobuf field <code>optional string output_type = 3;</code>
     * @param string $var
     * @return $this
     */
    public function setOutputType($var)
    {
        GPBUtil::checkString($var, True);
        $this->output_type = $var;
        $this->has_output_type = true;

        return $this;
    }

    public function hasOutputType()
    {
        return $this->has_output_type;
    }

    /**
     * Generated from protobuf field <code>optional .google.protobuf.MethodOptions options = 4;</code>
     * @return \Google\Protobuf\Internal\MethodOptions
     */
    public function getOptions()
    {
        return isset($this->options) ? $this->options : null;
    }

    public function hasOptions()
    {
        return isset($this->options);
    }

    public function clearOptions()
    {
        unset($this->options);
    }

    /**
     * Generated from protobuf field <code>optional .google.protobuf.MethodOptions options = 4;</code>
     * @param \Google\Protobuf\Internal\MethodOptions $var
     * @return $this
     */
    public function setOptions($var)
    {
        GPBUtil::checkMessage($var, \Google\Protobuf\Internal\MethodOptions::class);
        $this->options = $var;
        $this->has_options = true;

        return $this;
    }

    public function hasOptions()
    {
        return $this->has_options;
    }

    /**
     * Identifies if client streams multiple client messages
     *
     * Generated from protobuf field <code>optional bool client_streaming = 5 [default = false];</code>
     * @return bool
     */
    public function getClientStreaming()
    {
        return isset($this->client_streaming) ? $this->client_streaming : false;
    }

    public function hasClientStreaming()
    {
        return isset($this->client_streaming);
    }

    public function clearClientStreaming()
    {
        unset($this->client_streaming);
    }

    /**
     * Identifies if client streams multiple client messages
     *
     * Generated from protobuf field <code>optional bool client_streaming = 5 [default = false];</code>
     * @param bool $var
     * @return $this
     */
    public function setClientStreaming($var)
    {
        GPBUtil::checkBool($var);
        $this->client_streaming = $var;
        $this->has_client_streaming = true;

        return $this;
    }

    public function hasClientStreaming()
    {
        return $this->has_client_streaming;
    }

    /**
     * Identifies if server streams multiple server messages
     *
     * Generated from protobuf field <code>optional bool server_streaming = 6 [default = false];</code>
     * @return bool
     */
    public function getServerStreaming()
    {
        return isset($this->server_streaming) ? $this->server_streaming : false;
    }

    public function hasServerStreaming()
    {
        return isset($this->server_streaming);
    }

    public function clearServerStreaming()
    {
        unset($this->server_streaming);
    }

    /**
     * Identifies if server streams multiple server messages
     *
     * Generated from protobuf field <code>optional bool server_streaming = 6 [default = false];</code>
     * @param bool $var
     * @return $this
     */
    public function setServerStreaming($var)
    {
        GPBUtil::checkBool($var);
        $this->server_streaming = $var;
        $this->has_server_streaming = true;

        return $this;
    }

    public function hasServerStreaming()
    {
        return $this->has_server_streaming;
    }

}

