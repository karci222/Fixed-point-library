//
// Created by Karol on 21. 2. 2019.
//

#ifndef APPROXIMATIONTESTS_APPROXIMATIONS_H
#define APPROXIMATIONTESTS_APPROXIMATIONS_H


#include "Fixed_point.h"

Fixed_point PLAN(Fixed_point x);
Fixed_point A_LAW(Fixed_point x);
Fixed_point ALIPPI(Fixed_point x);
Fixed_point ITERATIVE(Fixed_point x, int q);

Fixed_point PLAN(double x, uint16_t fractional_bits);
Fixed_point A_LAW(double x, uint16_t fractional_bits);
Fixed_point ALIPPI(double x, uint16_t fractional_bits);
Fixed_point ITERATIVE(double x, int q, uint16_t fractional_bits);

#endif //APPROXIMATIONTESTS_APPROXIMATIONS_H
