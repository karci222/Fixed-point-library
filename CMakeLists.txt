# cmake_minimum_required(VERSION <specify CMake version here>)
cmake_minimum_required(VERSION 3.8)

project(ApproximationTests)

set(CMAKE_CXX_STANDARD 14)

add_executable(ApproximationTests main.cpp Fixed_point.cpp Fixed_point.h Approximations.cpp Approximations.h
        Simulator.cpp Simulator.h Approximations_tanh.cpp Approximations_tanh.h Sigmoid_simulations.cpp Sigmoid_simulations.h TanH_simulations.cpp TanH_simulations.h CORDIC.cpp CORDIC.h BKM.cpp BKM.h  Approximations_ELU.cpp Approximations_ELU.h Approximations_ELU.cpp Approximations_ELU.h ELU_simulations.cpp ELU_simulations.h BKM_simulations.cpp BKM_simulations.h)
include_directories(
        Cnl INTERFACE
        $<INSTALL_INTERFACE:include>)