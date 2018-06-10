#ifndef GPIO_PWM_H
#define GPIO_PWM_H

#include <cstdint>
#include <algorithm>
#include <cmath>

class GpioPwmPin
{
public:
    GpioPwmPin(const uint8_t pin_number);

    virtual ~GpioPwmPin() {}

    void WriteDutyCycle(const float duty_cycle);
    void SetRange(const uint16_t range);

protected:
    uint8_t pin_;
    uint16_t pwm_range_;

private:
    virtual void WriteDutyCycleToPin(const uint16_t value) = 0;
    virtual void SetRangeOnDevice(const uint16_t range) = 0;
};

#endif
