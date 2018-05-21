cmake_minimum_required(VERSION 3.8)
project(pwm_motor_control)

set(CMAKE_CXX_STANDARD 14)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )

# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src"
                 "${CMAKE_BINARY_DIR}/googletest-build")

find_library(WIRINGPI_LIB wiringPi)

IF(WIRINGPI_LIB)
    add_subdirectory(raspberrypi)
ENDIF()

add_subdirectory(gpio)
add_subdirectory(motor_control)
add_subdirectory(test)
