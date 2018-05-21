#include <gmock/gmock.h>

#define protected public
#include "gpio_pwm.h"
#undef protected

#include "gpio_mock.h"

class GpioPwmPinTest : public ::testing::Test
{
public:
    virtual void SetUp()
    {
        device_pin_number = 2U;
        unit = std::make_unique<GpioPwmPinMock>(device_pin_number);
    }

    uint8_t device_pin_number;
    std::unique_ptr<GpioPwmPinMock> unit;
};

TEST_F(GpioPwmPinTest, InitializePinNumber)
{
    EXPECT_EQ(unit->pin_, device_pin_number);
}

TEST_F(GpioPwmPinTest, InitializeWithDefaultRangeOf255)
{
    uint16_t expected_default_pwm_range = 255U;
    EXPECT_EQ(unit->pwm_range_, expected_default_pwm_range);
}

TEST_F(GpioPwmPinTest, WriteDutyCycle50PercentWithDefaultRange)
{
    uint16_t expected_pin_value = 128U;
    EXPECT_CALL(*unit, WriteDutyCycleToPin(expected_pin_value)).Times(1);
    unit->WriteDutyCycle(0.5F);
}

TEST_F(GpioPwmPinTest, SetRangeOf1024)
{
    uint16_t expected_new_range = 1024U;
    EXPECT_CALL(*unit, SetRangeOnDevice(expected_new_range)).Times(1);
    unit->SetRange(expected_new_range);
    EXPECT_EQ(unit->pwm_range_, expected_new_range);
}

TEST_F(GpioPwmPinTest, WriteDutyCycle50PercentWithRangeOf1024)
{
    uint16_t new_range = 1024U;
    unit->SetRange(new_range);

    uint16_t expected_pin_value = 512U;
    EXPECT_CALL(*unit, WriteDutyCycleToPin(expected_pin_value)).Times(1);
    unit->WriteDutyCycle(0.5F);
}
