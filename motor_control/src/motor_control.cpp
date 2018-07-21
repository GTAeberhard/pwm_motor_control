#include <motor_control.h>

PwmMotorControl::PwmMotorControl(std::unique_ptr<GpioPwmPin> pin_pwm,
                                 std::unique_ptr<GpioPin> pin_direction_1,
                                 std::unique_ptr<GpioPin> pin_direction_2)
    : pin_pwm_(std::move(pin_pwm)),
      pin_direction_1_(std::move(pin_direction_1)),
      pin_direction_2_(std::move(pin_direction_2))
{
}

void PwmMotorControl::SetSpeed(int8_t motor_speed)
{
    uint8_t corrected_motor_speed = std::abs(motor_speed);
    corrected_motor_speed = std::min(corrected_motor_speed, (uint8_t) 100U);

    if (motor_speed >= 0)
    {
        pin_direction_1_->WriteHigh();
        pin_direction_2_->WriteLow();
    }
    else
    {
        pin_direction_1_->WriteLow();
        pin_direction_2_->WriteHigh();
    }

    pin_pwm_->WriteDutyCycle(corrected_motor_speed / 100.0F);
}
