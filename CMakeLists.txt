cmake_minimum_required(VERSION 3.8)
project(pwm_motor_control)

set(CMAKE_CXX_STANDARD 14)

if(ENABLE_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g ")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

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

if(WIRINGPI_LIB)
    add_subdirectory(raspberrypi)
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

install(FILES package.xml DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME})

install(
    EXPORT ${PROJECT_NAME}
    FILE ${PROJECT_NAME}Targets.cmake
    DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}/cmake)

set(PROJECT_INCLUDE_DIR "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/")

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}-config.cmake.in"
    ${PROJECT_NAME}-config.cmake
    PATH_VARS PROJECT_INCLUDE_DIR CMAKE_INSTALL_LIBDIR
    INSTALL_DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}/cmake
    NO_CHECK_REQUIRED_COMPONENTS_MACRO)

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
    DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}/cmake)
