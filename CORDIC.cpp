//
// Created by Karol on 26. 5. 2019.
//

#include "CORDIC.h"
#include <cmath>
#include <cstdlib>

Fixed_point CORDIC::ROM_lookup(int i, int coor) {
    if (i > 0){
        if (coor == 1){
            return Fixed_point(atan(pow(2, -i)), this->integer_bits, this->fractional_bits);
        }
        else if (coor== 0) {
            return Fixed_point(pow(2, -i), this->integer_bits, this->fractional_bits);
        }
        else if (coor == -1) {
            return Fixed_point(atanh(pow(2, -i)), this->integer_bits, this->fractional_bits);
        }
    }
    else {
        if (coor == 1) {
            return Fixed_point(atan(1.0 - pow(2, (i-2))), this->integer_bits, this->fractional_bits);
        }
        else if(coor == 0) {
            return Fixed_point(1.0 - pow(2, (i - 2)), this->integer_bits, this->fractional_bits);
        }
        else if(coor == -1) {
            return Fixed_point(atanh(1 - pow(2, (i - 2))), this->integer_bits, this->fractional_bits);
        }
    }
}

CORDIC::CORDIC(uint16_t fractional_bits, uint16_t integer_bits) {
    this->fractional_bits = fractional_bits;
    this->integer_bits = integer_bits;
}

Fixed_point *CORDIC::cordic_rotate(Fixed_point x, Fixed_point y, Fixed_point z, int coor, int max_iterations, int m) {
    Fixed_point x_curr = x;
    Fixed_point y_curr = y;
    Fixed_point z_curr = z;



    int i = m;
    int di = 1;

    if(coor == -1 and m == 0) {
        i = 1;
    }else {
        i = m;
    }

    int flag = 0;

    for (; i <= max_iterations; i++){
        if (z_curr.isNegative()) {
            di = -1;
        }else{
            di = 1;
        }

        Fixed_point x_next;
        Fixed_point y_next;
        Fixed_point z_next;

        Fixed_point di_fixed_point = Fixed_point((double) di, this->integer_bits, this->fractional_bits);
        Fixed_point coor_fixed_point = Fixed_point((double) coor, this->integer_bits, this->fractional_bits);

        if (i > 0){
            Fixed_point x_term = (di_fixed_point*coor_fixed_point*y_curr) >> (i);
            Fixed_point y_term = (di_fixed_point*x_curr) >> (i);
            Fixed_point z_term = di_fixed_point*this->ROM_lookup(i, coor);
            x_next = x_curr - x_term;
            y_next = y_curr + y_term;
            z_next = z_curr - z_term;
        }else{
            Fixed_point x_term = (di_fixed_point*coor_fixed_point*(y_curr - (y_curr>>(abs(i) + 2))));
            Fixed_point y_term = (di_fixed_point*(x_curr - (x_curr>>(abs(i)+ 2))));
            Fixed_point z_term = di_fixed_point*this->ROM_lookup(i, coor);
            x_next = x_curr - x_term;
            y_next = y_curr + y_term;
            z_next = z_curr - z_term;
        }

        x_curr = x_next;
        y_curr = y_next;
        z_curr = z_next;


        if (coor == -1) {
            if ((i != 4) & (i != 13) & (i != 40)) {
            } else if (flag == 0) {
                flag = 1;
                i = i - 1;
            } else if (flag == 1) {
                flag = 0;
            }
        }
    }

    Fixed_point *fixed_point_arr = new Fixed_point[3];
    fixed_point_arr[0] = x_curr;
    fixed_point_arr[1] = y_curr;
    fixed_point_arr[2] = z_curr;

    return fixed_point_arr;
}
