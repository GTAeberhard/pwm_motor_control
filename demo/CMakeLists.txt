add_executable (motor_control_demo ${CMAKE_CURRENT_SOURCE_DIR}/motor_control_demo.cpp)
target_link_libraries (motor_control_demo LINK_PUBLIC motor_control)
