#include "gpio_raspberrypi.h"

RaspberryPiGpioPin::RaspberryPiGpioPin(uint8_t pin_number)
    : GpioPin(pin_number)
{
    wiringPiSetupGpio();
    pinMode(pin_, OUTPUT);
}

void RaspberryPiGpioPin::WriteToPin(const uint8_t value)
{
    analogWrite(pin_, value);
}

void RaspberryPiGpioPin::WriteHighToPin()
{
    digitalWrite(pin_, HIGH);
}

void RaspberryPiGpioPin::WriteLowToPin()
{
    digitalWrite(pin_, LOW);
}
