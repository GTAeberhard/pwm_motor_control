#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H

#include <cstdint>
#include <cmath>
#include <algorithm>
#include <memory>

#include <gpio.h>
#include <gpio_pwm.h>

class PwmServoControl
{
public:
    PwmServoControl(std::unique_ptr<GpioPwmPin> pin_pwm,
                    std::unique_ptr<GpioPin> pin_direction_1,
                    std::unique_ptr<GpioPin> pin_direction_2);

    void SetAngle(int8_t angle);

private:
    std::unique_ptr<GpioPwmPin> pin_pwm_;
    std::unique_ptr<GpioPin> pin_direction_1_;
    std::unique_ptr<GpioPin> pin_direction_2_;

    uint8_t pin_pwm_value_;
    uint8_t pin_direction_1_value_;
    uint8_t pin_direction_2_value_;

    const float angle_max_{90.0F};
};

#endif
