//
// Created by Karol on 4. 5. 2019.
//

#ifndef APPROXIMATIONTESTS_APPROXIMATIONS_TANH_H
#define APPROXIMATIONTESTS_APPROXIMATIONS_TANH_H


#include "Fixed_point.h"
#include <cmath>

Fixed_point TanH_PLAN(Fixed_point x);
Fixed_point TanH_A_LAW(Fixed_point x);
Fixed_point TanH_ALIPPI(Fixed_point x);
Fixed_point PLATanH(Fixed_point x);
Fixed_point LinearInterpolation(Fixed_point x);
Fixed_point QuadraticInterpolation(Fixed_point x);

Fixed_point PLAN_SIGMOID(Fixed_point x);
Fixed_point A_LAW_SIGMOID(Fixed_point x);
Fixed_point ALIPPI_SIGMOID(Fixed_point x);

Fixed_point TanH_A_LAW(double x, uint16_t fractional_bits);
Fixed_point TanH_PLAN(double x, uint16_t fractional_bits);
Fixed_point TanH_ALIPPI(double x, uint16_t fractional_bits);
Fixed_point PLATanH(double x, uint16_t fractional_bits);
Fixed_point Linear_interpolation(double x, uint16_t fractional_bits);
Fixed_point Quadratic_interpolation(double x, uint16_t fractional_bits);


#endif //APPROXIMATIONTESTS_APPROXIMATIONS_TANH_H
