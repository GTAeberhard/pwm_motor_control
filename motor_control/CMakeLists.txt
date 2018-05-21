add_library (motor_control ${CMAKE_CURRENT_SOURCE_DIR}/src/motor_control.cpp)
target_link_libraries(motor_control gpio)
target_include_directories(motor_control PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
