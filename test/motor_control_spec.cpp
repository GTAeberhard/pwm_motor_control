#include "gtest/gtest.h"

#define private public
#include "motor_control.h"
#undef private

class PwmMotorControlTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        pin_output_pwm = 2U;
        pin_output_direction_1= 3U;
        pin_output_direction_2= 4U;

        motor_control = std::make_unique<PwmMotorControl>(pin_output_pwm,
                                                          pin_output_direction_1,
                                                          pin_output_direction_2);
    }

    uint8_t pin_output_pwm;
    uint8_t pin_output_direction_1;
    uint8_t pin_output_direction_2;

    std::unique_ptr<PwmMotorControl> motor_control;
};

TEST_F(PwmMotorControlTest, Initialize)
{
    EXPECT_EQ(motor_control->pin_pwm_, pin_output_pwm);
    EXPECT_EQ(motor_control->pin_direction_1_, pin_output_direction_1);
    EXPECT_EQ(motor_control->pin_direction_2_, pin_output_direction_2);
}

TEST_F(PwmMotorControlTest, ForwardPercentPower50)
{
    int8_t percent_motor_power = 50;

    motor_control->SetMotorSpeed(percent_motor_power);

    uint8_t expected_pwm_value = 128U;
    EXPECT_EQ(motor_control->pin_pwm_value_, expected_pwm_value);
    EXPECT_EQ(motor_control->pin_direction_1_value_, HIGH);
    EXPECT_EQ(motor_control->pin_direction_2_value_, LOW);
}


TEST_F(PwmMotorControlTest, BackwardPercentPower50)
{
    int8_t percent_motor_power = -50;

    motor_control->SetMotorSpeed(percent_motor_power);

    uint8_t expected_pwm_value = 128U;
    EXPECT_EQ(motor_control->pin_pwm_value_, expected_pwm_value);
    EXPECT_EQ(motor_control->pin_direction_1_value_, LOW);
    EXPECT_EQ(motor_control->pin_direction_2_value_, HIGH);
}

TEST_F(PwmMotorControlTest, LargerPositive100Percent)
{
    int8_t percent_motor_power = 110;

    motor_control->SetMotorSpeed(percent_motor_power);

    uint8_t expected_pwm_value = 255U;
    EXPECT_EQ(motor_control->pin_pwm_value_, expected_pwm_value);
    EXPECT_EQ(motor_control->pin_direction_1_value_, HIGH);
    EXPECT_EQ(motor_control->pin_direction_2_value_, LOW);
}

TEST_F(PwmMotorControlTest, LowerNegative100Percent)
{
    int8_t percent_motor_power = -110;

    motor_control->SetMotorSpeed(percent_motor_power);

    uint8_t expected_pwm_value = 255U;
    EXPECT_EQ(motor_control->pin_pwm_value_, expected_pwm_value);
    EXPECT_EQ(motor_control->pin_direction_1_value_, LOW);
    EXPECT_EQ(motor_control->pin_direction_2_value_, HIGH);
}
