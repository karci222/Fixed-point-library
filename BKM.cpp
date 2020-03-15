//
// Created by Karol on 27. 5. 2019.
//

#include "BKM.h"
#include <cmath>
#include <cstdio>

BKM::BKM(uint16_t fractional_bits, uint16_t integer_bits) {
    this->fractional_bits = fractional_bits;
    this->integer_bits = integer_bits;
}

Fixed_point BKM::ROM_lookup(int di, int i) {
    return Fixed_point(log(1.0 + (double)di*(pow((double)2, -i))), this->integer_bits, this->fractional_bits);
}



Fixed_point *BKM::bkm(Fixed_point x, Fixed_point e0, int iterations) {
    Fixed_point Li = x;
    Fixed_point Ei = e0;
    Fixed_point *arr = new Fixed_point[2];
    int di_int = 0;

    for(int i = 0; i < iterations; i++){
        Fixed_point di;
        if (Li > ROM_lookup(1, i)){
            di_int = 1;
            di = Fixed_point(1.0, this->integer_bits, this->fractional_bits);
        }else{
            di_int = 0;
            di = Fixed_point(0.0, this->integer_bits, this->fractional_bits);
        }

        Fixed_point L_term = ROM_lookup(di_int, i);
        //printf("16bit: %d\t%d\n", i, L_term.getNumber());
        Fixed_point Li_next = Li - L_term;
        Fixed_point E_term = (di*Ei)>>(i);
        Fixed_point E_next = Ei + E_term;

        Ei = E_next;
        Li = Li_next;
    }

    arr[0] = Ei;
    arr[1] = Li;

    return arr;
}

Fixed_point *BKM::bkm_range_reduced(Fixed_point x, Fixed_point e0, int iterations) {
    Fixed_point n;
    Fixed_point x_dot;
    if (x > Fixed_point(1.56202, this->integer_bits, this->fractional_bits) ||  x < Fixed_point(0.0, this->integer_bits, this->fractional_bits)) {
        n =(x * Fixed_point(23.0 / 16.0, this->integer_bits, this->fractional_bits));
        n = Fixed_point((double )((short )n.getIntegerPart()), this->integer_bits, this->fractional_bits);
        Fixed_point x_dot_term = n * Fixed_point(log(2.0), this->integer_bits, this->fractional_bits);
        x_dot = x - n * Fixed_point(log(2.0), this->integer_bits, this->fractional_bits);
    }else {
        n = Fixed_point(0.0, this->integer_bits, this->fractional_bits);
        x_dot = x;
    }

    short shift = (short) n.getIntegerPart();
    Fixed_point *result = bkm(x_dot, e0, iterations);
    if(shift > 0) {
        result[0] = result[0] << shift;
    }else
    {
        result[0] = result[0] >> (-1*shift);
    }

    return result;
}

Fixed_point *BKM::bkm_2(Fixed_point x, Fixed_point l0, int iterations) {
    Fixed_point Li = l0;
    Fixed_point Ei = x;
    Fixed_point *arr = new Fixed_point[2];
    int di_int = 0;

    Fixed_point epsilon_0 = compute_error(0, Ei);
    Fixed_point cond_0 = Fixed_point(-6.0/16.0, x.getInteger_bits(), x.getFractional_bits());
    if (epsilon_0 >= cond_0){
        di_int = 1;
    }else{
        di_int = 0;
    }

    Fixed_point cond_half = Fixed_point(0.5, x.getInteger_bits(), x.getFractional_bits());
    Fixed_point cond_negative_half = Fixed_point(-0.5, x.getInteger_bits(), x.getFractional_bits());

    for(int i = 0; i < iterations; i++){
        Fixed_point di;
        Fixed_point epsilon = compute_error(i, Ei);

        if (i > 0) {
            if (epsilon >= cond_half) {
                di_int = -1;
                di = Fixed_point(-1.0, this->integer_bits, this->fractional_bits);
            } else if (epsilon > cond_negative_half){
                di_int = 0;
                di = Fixed_point(0.0, this->integer_bits, this->fractional_bits);
            }else{
                di_int = 1;
                di = Fixed_point(1.0, this->integer_bits, this->fractional_bits);
            }
        }else{
            di = Fixed_point((double)di_int, this->integer_bits, this->fractional_bits);
        }

        Fixed_point L_term = ROM_lookup(di_int, i);
        //printf("%d\n", L_term.getNumber());
        Fixed_point Li_next = Li - L_term;
        Fixed_point E_term = (di*Ei)>>(i);
        Fixed_point E_next = Ei + E_term;

        Ei = E_next;
        Li = Li_next;
    }

    arr[0] = Ei;
    arr[1] = Li;

    return arr;
}

