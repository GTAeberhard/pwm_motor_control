#include <wiringpi>
#include "gpio.h"

class RaspberryPiGpioPwmPin : public GpioPin
{
public:
    RaspberryPiGpioPwmPin(uint8_t pin_numner);

    ~GpioPwmPin() {}

private:
    void WriteToPin(const uint8_t value);
    void WriteHighToPin();
    void WriteLowToPin();
};
