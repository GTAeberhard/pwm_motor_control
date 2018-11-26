#include <gmock/gmock.h>

#define private public
#define protected public
#include <motor_control.h>
#undef protected
#undef private

#include <mock_control_factory.h>
#include <gpio_mock.h>

class PwmMotorControlTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        pin_output_pwm = 2U;
        pin_output_direction_1= 3U;
        pin_output_direction_2= 4U;

        MockPwmControlFactory factory;
        motor_control = factory.CreateMotorControl(pin_output_pwm,
                                                   pin_output_direction_1,
                                                   pin_output_direction_2);
        
        pin_output_pwm_raw_ptr_ = dynamic_cast<GpioPwmPinMock*>(motor_control->pin_pwm_.get());
        pin_output_direction_1_raw_ptr_ = dynamic_cast<GpioPinMock*>(motor_control->pin_direction_1_.get());
        pin_output_direction_2_raw_ptr_ = dynamic_cast<GpioPinMock*>(motor_control->pin_direction_2_.get());
    }

    uint8_t pin_output_pwm;
    uint8_t pin_output_direction_1;
    uint8_t pin_output_direction_2;

    std::unique_ptr<PwmMotorControl> motor_control;

    GpioPwmPinMock* pin_output_pwm_raw_ptr_;
    GpioPinMock* pin_output_direction_1_raw_ptr_;
    GpioPinMock* pin_output_direction_2_raw_ptr_;
};

TEST_F(PwmMotorControlTest, Initialize)
{
    EXPECT_EQ(motor_control->pin_pwm_->pin_, pin_output_pwm);
    EXPECT_EQ(motor_control->pin_direction_1_->pin_, pin_output_direction_1);
    EXPECT_EQ(motor_control->pin_direction_2_->pin_, pin_output_direction_2);
}

struct TestMotorPwm
{
    int8_t percent_motor_power;
    uint8_t expected_pwm_value;
};

class TestMotorSpeeds : public PwmMotorControlTest,
                        public ::testing::WithParamInterface<TestMotorPwm>
{};

TEST_P(TestMotorSpeeds, MotorSpeeds)
{
    int8_t percent_motor_power = GetParam().percent_motor_power;

    uint8_t expected_pwm_value = GetParam().expected_pwm_value;
    EXPECT_CALL(*pin_output_pwm_raw_ptr_, WriteDutyCycleToPin(expected_pwm_value)).Times(1);

    if (percent_motor_power >= 0)
    {
        EXPECT_CALL(*pin_output_direction_1_raw_ptr_, WriteHighToPin()).Times(1);
        EXPECT_CALL(*pin_output_direction_2_raw_ptr_, WriteLowToPin()).Times(1);
    }
    else
    {
        EXPECT_CALL(*pin_output_direction_1_raw_ptr_, WriteLowToPin()).Times(1);
        EXPECT_CALL(*pin_output_direction_2_raw_ptr_, WriteHighToPin()).Times(1);        
    }

    motor_control->SetSpeed(percent_motor_power);
}

INSTANTIATE_TEST_CASE_P(TypicalSpeeds,
                        TestMotorSpeeds,
                        ::testing::Values(TestMotorPwm{0, 0U},
                                          TestMotorPwm{100, 255U},
                                          TestMotorPwm{-100, 255U},
                                          TestMotorPwm{50, 128U},
                                          TestMotorPwm{-50, 128U}));

INSTANTIATE_TEST_CASE_P(OutOfRangeSpeeds,
                        TestMotorSpeeds,
                        ::testing::Values(TestMotorPwm{120, 255U},
                                          TestMotorPwm{-120, 255U}));