Fixed_point BKM::compute_error(int n, Fixed_point Ei) {
    Fixed_point two_to_n = Fixed_point(1.0, Ei.getInteger_bits(), Ei.getFractional_bits());
    two_to_n = two_to_n << n;

    Fixed_point computed_error = two_to_n * (Ei - Fixed_point(1.0, Ei.getInteger_bits(), Ei.getFractional_bits()));

    return computed_error;
}

Fixed_point *BKM::bkm_range_reduced_log(Fixed_point x, Fixed_point l0, int iterations) {
    Fixed_point boundary_low = Fixed_point(0.5, x.getInteger_bits(), x.getFractional_bits());
    Fixed_point boundary_high = Fixed_point(1.0, x.getInteger_bits(), x.getFractional_bits());
    Fixed_point *result;

    if (x < boundary_low || x > boundary_high){
        Fixed_point k = this->get_k(x);
        int k_int = this->get_k_int(x);
        //printf("%d\n", k_int);
        Fixed_point x_dot = this->range_reduce(x, k_int);
        result = bkm_2(x_dot, l0, iterations);
        Fixed_point log_2 = Fixed_point(log(2.0), x.getInteger_bits(), x.getFractional_bits());
        Fixed_point log_2_k = k*log_2;
        result[1] = result[1] + log_2_k;
    }else{
        result = bkm_2(x, l0, iterations);
    }

    return result;
}

Fixed_point BKM::get_k(Fixed_point x) {
    int leading_ones = x.getLeadingOnes();
    int k_int = x.getInteger_bits() - ((x.getFractional_bits() + x.getInteger_bits() - 1)  - leading_ones);
    Fixed_point k = Fixed_point((double) k_int, x.getInteger_bits(), x.getFractional_bits());

    return k;
}

Fixed_point BKM::range_reduce(Fixed_point x, int k) {
    Fixed_point x_shifted = x;
    if (k >= 0){
        x_shifted = x_shifted >> k;
    }else{
        x_shifted = x_shifted << -k;
    }

    return x_shifted;
}

int BKM::get_k_int(Fixed_point x) {
    int leading_ones = x.getLeadingOnes();
    int k_int = x.getInteger_bits() - ((x.getFractional_bits() + x.getInteger_bits() - 1)  - leading_ones);

    return k_int;
}

Fixed_point32 BKM::ROM32_lookup(int di, int i) {
    return Fixed_point32(log(1.0 + (double)di*(pow((double)2, -i))), this->integer_bits, this->fractional_bits);
}

Fixed_point32 BKM::compute_error(int n, Fixed_point32 Ei) {
    Fixed_point32 two_to_n = Fixed_point32(1.0, Ei.getInteger_bits(), Ei.getFractional_bits());
    two_to_n = two_to_n << n;

    Fixed_point32 computed_error = two_to_n * (Ei - Fixed_point32(1.0, Ei.getInteger_bits(), Ei.getFractional_bits()));

    return computed_error;
}

Fixed_point32 BKM::get_k(Fixed_point32 x) {
    int leading_ones = x.getLeadingOnes();
    int k_int = x.getInteger_bits() - ((x.getFractional_bits() + x.getInteger_bits() - 1)  - leading_ones);
    Fixed_point32 k = Fixed_point32((double) k_int, x.getInteger_bits(), x.getFractional_bits());

    return k;
}

int BKM::get_k_int(Fixed_point32 x) {
    int leading_ones = x.getLeadingOnes();
    int k_int = x.getInteger_bits() - ((x.getFractional_bits() + x.getInteger_bits() - 1)  - leading_ones);

    return k_int;
}

Fixed_point32 BKM::range_reduce(Fixed_point32 x, int k) {
    Fixed_point32 x_shifted = x;
    if (k >= 0){
        x_shifted = x_shifted >> k;
    }else{
        x_shifted = x_shifted << -k;
    }

    return x_shifted;
}

Fixed_point32 *BKM::bkm(Fixed_point32 x, Fixed_point32 e0, int iterations) {
    Fixed_point32 Li = x;
    Fixed_point32 Ei = e0;
    Fixed_point32 *arr = new Fixed_point32[2];
    int di_int = 0;

    for(int i = 0; i < iterations; i++){
        Fixed_point32 di;
        Fixed_point32 margin = ROM32_lookup(1, i);
        if (Li > margin){
            di_int = 1;
            di = Fixed_point32(1.0, this->integer_bits, this->fractional_bits);
        }else{
            di_int = 0;
            di = Fixed_point32(0.0, this->integer_bits, this->fractional_bits);
        }

        Fixed_point32 L_term = ROM32_lookup(di_int, i);
        //printf("32bit: %d %d\n", i, L_term.getNumber());
        Fixed_point32 Li_next = Li - L_term;
        Fixed_point32 E_term = (di*Ei)>>(i);
        Fixed_point32 E_next = Ei + E_term;

        Ei = E_next;
        Li = Li_next;
    }

    arr[0] = Ei;
    arr[1] = Li;

    return arr;
}

