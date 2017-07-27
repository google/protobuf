<?php

require_once('generated/Descriptors/TestDescriptorsEnum.php');
require_once('generated/Descriptors/TestDescriptorsMessage.php');
require_once('test_base.php');
require_once('test_util.php');

use Google\Protobuf\DescriptorPool;
use Google\Protobuf\Internal\GPBLabel;
use Google\Protobuf\Internal\RepeatedField;
use Google\Protobuf\Internal\MapField;
use Google\Protobuf\Internal\GPBType;
use Descriptors\TestDescriptorsEnum;
use Descriptors\TestDescriptorsMessage;
use Descriptors\TestDescriptorsMessage_Sub;

class DescriptorsTest extends TestBase
{

    #########################################################
    # Test descriptor pool.
    #########################################################

    public function testDescriptorPool()
    {
        $pool = DescriptorPool::getGeneratedPool();

        $desc = $pool->getDescriptorByClassName(get_class(new TestDescriptorsMessage()));
        $this->assertInstanceOf('\Google\Protobuf\Descriptor', $desc);

        $enumDesc = $pool->getEnumDescriptorByClassName(get_class(new TestDescriptorsEnum()));
        $this->assertInstanceOf('\Google\Protobuf\EnumDescriptor', $enumDesc);
    }

    public function testDescriptorPoolIncorrectArgs()
    {
        $pool = DescriptorPool::getGeneratedPool();

        $desc = $pool->getDescriptorByClassName('NotAClass');
        $this->assertNull($desc);

        $desc = $pool->getDescriptorByClassName(get_class(new TestDescriptorsEnum()));
        $this->assertNull($desc);

        $enumDesc = $pool->getEnumDescriptorByClassName(get_class(new TestDescriptorsMessage()));
        $this->assertNull($enumDesc);
    }

    #########################################################
    # Test descriptor.
    #########################################################

    public function testDescriptor()
    {
        $pool = DescriptorPool::getGeneratedPool();
        $desc = $pool->getDescriptorByClassName(get_class(new TestDescriptorsMessage()));

        $this->assertSame('.descriptors.TestDescriptorsMessage', $desc->getFullName());

        $this->assertInstanceOf('\Google\Protobuf\FieldDescriptor', $desc->getField(0));
        $this->assertSame(7, $desc->getFieldCount());

        $this->assertInstanceOf('\Google\Protobuf\Descriptor', $desc->getNestedType(0));
        //  2 nested types: submessage and map entry
        $this->assertSame(2, $desc->getNestedTypeCount());

        $this->assertInstanceOf('\Google\Protobuf\EnumDescriptor', $desc->getEnumType(0));
        $this->assertSame(1, $desc->getEnumTypeCount());

        $this->assertInstanceOf('\Google\Protobuf\OneofDescriptor', $desc->getOneofDecl(0));
        $this->assertSame(1, $desc->getOneofDeclCount());
    }

    #########################################################
    # Test enum descriptor.
    #########################################################

    public function testEnumDescriptor()
    {
        // WARNINIG - we need to do this so that TestDescriptorsEnum is registered!!?
        new TestDescriptorsMessage();

        $pool = DescriptorPool::getGeneratedPool();

        $enumDesc = $pool->getEnumDescriptorByClassName(get_class(new TestDescriptorsEnum()));

        // Build map of enum values
        $enumDescMap = [];
        for ($i = 0; $i < $enumDesc->getValueCount(); $i++) {
            $enumValueDesc = $enumDesc->getValue($i);
            $this->assertInstanceOf('\Google\Protobuf\EnumValueDescriptor', $enumValueDesc);
            $enumDescMap[$enumValueDesc->getNumber()] = $enumValueDesc->getName();
        }

        $this->assertSame('ZERO', $enumDescMap[0]);
        $this->assertSame('ONE', $enumDescMap[1]);

        $this->assertSame(2, $enumDesc->getValueCount());
    }

    #########################################################
    # Test field descriptor.
    #########################################################

