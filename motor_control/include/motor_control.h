#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <cstdint>
#include <cmath>
#include <algorithm>
#include <memory>

#include <gpio.h>
#include <gpio_pwm.h>

const uint8_t HIGH = 255U;
const uint8_t LOW = 0U;

class PwmMotorControl {
public:
    PwmMotorControl(std::unique_ptr<GpioPwmPin> pin_pwm,
                    std::unique_ptr<GpioPin> pin_direction_1,
                    std::unique_ptr<GpioPin> pin_direction_2);

    void SetMotorSpeed(int8_t motor_speed);

private:
    std::unique_ptr<GpioPwmPin> pin_pwm_;
    std::unique_ptr<GpioPin> pin_direction_1_;
    std::unique_ptr<GpioPin> pin_direction_2_;

    uint8_t pin_pwm_value_;
    uint8_t pin_direction_1_value_;
    uint8_t pin_direction_2_value_;
};

#endif
