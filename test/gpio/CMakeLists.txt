add_executable(gpio_spec gpio_spec.cpp gpio_pwm_spec.cpp)
target_link_libraries(gpio_spec gpio gtest_main gmock pthread)
target_include_directories(gpio_spec PUBLIC ${TEST_SUPPORT_DIR})
add_test(NAME gpio_spec COMMAND gpio_spec)
