#include <gpio.h>

GpioPin::GpioPin(const uint8_t pin_number)
    : pin_(pin_number)
{
}

void GpioPin::Write(const uint8_t value)
{
    WriteToPin(value);
}

void GpioPin::WriteHigh()
{
    WriteHighToPin();
}

void GpioPin::WriteLow()
{
    WriteLowToPin();
}
