//
// Created by Karol on 27. 5. 2019.
//

#ifndef APPROXIMATIONTESTS_BKM_H
#define APPROXIMATIONTESTS_BKM_H


#include "Fixed_point.h"
#include "FixedPoint32.h"

class BKM {
public:
    Fixed_point *bkm(Fixed_point x, Fixed_point e0, int iterations);
    Fixed_point *bkm_2(Fixed_point x, Fixed_point l0, int iterations);
    BKM(uint16_t fractional_bits, uint16_t integer_bits);
    Fixed_point *bkm_range_reduced(Fixed_point x, Fixed_point e0, int iterations);
    Fixed_point *bkm_range_reduced_log(Fixed_point x, Fixed_point l0, int iterations);

    Fixed_point32 *bkm(Fixed_point32 x, Fixed_point32 e0, int iterations);
    Fixed_point32 *bkm_2(Fixed_point32 x, Fixed_point32 l0, int iterations);
    Fixed_point32 *bkm_range_reduced(Fixed_point32 x, Fixed_point32 e0, int iterations);
    Fixed_point32 *bkm_range_reduced_log(Fixed_point32 x, Fixed_point32 l0, int iterations);

private:
    Fixed_point ROM_lookup(int di, int i);
    Fixed_point compute_error(int n, Fixed_point Ei);
    uint16_t fractional_bits;
    uint16_t integer_bits;
    Fixed_point get_k(Fixed_point x);
    int get_k_int(Fixed_point x);
    Fixed_point range_reduce(Fixed_point x, int k);

    Fixed_point32 ROM32_lookup(int di, int i);
    Fixed_point32 compute_error(int n, Fixed_point32 Ei);
    Fixed_point32 get_k(Fixed_point32 x);
    int get_k_int(Fixed_point32 x);
    Fixed_point32 range_reduce(Fixed_point32 x, int k);

};


#endif //APPROXIMATIONTESTS_BKM_H
