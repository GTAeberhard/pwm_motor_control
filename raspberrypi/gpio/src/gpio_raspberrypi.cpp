#include <gpio_raspberrypi.h>

RaspberryPiGpioPin::RaspberryPiGpioPin(uint8_t pin_number)
    : GpioPin(pin_number)
{
    wiringPiSetup();
    pinMode(pin_, OUTPUT);
}

void RaspberryPiGpioPin::WriteToPin(const uint8_t value)
{
    analogWrite(pin_, value);
}

void RaspberryPiGpioPin::WriteHighToPin()
{
    digitalWrite(pin_, HIGH);
    std::cout << "Writing HIGH on pin " <<  (int) pin_ << std::endl;
}

void RaspberryPiGpioPin::WriteLowToPin()
{
    digitalWrite(pin_, LOW);
    std::cout << "Writing LOW on pin " <<  (int) pin_ << std::endl;
}
