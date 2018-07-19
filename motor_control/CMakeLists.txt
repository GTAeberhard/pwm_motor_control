add_library (motor_control SHARED
             ${CMAKE_CURRENT_SOURCE_DIR}/src/motor_control.cpp
             ${CMAKE_CURRENT_SOURCE_DIR}/src/servo_control.cpp)
target_link_libraries(motor_control gpio)
target_include_directories(motor_control PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/motor_control>)

install(TARGETS motor_control
    EXPORT pwm_motor_controlTargets
    RUNTIME DESTINATION "${INSTALL_BIN_DIR}"
    LIBRARY DESTINATION "${INSTALL_LIB_DIR}"
    ARCHIVE DESTINATION "${INSTALL_LIB_DIR}"
    PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/motor_control")
