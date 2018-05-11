#include "motor_control.h"

PwmMotorControl::PwmMotorControl(uint8_t pin_pwm, uint8_t pin_direction_1, uint8_t pin_direction_2)
    : pin_pwm_(pin_pwm), pin_direction_1_(pin_direction_1), pin_direction_2_(pin_direction_2)
{
}

void PwmMotorControl::SetMotorSpeed(int8_t motor_speed)
{
    uint8_t corrected_motor_speed = std::abs(motor_speed);
    corrected_motor_speed = std::min(corrected_motor_speed, (uint8_t) 100U);
    pin_pwm_value_ = std::round(HIGH * (corrected_motor_speed / 100.0F));
    pin_pwm_value_ = std::min(pin_pwm_value_, HIGH);

    if (motor_speed >= 0)
    {
        pin_direction_1_value_ = HIGH;
        pin_direction_2_value_ = LOW;
    }
    else
    {
        pin_direction_1_value_ = LOW;
        pin_direction_2_value_ = HIGH;
    }
}
