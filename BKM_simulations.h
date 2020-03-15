//
// Created by Karol on 17. 1. 2020.
//
#ifndef APPROXIMATIONTESTS_BKM_SIMULATIONS_H
#define APPROXIMATIONTESTS_BKM_SIMULATIONS_H

#include "Simulator.h"

#include <cmath>
#include <cstdint>
#include <iostream>
#include <fstream>


class BKM_simulations : public Simulator{
public:
    void perform_run() override;
    void perform_test() override;

    void runBKM_exp(uint16_t fractional_bits);
    void runBKM_log(uint16_t fractional_bits);
    void runBKM_exp32(uint16_t fractional_bits);
    void runBKM_log32(uint16_t fractional_bits);

    void testBKM_exp(uint16_t fractional_bits, bool writeFile);
    void testBKM_log(uint16_t fractional_bits, bool writeFile);
    void testBKM_exp32(uint16_t fractional_bits, bool writeFile);
    void testBKM_log32(uint16_t fractional_bits, bool writeFile);
};


#endif //APPROXIMATIONTESTS_BKM_SIMULATIONS_H
