add_library (gpio_raspberrypi
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gpio_pwm_raspberrypi.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gpio_raspberrypi.cpp)
target_include_directories (gpio_raspberrypi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)
target_link_libraries (gpio_raspberrypi LINK_PUBLIC pthread ${WIRINGPI_LIB} rt crypt gpio)
