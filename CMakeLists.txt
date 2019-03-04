# cmake_minimum_required(VERSION <specify CMake version here>)
cmake_minimum_required(VERSION 3.8)

project(ApproximationTests)

set(CMAKE_CXX_STANDARD 14)

add_executable(ApproximationTests main.cpp Fixed_point.cpp Fixed_point.h Approximations.cpp Approximations.h)
include_directories(
        Cnl INTERFACE
        $<BUILD_INTERFACE:"C:\\Program Files (x86)\\CNL_Library\\cnl-develop\\include">
        $<INSTALL_INTERFACE:include>)