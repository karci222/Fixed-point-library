//
// Created by Karol on 5. 5. 2019.
//

#ifndef APPROXIMATIONTESTS_TANH_SIMULATIONS_H
#define APPROXIMATIONTESTS_TANH_SIMULATIONS_H


#include <cstdint>
#include <cmath>
#include <iostream>
#include <fstream>
#include "Simulator.h"
#include "Approximations_tanh.h"

class TanH_simulations: public Simulator {
private:
    double TanH(double x);

public:
    void perform_run() override;
    void perform_test() override;
    void runPLAN(uint16_t fractional_bits);
    void runALIPPI(uint16_t fractional_bits);
    void runA_LAW(uint16_t fractional_bits);
    void runPLATanH(uint16_t fractional_bits);
    void runLinear(uint16_t fractional_bits);
    void runQuadratic(uint16_t fractional_bits);


    void testPLAN(uint16_t fractional_bits, bool writeFile);
    void testA_LAW(uint16_t fractional_bits, bool writeFile);
    void testALIPPI(uint16_t fractional_bits, bool writeFile);
    void testPLATanH(uint16_t fractional_bits, bool writeFile);
    void testLinear(uint16_t fractional_bits, bool writeFile);
    void testQuadratic(uint16_t fractional_bits, bool writeFile);
};


#endif //APPROXIMATIONTESTS_TANH_SIMULATIONS_H
