#ifndef PWM_CONTROL_FACTORY_H
#define PWM_CONTROL_FACTORY_H

#include <memory.h>

#include <motor_control.h>
#include <servo_control.h>

class PwmControlFactory
{
public:
    virtual std::unique_ptr<PwmMotorControl>
    CreateMotorControl(const std::uint8_t pin_pwm,
                       const std::uint8_t pin_direction_1,
                       const std::uint8_t pin_direction_2) = 0;

    virtual std::unique_ptr<PwmServoControl>
    CreateServoControl(const std::uint8_t pin_pwm,
                       const std::uint8_t pin_direction_1,
                       const std::uint8_t pin_direction_2) = 0;
};

#endif