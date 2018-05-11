enable_testing()

add_executable(motor_control_spec
               motor_control_spec.cpp)

target_link_libraries(motor_control_spec motor_control gtest_main pthread)

add_test(NAME motor_control_spec
         COMMAND motor_control_spec)
