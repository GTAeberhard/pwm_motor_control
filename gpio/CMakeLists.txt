add_library (gpio SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gpio.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gpio_pwm.cpp)
target_include_directories (gpio PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/gpio>)

install(TARGETS gpio
    EXPORT pwm_motor_controlTargets
    RUNTIME DESTINATION "${INSTALL_BIN_DIR}"
    LIBRARY DESTINATION "${INSTALL_LIB_DIR}"
    ARCHIVE DESTINATION "${INSTALL_LIB_DIR}"
    PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/gpio")
