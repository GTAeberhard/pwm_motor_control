cmake_minimum_required(VERSION 3.8)
project(pwm_motor_control)

set(CMAKE_CXX_STANDARD 14)

find_package(GMock QUIET)
if(NOT GMOCK_FOUND)
    configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)

    execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/googletest-download")
    execute_process(COMMAND "${CMAKE_COMMAND}" --build .
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/googletest-download")

    add_subdirectory("${CMAKE_CURRENT_BINARY_DIR}/googletest-src"
                        "${CMAKE_CURRENT_BINARY_DIR}/googletest-build")
endif()

add_subdirectory(gpio)
add_subdirectory(motor_control)
add_subdirectory(test)

find_library(WIRINGPI_LIB wiringPi)

IF(WIRINGPI_LIB)
    add_subdirectory(raspberrypi)
ENDIF()
