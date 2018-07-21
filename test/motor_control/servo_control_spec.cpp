#include <gmock/gmock.h>

#define private public
#define protected public
#include <servo_control.h>
#undef protected
#undef private

#include <mock_control_factory.h>
#include <gpio_mock.h>

class PwmServoControlTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        pin_output_pwm = 2U;
        pin_output_direction_1= 3U;
        pin_output_direction_2= 4U;

        MockPwmControlFactory factory;
        servo_control = factory.CreateServoControl(pin_output_pwm,
                                                   pin_output_direction_1,
                                                   pin_output_direction_2);
        
        pin_output_pwm_raw_ptr_ = dynamic_cast<GpioPwmPinMock*>(servo_control->pin_pwm_.get());
        pin_output_direction_1_raw_ptr_ = dynamic_cast<GpioPinMock*>(servo_control->pin_direction_1_.get());
        pin_output_direction_2_raw_ptr_ = dynamic_cast<GpioPinMock*>(servo_control->pin_direction_2_.get());
    }

    uint8_t pin_output_pwm;
    uint8_t pin_output_direction_1;
    uint8_t pin_output_direction_2;

    std::unique_ptr<PwmServoControl> servo_control;

    GpioPwmPinMock* pin_output_pwm_raw_ptr_;
    GpioPinMock* pin_output_direction_1_raw_ptr_;
    GpioPinMock* pin_output_direction_2_raw_ptr_;
};

TEST_F(PwmServoControlTest, Initialize)
{
    EXPECT_EQ(servo_control->pin_pwm_->pin_, pin_output_pwm);
    EXPECT_EQ(servo_control->pin_direction_1_->pin_, pin_output_direction_1);
    EXPECT_EQ(servo_control->pin_direction_2_->pin_, pin_output_direction_2);
}

TEST_F(PwmServoControlTest, Angle_0)
{
    uint8_t expected_pwm_value = 0U;
    EXPECT_CALL(*pin_output_pwm_raw_ptr_, WriteDutyCycleToPin(expected_pwm_value)).Times(1);
    EXPECT_CALL(*pin_output_direction_1_raw_ptr_, WriteHighToPin()).Times(1);
    EXPECT_CALL(*pin_output_direction_2_raw_ptr_, WriteLowToPin()).Times(1);

    int8_t desired_angle = 0;
    servo_control->SetAngle(desired_angle);
}

TEST_F(PwmServoControlTest, AngleMaxPositive)
{
    uint8_t expected_pwm_value = 255U;
    EXPECT_CALL(*pin_output_pwm_raw_ptr_, WriteDutyCycleToPin(expected_pwm_value)).Times(1);
    EXPECT_CALL(*pin_output_direction_1_raw_ptr_, WriteHighToPin()).Times(1);
    EXPECT_CALL(*pin_output_direction_2_raw_ptr_, WriteLowToPin()).Times(1);

    int16_t desired_angle = 180;
    servo_control->SetAngle(desired_angle);
}

TEST_F(PwmServoControlTest, AngleMaxNegative)
{
    uint8_t expected_pwm_value = 255U;
    EXPECT_CALL(*pin_output_pwm_raw_ptr_, WriteDutyCycleToPin(expected_pwm_value)).Times(1);
    EXPECT_CALL(*pin_output_direction_1_raw_ptr_, WriteLowToPin()).Times(1);
    EXPECT_CALL(*pin_output_direction_2_raw_ptr_, WriteHighToPin()).Times(1);

    int16_t desired_angle = -180;
    servo_control->SetAngle(desired_angle);
}

TEST_F(PwmServoControlTest, AnglePositive_90)
{
    uint8_t expected_pwm_value = 128U;
    EXPECT_CALL(*pin_output_pwm_raw_ptr_, WriteDutyCycleToPin(expected_pwm_value)).Times(1);
    EXPECT_CALL(*pin_output_direction_1_raw_ptr_, WriteHighToPin()).Times(1);
    EXPECT_CALL(*pin_output_direction_2_raw_ptr_, WriteLowToPin()).Times(1);

    int16_t desired_angle = 90;
    servo_control->SetAngle(desired_angle);
}

TEST_F(PwmServoControlTest, AngleNegative_90)
{
    uint8_t expected_pwm_value = 128U;
    EXPECT_CALL(*pin_output_pwm_raw_ptr_, WriteDutyCycleToPin(expected_pwm_value)).Times(1);
    EXPECT_CALL(*pin_output_direction_1_raw_ptr_, WriteLowToPin()).Times(1);
    EXPECT_CALL(*pin_output_direction_2_raw_ptr_, WriteHighToPin()).Times(1);

    int16_t desired_angle = -90;
    servo_control->SetAngle(desired_angle);
}

TEST_F(PwmServoControlTest, LargerAnglePositive)
{
    uint8_t expected_pwm_value = 255U;
    EXPECT_CALL(*pin_output_pwm_raw_ptr_, WriteDutyCycleToPin(expected_pwm_value)).Times(1);
    EXPECT_CALL(*pin_output_direction_1_raw_ptr_, WriteHighToPin()).Times(1);
    EXPECT_CALL(*pin_output_direction_2_raw_ptr_, WriteLowToPin()).Times(1);

    int16_t desired_angle = 200;
    servo_control->SetAngle(desired_angle);
}

TEST_F(PwmServoControlTest, LargerAngleNegative)
{
    uint8_t expected_pwm_value = 255U;
    EXPECT_CALL(*pin_output_pwm_raw_ptr_, WriteDutyCycleToPin(expected_pwm_value)).Times(1);
    EXPECT_CALL(*pin_output_direction_1_raw_ptr_, WriteLowToPin()).Times(1);
    EXPECT_CALL(*pin_output_direction_2_raw_ptr_, WriteHighToPin()).Times(1);

    int16_t desired_angle = -200;
    servo_control->SetAngle(desired_angle);
}