Fixed_point32 *BKM::bkm_2(Fixed_point32 x, Fixed_point32 l0, int iterations) {
    Fixed_point32 Li = l0;
    Fixed_point32 Ei = x;
    Fixed_point32 *arr = new Fixed_point32[2];
    int di_int = 0;

    Fixed_point32 epsilon_0 = compute_error(0, Ei);
    Fixed_point32 cond_0 = Fixed_point32(-6.0/16.0, x.getInteger_bits(), x.getFractional_bits());
    if (epsilon_0 >= cond_0){
        di_int = 1;
    }else{
        di_int = 0;
    }

    Fixed_point32 cond_half = Fixed_point32(0.5, x.getInteger_bits(), x.getFractional_bits());
    Fixed_point32 cond_negative_half = Fixed_point32(-0.5, x.getInteger_bits(), x.getFractional_bits());

    for(int i = 0; i < iterations; i++){
        Fixed_point32 di;
        Fixed_point32 epsilon = compute_error(i, Ei);

        if (i > 0) {
            if (epsilon >= cond_half) {
                di_int = -1;
                di = Fixed_point32(-1.0, this->integer_bits, this->fractional_bits);
            } else if (epsilon > cond_negative_half){
                di_int = 0;
                di = Fixed_point32(0.0, this->integer_bits, this->fractional_bits);
            }else{
                di_int = 1;
                di = Fixed_point32(1.0, this->integer_bits, this->fractional_bits);
            }
        }else{
            di = Fixed_point32((double)di_int, this->integer_bits, this->fractional_bits);
        }

        Fixed_point32 L_term = ROM32_lookup(di_int, i);
        //printf("32bit: %d %d\n", i, L_term.getNumber());
        Fixed_point32 Li_next = Li - L_term;
        Fixed_point32 E_term = (di*Ei)>>(i);
        Fixed_point32 E_next = Ei + E_term;

        Ei = E_next;
        Li = Li_next;
    }

    arr[0] = Ei;
    arr[1] = Li;

    return arr;
}

Fixed_point32 *BKM::bkm_range_reduced(Fixed_point32 x, Fixed_point32 e0, int iterations) {
    Fixed_point32 n;
    Fixed_point32 x_dot;
    //if (x.getNumber() == 0)
        //printf("x^0\n");
    if (x > Fixed_point32(1.56202, this->integer_bits, this->fractional_bits) ||  x < Fixed_point32(0.0, this->integer_bits, this->fractional_bits)) {

        n =(x * Fixed_point32(23.0 / 16.0, this->integer_bits, this->fractional_bits));
        n = Fixed_point32((double )((short )n.getIntegerPart()), this->integer_bits, this->fractional_bits);
        Fixed_point32 x_dot_term = n * Fixed_point32(log(2.0), this->integer_bits, this->fractional_bits);
        x_dot = x - n * Fixed_point32(log(2.0), this->integer_bits, this->fractional_bits);
    }else {
        n = Fixed_point32(0.0, this->integer_bits, this->fractional_bits);
        x_dot = x;
    }

    short shift = (short) n.getIntegerPart();
    Fixed_point32 *result = bkm(x_dot, e0, iterations);
    if(shift > 0) {
        result[0] = result[0] << shift;
    }else
    {
        result[0] = result[0] >> (-1*shift);
    }

    return result;
}

Fixed_point32 *BKM::bkm_range_reduced_log(Fixed_point32 x, Fixed_point32 l0, int iterations) {
    Fixed_point32 boundary_low = Fixed_point32(0.5, x.getInteger_bits(), x.getFractional_bits());
    Fixed_point32 boundary_high = Fixed_point32(1.0, x.getInteger_bits(), x.getFractional_bits());
    Fixed_point32 *result;

    if (x < boundary_low || x > boundary_high){
        Fixed_point32 k = this->get_k(x);
        int k_int = this->get_k_int(x);
        //printf("%d\n", k_int);
        Fixed_point32 x_dot = this->range_reduce(x, k_int);
        result = bkm_2(x_dot, l0, iterations);
        Fixed_point32 log_2 = Fixed_point32(log(2.0), x.getInteger_bits(), x.getFractional_bits());
        Fixed_point32 log_2_k = k*log_2;
        result[1] = result[1] + log_2_k;
    }else{
        result = bkm_2(x, l0, iterations);
    }

    return result;
}
