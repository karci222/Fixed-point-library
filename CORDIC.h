//
// Created by Karol on 26. 5. 2019.
//

#ifndef APPROXIMATIONTESTS_CORDIC_H
#define APPROXIMATIONTESTS_CORDIC_H


#include "Fixed_point.h"

class CORDIC {
public:
    Fixed_point *cordic_rotate(Fixed_point x, Fixed_point y, Fixed_point z, int coor, int max_iterations, int m);
    CORDIC(uint16_t fractional_bits, uint16_t integer_bits);

private:
    Fixed_point ROM_lookup(int i, int coor);
    uint16_t fractional_bits;
    uint16_t integer_bits;
};


#endif //APPROXIMATIONTESTS_CORDIC_H
