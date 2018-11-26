#include <servo_control.h>

PwmServoControl::PwmServoControl(std::unique_ptr<GpioPwmPin> pin_pwm,
                                 std::unique_ptr<GpioPin> pin_direction_1,
                                 std::unique_ptr<GpioPin> pin_direction_2)
    : pin_pwm_(std::move(pin_pwm)),
      pin_direction_1_(std::move(pin_direction_1)),
      pin_direction_2_(std::move(pin_direction_2))
{
}

void PwmServoControl::SetAngle(int8_t angle)
{
    uint8_t corrected_angle = std::abs(angle);
    corrected_angle = std::min(corrected_angle, (uint8_t) angle_max_);
    float percent_displacement = (float) corrected_angle / angle_max_;

    if (angle >= 0)
    {
        pin_direction_1_->WriteHigh();
        pin_direction_2_->WriteLow();
    }
    else
    {
        pin_direction_1_->WriteLow();
        pin_direction_2_->WriteHigh();
    }

    pin_pwm_->WriteDutyCycle(percent_displacement);
}
