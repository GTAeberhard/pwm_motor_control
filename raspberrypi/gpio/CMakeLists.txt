add_library (gpio_raspberrypi
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gpio/gpio_pwm_raspberrypi.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gpio/gpio_raspberrypi.cpp)
target_include_directories (gpio_raspberrypi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/gpio/)
target_link_libraries (gpio_raspberrypi LINK_PUBLIC pthread ${WIRINGPI_LIB} rt crypt gpio)
