#include <iostream>
#include <wiringPi.h>
#include <gpio_pwm.h>

class RaspberryPiGpioPwmPin : public GpioPwmPin
{
public:
    RaspberryPiGpioPwmPin(uint8_t pin_number);

    ~RaspberryPiGpioPwmPin() {}

private:
    void WriteDutyCycleToPin(const uint16_t value) override;
    void SetRangeOnDevice(const uint16_t range) override;
};
