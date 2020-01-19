//
// Created by Karol on 28. 5. 2019.
//

#ifndef APPROXIMATIONTESTS_ELU_SIMULATIONS_H
#define APPROXIMATIONTESTS_ELU_SIMULATIONS_H


#include "Simulator.h"

#include <cmath>
#include <cstdint>
#include <iostream>
#include <fstream>

class ELU_simulations : public Simulator{
public:
    void perform_run() override;
    void perform_test() override;
    void runBKM(uint16_t fractional_bits);
    void runCORDIC(uint16_t fractional_bits);
    void runLinear(uint16_t fractional_bits);

    void testBKM(uint16_t fractional_bits, bool writeFile);
    void testCORDIC(uint16_t fractional_bits, bool writeFile);
    void testLinear(uint16_t fractional_bits, bool writeFile);

private:
    double elu(double x);
};


#endif //APPROXIMATIONTESTS_ELU_SIMULATIONS_H
