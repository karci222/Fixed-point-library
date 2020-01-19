//
// Created by Karol on 27. 5. 2019.
//

#include "Fixed_point.h"

#ifndef APPROXIMATIONTESTS_APPROXIMATIONS_ELU_H
#define APPROXIMATIONTESTS_APPROXIMATIONS_ELU_H

Fixed_point ELU_BKM(Fixed_point x, Fixed_point e0, int iterations);
Fixed_point ELU_CORDIC(Fixed_point x, int max_iterations, int m);
Fixed_point ELU_Linear(Fixed_point x);

Fixed_point ELU_BKM(double x, int  fractional_bits, Fixed_point e0, int iterations);
Fixed_point ELU_CORDIC(double x, int fractional_bits, int max_iterations, int m);
Fixed_point ELU_Linear(double x, int fractional_bits);



#endif //APPROXIMATIONTESTS_APPROXIMATIONS_ELU_H