    public function testFieldDescriptor()
    {
        $pool = DescriptorPool::getGeneratedPool();
        $desc = $pool->getDescriptorByClassName(get_class(new TestDescriptorsMessage()));

        $fieldDescMap = $this->buildFieldMap($desc);

        // Optional int field
        $fieldDesc = $fieldDescMap[1];
        $this->assertSame('optional_int32', $fieldDesc->getName());
        $this->assertSame(1, $fieldDesc->getNumber());
        $this->assertSame(GPBLabel::OPTIONAL, $fieldDesc->getLabel());
        $this->assertSame(GPBType::INT32, $fieldDesc->getType());
        $this->assertFalse($fieldDesc->isMap());

        // Optional enum field
        $fieldDesc = $fieldDescMap[16];
        $this->assertSame('optional_enum', $fieldDesc->getName());
        $this->assertSame(16, $fieldDesc->getNumber());
        $this->assertSame(GPBLabel::OPTIONAL, $fieldDesc->getLabel());
        $this->assertSame(GPBType::ENUM, $fieldDesc->getType());
        $this->assertInstanceOf('\Google\Protobuf\EnumDescriptor', $fieldDesc->getEnumType());
        $this->assertFalse($fieldDesc->isMap());

        // Optional message field
        $fieldDesc = $fieldDescMap[17];
        $this->assertSame('optional_message', $fieldDesc->getName());
        $this->assertSame(17, $fieldDesc->getNumber());
        $this->assertSame(GPBLabel::OPTIONAL, $fieldDesc->getLabel());
        $this->assertSame(GPBType::MESSAGE, $fieldDesc->getType());
        $this->assertInstanceOf('\Google\Protobuf\Descriptor', $fieldDesc->getMessageType());
        $this->assertFalse($fieldDesc->isMap());

        // Repeated int field
        $fieldDesc = $fieldDescMap[31];
        $this->assertSame('repeated_int32', $fieldDesc->getName());
        $this->assertSame(31, $fieldDesc->getNumber());
        $this->assertSame(GPBLabel::REPEATED, $fieldDesc->getLabel());
        $this->assertSame(GPBType::INT32, $fieldDesc->getType());
        $this->assertFalse($fieldDesc->isMap());

        // Repeated message field
        $fieldDesc = $fieldDescMap[47];
        $this->assertSame('repeated_message', $fieldDesc->getName());
        $this->assertSame(47, $fieldDesc->getNumber());
        $this->assertSame(GPBLabel::REPEATED, $fieldDesc->getLabel());
        $this->assertSame(GPBType::MESSAGE, $fieldDesc->getType());
        $this->assertInstanceOf('\Google\Protobuf\Descriptor', $fieldDesc->getMessageType());
        $this->assertFalse($fieldDesc->isMap());

        // Oneof int field
        // Tested further in testOneofDescriptor()
        $fieldDesc = $fieldDescMap[51];
        $this->assertSame('oneof_int32', $fieldDesc->getName());
        $this->assertSame(51, $fieldDesc->getNumber());
        $this->assertSame(GPBLabel::OPTIONAL, $fieldDesc->getLabel());
        $this->assertSame(GPBType::INT32, $fieldDesc->getType());
        $this->assertFalse($fieldDesc->isMap());

        // Map int-enum field
        $fieldDesc = $fieldDescMap[71];
        $this->assertSame('map_int32_enum', $fieldDesc->getName());
        $this->assertSame(71, $fieldDesc->getNumber());
        $this->assertSame(GPBLabel::REPEATED, $fieldDesc->getLabel());
        $this->assertSame(GPBType::MESSAGE, $fieldDesc->getType());
        $this->assertTrue($fieldDesc->isMap());
        $mapDesc = $fieldDesc->getMessageType();
        $this->assertSame('.descriptors.TestDescriptorsMessage.MapInt32EnumEntry', $mapDesc->getFullName());
        $this->assertSame(GPBType::INT32, $mapDesc->getField(0)->getType());
        $this->assertSame(GPBType::ENUM, $mapDesc->getField(1)->getType());
    }

    /**
     * @expectedException \Exception
     */
    public function testFieldDescriptorEnumException()
    {
        $pool = DescriptorPool::getGeneratedPool();
        $desc = $pool->getDescriptorByClassName(get_class(new TestDescriptorsMessage()));
        $fieldDesc = $desc->getField(0);
        $fieldDesc->getEnumType();
    }

    /**
     * @expectedException \Exception
     */
    public function testFieldDescriptorMessageException()
    {
        $pool = DescriptorPool::getGeneratedPool();
        $desc = $pool->getDescriptorByClassName(get_class(new TestDescriptorsMessage()));
        $fieldDesc = $desc->getField(0);
        $fieldDesc->getMessageType();
    }

    #########################################################
    # Test oneof descriptor.
    #########################################################

    public function testOneofDescriptor()
    {
        $pool = DescriptorPool::getGeneratedPool();
        $desc = $pool->getDescriptorByClassName(get_class(new TestDescriptorsMessage()));

        $fieldDescMap = $this->buildFieldMap($desc);
        $fieldDesc = $fieldDescMap[51];

        $oneofDesc = $desc->getOneofDecl(0);

        $this->assertSame('my_oneof', $oneofDesc->getName());
        $fieldDescFromOneof = $oneofDesc->getField(0);
        $this->assertSame($fieldDesc, $fieldDescFromOneof);
        $this->assertSame(1, $oneofDesc->getFieldCount());
    }

    private function buildFieldMap($desc)
    {
        $fieldDescMap = [];
        for ($i = 0; $i < $desc->getFieldCount(); $i++) {
            $fieldDesc = $desc->getField($i);
            $fieldDescMap[$fieldDesc->getNumber()] = $fieldDesc;
        }
        return $fieldDescMap;
    }
}
