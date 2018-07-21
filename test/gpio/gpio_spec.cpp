#include <gmock/gmock.h>

#define protected public
#include <gpio.h>
#undef protected

#include <gpio_mock.h>

class GpioPinTest : public ::testing::Test
{
public:
    virtual void SetUp()
    {
        device_pin_number = 2U;
        unit = std::make_unique<GpioPinMock>(device_pin_number);
    }

    uint8_t device_pin_number;
    std::unique_ptr<GpioPinMock> unit;
};

TEST_F(GpioPinTest, Initialize)
{
    EXPECT_EQ(unit->pin_, device_pin_number);
}

TEST_F(GpioPinTest, WriteAnalogOrPwmValue)
{
    uint8_t write_value = 105U;

    EXPECT_CALL(*unit, WriteToPin(write_value))
            .Times(1);

    unit->Write(write_value);
}

TEST_F(GpioPinTest, WriteHigh)
{
    EXPECT_CALL(*unit, WriteHighToPin())
            .Times(1);

    unit->WriteHigh();
}

TEST_F(GpioPinTest, WriteLow)
{
    EXPECT_CALL(*unit, WriteLowToPin())
            .Times(1);

    unit->WriteLow();
}
