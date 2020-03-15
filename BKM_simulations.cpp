//
// Created by Karol on 17. 1. 2020.
//

#include "BKM_simulations.h"
#include "Fixed_point.h"
#include "BKM.h"

#include <cmath>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdint>

using namespace std;

void BKM_simulations::perform_run() {
    for (uint16_t i = 7; i < 12; i++){
        runBKM_exp(i);

    }
    for (uint16_t i = 7; i < 12; i++){
        runBKM_log(i);
    }

    for (uint16_t i = 7; i < 12; i++){
        runBKM_exp32(i);
    }

    for (uint16_t i = 7; i < 12; i++) {
        runBKM_log32(i);
    }
}

void BKM_simulations::perform_test() {
    for (uint16_t i = 4; i < 9; i++){
        printf("Testing BKM algorithms with bit length of: %d\n", i);
        testBKM_exp(i, true);
    }
    for (uint16_t i = 7; i < 13; i++){
        printf("Testing BKM algorithms with bit length of: %d\n", i);
        testBKM_log(i, true);
    }
}

void BKM_simulations::runBKM_exp(uint16_t fractional_bits) {
    printf("BKM exponential approximation test...\n");
    double i = -8.0;
    double di = (double) 1/(double)(1<<fractional_bits);
    double max_i = 4.8;

    uint16_t integer_bits = 15 - fractional_bits;
    ofstream file;
    file.open("BKM_exp_range_" + to_string(fractional_bits) + ".txt");
    BKM bkm = BKM(fractional_bits, integer_bits);

    while (i < max_i){
        Fixed_point fxp = Fixed_point(i, integer_bits, fractional_bits);
        Fixed_point *result = bkm.bkm_range_reduced(fxp, Fixed_point(1.0, integer_bits, fractional_bits), 8);

        file << i << "," << result[0].getNumber() << endl;

        i += di;
    }

    file.close();
}

void BKM_simulations::runBKM_log(uint16_t fractional_bits) {
    printf("BKM logarithm approximation test...\n");
    double di = (double) 1/(double)(1<<fractional_bits);
    double i = 0.05;
    double max_i = 15.0;

    uint16_t integer_bits = 15 - fractional_bits;
    ofstream file;
    file.open("BKM_log_range_" + to_string(fractional_bits) + ".txt");
    BKM bkm = BKM(fractional_bits, integer_bits);

    while (i < max_i){
        Fixed_point fxp = Fixed_point(i, integer_bits, fractional_bits);
        Fixed_point *result = bkm.bkm_range_reduced_log(fxp, Fixed_point(0.0, integer_bits, fractional_bits), 10);
        short out_num =  short(result[1].getNumber());

        file << i << "," << out_num << endl;

        i += di;
    }

    file.close();
}

void BKM_simulations::testBKM_exp(uint16_t fractional_bits, bool writeFile) {

}

void BKM_simulations::testBKM_log(uint16_t fractional_bits, bool writeFile) {

}

void BKM_simulations::runBKM_exp32(uint16_t fractional_bits) {
    printf("BKM exponential approximation test %d...\n", fractional_bits);
    double i = -8.0;
    double di = (double) 1/(double)(1<<fractional_bits);
    double max_i = 11.0;

    uint16_t integer_bits = 31 - fractional_bits;
    ofstream file;
    file.open("BKM32_exp_range_" + to_string(fractional_bits) + ".txt");
    BKM bkm = BKM(fractional_bits, integer_bits);

    while (i < max_i){
        Fixed_point32 fxp = Fixed_point32(i, integer_bits, fractional_bits);
        Fixed_point32 *result = bkm.bkm_range_reduced(fxp, Fixed_point32(1.0, integer_bits, fractional_bits), 8);

        file << i << "," << result[0].getNumber() << endl;

        i += di;
    }

    file.close();
}

void BKM_simulations::runBKM_log32(uint16_t fractional_bits) {
    printf("BKM logarithm approximation test %d...\n", fractional_bits);
    double di = (double) 1/(double)(1<<fractional_bits);
    double i = 0.05;
    double max_i = 15.0;

    uint16_t integer_bits = 31 - fractional_bits;
    ofstream file;
    file.open("BKM_log_range_" + to_string(fractional_bits) + ".txt");
    BKM bkm = BKM(fractional_bits, integer_bits);

    while (i < max_i){
        Fixed_point32 fxp = Fixed_point32(i, integer_bits, fractional_bits);
        Fixed_point32 *result = bkm.bkm_range_reduced_log(fxp, Fixed_point32(0.0, integer_bits, fractional_bits), 10);
        short out_num =  short(result[1].getNumber());

        file << i << "," << out_num << endl;

        i += di;
    }

    file.close();
}
