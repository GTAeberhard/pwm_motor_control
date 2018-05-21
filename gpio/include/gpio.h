#ifndef GPIO_H
#define GPIO_H

#include <cstdint>

class GpioPin
{
public:
    GpioPin(const uint8_t pin_number);

    virtual ~GpioPin() {}

    void Write(const uint8_t value);
    void WriteHigh();
    void WriteLow();

protected:
    uint8_t pin_;

private:
    virtual void WriteToPin(const uint8_t value) = 0;
    virtual void WriteHighToPin() = 0;
    virtual void WriteLowToPin() = 0;
};

#endif
