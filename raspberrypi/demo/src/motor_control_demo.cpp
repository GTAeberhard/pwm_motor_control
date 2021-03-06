#include <cstring>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <termios.h>

#include <gpio_raspberrypi.h>
#include <gpio_pwm_raspberrypi.h>
#include <motor_control.h>

#define KEY_SPACEBAR    0x20
#define KEY_BACKSPACE   0x7F

int kfd = 0;
struct termios cooked, raw;

void quit(int sig)
{
    (void) sig;
    tcsetattr(kfd, TCSANOW, &cooked);
    exit(0);
}

int main()
{
    std::unique_ptr<RaspberryPiGpioPwmPin> pin_pwm = std::make_unique<RaspberryPiGpioPwmPin>(1);
    std::unique_ptr<RaspberryPiGpioPin> pin_direction_1 = std::make_unique<RaspberryPiGpioPin>(4);
    std::unique_ptr<RaspberryPiGpioPin> pin_direction_2 = std::make_unique<RaspberryPiGpioPin>(5);
    PwmMotorControl motor_control(std::move(pin_pwm),
                                  std::move(pin_direction_1),
                                  std::move(pin_direction_2));

    signal(SIGINT, quit);

    puts("------------------------------------------------------------");
    puts("Press <SPACEBAR> to turn the motor forwards for 1 second.");
    puts("Press <BACKSPACE> to turn the motor backwards for 1 second.");
    puts("------------------------------------------------------------");

    char keyboard_input;

    // get the console in raw mode
    tcgetattr(kfd, &cooked);
    memcpy(&raw, &cooked, sizeof(struct termios));
    raw.c_lflag &=~ (ICANON | ECHO);
    // Setting a new line, then end of file
    raw.c_cc[VEOL] = 1;
    raw.c_cc[VEOF] = 2;
    tcsetattr(kfd, TCSANOW, &raw);

    for(;;)
    {
        if(read(kfd, &keyboard_input, 1) < 0)
        {
            perror("read():");
            exit(-1);
        }

        switch (keyboard_input)
        {
        case KEY_SPACEBAR:
            puts("Running motor forward for 1 second...");
            motor_control.SetSpeed(100);
            sleep(5);
            motor_control.SetSpeed(0);
            break;
        case KEY_BACKSPACE:
            puts("Running motor backward for 1 second...");
            motor_control.SetSpeed(-100);
            sleep(5);
            motor_control.SetSpeed(0);
            break;
        default:
            break;
        }
    }

    return 0;
}
