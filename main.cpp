#include <iostream>
#include <cmath>
#include <fstream>
#include "Fixed_point.h"
#include "Approximations.h"
#include "Simulator.h"
#include "TanH_simulations.h"
#include "CORDIC.h"
#include "BKM.h"
#include "ELU_simulations.h"


using namespace std;

void basicExamples();
void averageAndMaximalError(int print, uint16_t fractional_bits);
void operatorsTest();


int main() {
    Simulator *simulator = new ELU_simulations();

    simulator->perform_test();


}

void basicExamples(){
    double number = 6.00000 ;
    double integral;

    printf("%d\n",  (uint16_t)round(modf((-1)*number, &integral) * (1 << 11)));
    printf("%d\n", (uint16_t)number);


    Fixed_point fxp1 =  Fixed_point(-7.990723);
    Fixed_point fxp2 = Fixed_point(-7.785);

    printf("FxP 1: %u\n", (fxp1>>6).getNumber());
    printf("FxP 2: %u\n", fxp2.getNumber());

    printf("FxP1: Integer part: %u\t Fractional part: %u\n", fxp1.getIntegerPart(), fxp1.getFractionalPart());
    printf("FxP2: Integer part: %u\t Fractional part: %u\n", fxp2.getIntegerPart(), fxp2.getFractionalPart());

    printf("FxP 1: %f\n", fxp1.getDoubleValue());
    printf("FxP 2: %f\n", fxp2.getDoubleValue());

    Fixed_point fxp1_1 = Fixed_point(3.98, 3, 12);
    Fixed_point fxp2_1 = Fixed_point(0.98, 3, 12);

    printf("%f %f\n", 3.98*0.98, (fxp1_1*fxp2_1).getDoubleValue());
}

/*
 * Only computed within a range -15 to 15
 */
void averageAndMaximalError(int print, uint16_t fractional_bits){
    uint16_t integer_bits = 15 - fractional_bits;
    double di = (double) 1 /(double)(1<<fractional_bits);
    printf("%f\n", di);
    int j = 0;
    double sum = 0;
    double max_abs_error = 0;
    double  i = (double)((-1)*((1<<integer_bits) - 1));
    while (i < (1<<integer_bits) - 1){
        j+=1;
        Fixed_point fxp = Fixed_point(i, integer_bits, fractional_bits);
        double stored = fxp.getDoubleValue();

        double abs_error = abs(i - stored);
        if(abs_error > max_abs_error){
            max_abs_error = abs_error;
        }

        sum += abs_error;

        if(print) {
            printf("Actual number: %f. From Fixed point: %f. Error: %f\n", i, stored, abs_error);
        }

        i+= di;
    }

    double average_absolute_error = sum/((double) j);
    printf("Average absolute error: %f\t Maximal absolute error: %f\n", average_absolute_error, max_abs_error);
}

void operatorsTest(){
    Fixed_point fxp1 = Fixed_point(2.3);
    Fixed_point fxp2 = Fixed_point(0.23);

    printf("fxp1: %f\n", fxp1.getDoubleValue());
    printf("fxp2: %f\n", fxp2.getDoubleValue());

    printf("fxp1 fractional part: %u\t%f\n",fxp2.getFractionalPart(), Fixed_point(fxp2.getFractionalPart()).getDoubleValue());

    printf("Addition result: %f\n", (fxp1+fxp2).getDoubleValue());
    printf("Subtraction result: %f\n", (fxp1-fxp2).getDoubleValue());
    printf("Right shift: %f\n", (fxp1>>10).getDoubleValue());
    printf("Right shift: %f\n", (fxp2>>2).getDoubleValue());

    printf("Left shift: %f\n", (fxp1<<2).getDoubleValue());
    printf("Left shift: %f\n", (fxp2<<3).getDoubleValue());

    Fixed_point fxp_pos1 = Fixed_point(2.3);
    Fixed_point fxp_pos2 = Fixed_point(0.3);
    Fixed_point fxp_neg1 = Fixed_point(-0.46);
    Fixed_point fxp_neg2 = Fixed_point(-4.5);

    printf("fxp_pos1 > fxp_pos2: %u\n", fxp_pos1 > fxp_pos2 ? 1: 0);
    printf("fxp_pos2 < fxp_pos1: %u\n", fxp_pos2 < fxp_pos1 ? 1: 0);
    printf("fxp_neg1 > fxp_neg2: %u\n", fxp_neg1 > fxp_neg2 ? 1: 0);
    printf("fxp_neg2 < fxp_neg1: %u\n", fxp_neg2 < fxp_neg1 ? 1: 0);
    printf("fxp_pos2 > fxp_neg2: %u\n", fxp_pos2 > fxp_neg2 ? 1: 0);
    printf("fxp_neg1 < fxp_pos1: %u\n", fxp_neg1 < fxp_pos1 ? 1: 0);

    printf("FxP value: %u\t Double value: %f\n", fxp_pos1.getNumber(), fxp_pos1.getDoubleValue());
    fxp_pos1 = 4.2;
    printf("FxP value: %u\t Double value: %f\n", fxp_pos1.getNumber(), fxp_pos1.getDoubleValue());
}



