#include <iostream>
#include <wiringPi.h>
#include <gpio.h>

class RaspberryPiGpioPin : public GpioPin
{
public:
    RaspberryPiGpioPin(uint8_t pin_number);

    ~RaspberryPiGpioPin() {}

private:
    void WriteToPin(const uint8_t value) override;
    void WriteHighToPin() override;
    void WriteLowToPin() override;
};
