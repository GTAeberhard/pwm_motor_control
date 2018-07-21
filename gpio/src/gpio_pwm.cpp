#include <gpio_pwm.h>

GpioPwmPin::GpioPwmPin(const uint8_t pin_number)
    : pin_(pin_number), pwm_range_(255U)
{
}

void GpioPwmPin::WriteDutyCycle(const float duty_cycle)
{
    uint16_t pwm_value = std::round(pwm_range_ * duty_cycle);
    WriteDutyCycleToPin(pwm_value);
}

void GpioPwmPin::SetRange(const uint16_t range)
{
    pwm_range_ = range;
    SetRangeOnDevice(pwm_range_);
}
