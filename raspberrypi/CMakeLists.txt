add_library (gpio_pwn_raspberrypi
    gpio
    ${WIRINGPI_LIB}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gpio/gpio_pwm_raspberrypi.cpp)
target_include_directories (gpio_pwn_raspberrypi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/gpio)

add_executable (motor_control_demo ${CMAKE_CURRENT_SOURCE_DIR}/motor_control_demo.cpp)
target_link_libraries (motor_control_demo LINK_PUBLIC gpio_pwn_raspberrypi motor_control)
