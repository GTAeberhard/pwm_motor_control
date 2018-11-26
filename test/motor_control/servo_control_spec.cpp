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

struct TestAnglePwm
{
    int8_t desired_angle;
    uint8_t expected_pwm_value;
};

class TestServoAngles : public PwmServoControlTest,
                        public ::testing::WithParamInterface<TestAnglePwm>
{};

TEST_P(TestServoAngles, TestAngles)
{
    uint8_t expected_pwm_value = GetParam().expected_pwm_value;
    EXPECT_CALL(*pin_output_pwm_raw_ptr_, WriteDutyCycleToPin(expected_pwm_value)).Times(1);

    int8_t desired_angle = GetParam().desired_angle;

    if (desired_angle >= 0)
    {
        EXPECT_CALL(*pin_output_direction_1_raw_ptr_, WriteHighToPin()).Times(1);
        EXPECT_CALL(*pin_output_direction_2_raw_ptr_, WriteLowToPin()).Times(1);
    }
    else
    {
        EXPECT_CALL(*pin_output_direction_1_raw_ptr_, WriteLowToPin()).Times(1);
        EXPECT_CALL(*pin_output_direction_2_raw_ptr_, WriteHighToPin()).Times(1);        
    }

    servo_control->SetAngle(desired_angle);
}

INSTANTIATE_TEST_CASE_P(TypicalAngles,
                        TestServoAngles,
                        ::testing::Values(TestAnglePwm{0, 0U},
                                          TestAnglePwm{90, 255U},
                                          TestAnglePwm{-90, 255U},
                                          TestAnglePwm{45, 128U},
                                          TestAnglePwm{-45, 128U}));

INSTANTIATE_TEST_CASE_P(OutOfRangeAngles,
                        TestServoAngles,
                        ::testing::Values(TestAnglePwm{120, 255U},
                                          TestAnglePwm{-120, 255U}));
