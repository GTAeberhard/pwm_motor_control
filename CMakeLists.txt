cmake_minimum_required(VERSION 3.8)
project(pwm_motor_control)

set(CMAKE_CXX_STANDARD 14)

set(PWM_MOTOR_CONTROL_MAJOR_VERSION 0)
set(PWM_MOTOR_CONTROL_MINOR_VERSION 1)
set(PWM_MOTOR_CONTROL_PATCH_VERSION 0)
set(PWM_MOTOR_CONTROL_VERSION
    ${PWM_MOTOR_CONTROL_MAJOR_VERSION}.${PWM_MOTOR_CONTROL_MINOR_VERSION}.${PWM_MOTOR_CONTROL_PATCH_VERSION})

set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE PATH "Installation directory for header files")
set(INSTALL_CMAKE_DIR lib/CMake/pwm_motor_control CACHE PATH "Installation directory for CMake files")

foreach(p LIB BIN INCLUDE CMAKE)
  set(var INSTALL_${p}_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()

include_directories(
  "${PROJECT_SOURCE_DIR}"
  "${PROJECT_BINARY_DIR}")

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

export(TARGETS gpio motor_control
    FILE "${PROJECT_BINARY_DIR}/pwm_motor_controlTargets.cmake")

export(PACKAGE pwm_motor_control)

file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}"
    "${INSTALL_INCLUDE_DIR}")

set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
configure_file(pwm_motor_control-config.cmake.in
    "${PROJECT_BINARY_DIR}/pwm_motor_control-config.cmake" @ONLY)

set(CONF_INCLUDE_DIRS "\${PWM_MOTOR_CONTROL_CMAKE_DIR}/${REL_INCLUDE_DIR}")
configure_file(pwm_motor_control-config.cmake.in
    "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/pwm_motor_control-config.cmake" @ONLY)

configure_file(pwm_motor_control-config-version.cmake.in
    "${PROJECT_BINARY_DIR}/pwm_motor_control-config-version.cmake" @ONLY)

install(FILES
    "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/pwm_motor_control-config.cmake"
    "${PROJECT_BINARY_DIR}/pwm_motor_control-config-version.cmake"
    DESTINATION "${INSTALL_CMAKE_DIR}")

install(EXPORT pwm_motor_controlTargets DESTINATION
    "${INSTALL_CMAKE_DIR}")
