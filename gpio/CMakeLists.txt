add_library (gpio
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gpio.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gpio_pwm.cpp)
target_include_directories (gpio PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
