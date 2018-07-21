#include <gpio_pwm_raspberrypi.h>

RaspberryPiGpioPwmPin::RaspberryPiGpioPwmPin(uint8_t pin_number)
    : GpioPwmPin(pin_number)
{
    wiringPiSetup();
    pinMode(pin_, PWM_OUTPUT);

}

void RaspberryPiGpioPwmPin::WriteDutyCycleToPin(const uint16_t value)
{
    pwmWrite(pin_, value);
    std::cout << "Writing PWM on pin " << (int) pin_ << " with value " << value << std::endl;
}

void RaspberryPiGpioPwmPin::SetRangeOnDevice(const uint16_t range)
{
    pwmSetRange(range);
}
