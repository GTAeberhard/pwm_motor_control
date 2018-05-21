#define protected public
#include "gpio.h"
#include "gpio_pwm.h"
#undef protected

class GpioPinMock : public GpioPin
{
public:
    GpioPinMock(const uint8_t pin_number) : GpioPin(pin_number) {}
    ~GpioPinMock() {}

    MOCK_METHOD1(WriteToPin, void(const uint8_t value));
    MOCK_METHOD0(WriteHighToPin, void());
    MOCK_METHOD0(WriteLowToPin, void());
};

class GpioPwmPinMock : public GpioPwmPin
{
public:
    GpioPwmPinMock(const uint8_t pin_number) : GpioPwmPin(pin_number) {}
    ~GpioPwmPinMock() {}

    MOCK_METHOD1(WriteDutyCycleToPin, void(const uint16_t duty_cycle));
    MOCK_METHOD1(SetRangeOnDevice, void(const uint16_t range));
};
