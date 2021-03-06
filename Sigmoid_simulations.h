//
// Created by Karol on 4. 5. 2019.
//

#include <cstdint>
#include <iostream>
#include <cmath>
#include <fstream>
#include "Simulator.h"
#include "Approximations.h"

#ifndef APPROXIMATIONTESTS_SIGMOID_SIMULATIONS_H
#define APPROXIMATIONTESTS_SIGMOID_SIMULATIONS_H




class Sigmoid_simulations: public Simulator{
private:
    double sigmoid(double x);
public:
    void perform_run() override;
    void perform_test() override;
    void runPLAN(uint16_t fractional_bits);
    void runALIPPI(uint16_t fractional_bits);
    void runA_LAW(uint16_t fractional_bits);
    void runIterative(int q,uint16_t fractional_bits);
    void runLinear(uint16_t fractional_bits);
    void runQuadratic(uint16_t fractional_bits);

    void testPLAN(uint16_t fractional_bits, bool writeFile);
    void testA_LAW(uint16_t fractional_bits, bool writeFile);
    void testALIPPI(uint16_t fractional_bits, bool writeFile);
    void testIterative(int q, uint16_t fractional_bits, bool writeFile);
    void testPOLYNOMIAL(uint16_t fractional_bits, bool writeFile);
    void testPOLYNOMIALQUADRATIC(uint16_t fractional_bits, bool writeFile);
};


#endif //APPROXIMATIONTESTS_SIGMOID_SIMULATIONS_H
