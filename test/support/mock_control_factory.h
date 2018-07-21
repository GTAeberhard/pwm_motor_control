#ifndef MOCK_CONTROL_FACTORY_H
#define MOCK_CONTROL_FACTORY_H

#include <pwm_control_factory.h>
#include <gpio_mock.h>

class MockPwmControlFactory : public PwmControlFactory
{
public:
    std::unique_ptr<PwmMotorControl>
    CreateMotorControl(const uint8_t pin_pwm,
                       const uint8_t pin_direction_1,
                       const uint8_t pin_direction_2) override
    {
        auto output_pwm = std::make_unique<GpioPwmPinMock>(pin_pwm);
        auto output_direction_1 = std::make_unique<GpioPinMock>(pin_direction_1);
        auto output_direction_2 = std::make_unique<GpioPinMock>(pin_direction_2);

        return std::make_unique<PwmMotorControl>(std::move(output_pwm),
                                                 std::move(output_direction_1),
                                                 std::move(output_direction_2));   
    }

    std::unique_ptr<PwmServoControl>
    CreateServoControl(const uint8_t pin_pwm,
                       const uint8_t pin_direction_1,
                       const uint8_t pin_direction_2) override
    {
        auto output_pwm = std::make_unique<GpioPwmPinMock>(pin_pwm);
        auto output_direction_1 = std::make_unique<GpioPinMock>(pin_direction_1);
        auto output_direction_2 = std::make_unique<GpioPinMock>(pin_direction_2);

        return std::make_unique<PwmServoControl>(std::move(output_pwm),
                                                 std::move(output_direction_1),
                                                 std::move(output_direction_2));  
    }
};

#endif