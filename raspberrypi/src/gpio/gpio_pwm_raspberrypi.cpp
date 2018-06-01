#include "gpio_pwm_raspberrypi.h"

RaspberryPiGpioPwmPin::RaspberryPiGpioPwmPin(uint8_t pin_number)
    : GpioPwmPin(pin_number)
{
    wiringPiSetupGpio();
    pinMode(pin_, PWM_OUTPUT);

}

void RaspberryPiGpioPwmPin::WriteDutyCycleToPin(const uint16_t value)
{
    pwmWrite(pin_, value);
}

void RaspberryPiGpioPwmPin::SetRangeOnDevice(const uint16_t range)
{
    pwmSetRange(range);
}
