#include "gpio_pwm_raspberrypi.h"

RaspberryPiGpioPwmPin::RaspberryPiGpioPwmPin(uint8_t pin_numner)
    : GpioPin(pin_numner)
{
    wiringPiSetupGpio();
}

void RaspberryPiGpioPwmPin::WriteToPin(const uint8_t value)
{
    pwmWrite(pin_, value);
}

void RaspberryPiGpioPwmPin::WriteHighToPin()
{
    pwmWrite(pin_, 1024);
}

void RaspberryPiGpioPwmPin::WriteLowToPin()
{
    pwmWrite(pin_, 0);
}
