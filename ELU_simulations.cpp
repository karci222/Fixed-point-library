//
// Created by Karol on 28. 5. 2019.
//

#include <cstdio>
#include <cstdint>
#include "ELU_simulations.h"
#include "Fixed_point.h"
#include "Approximations_ELU.h"

#include <cmath>
#include <cstdint>
#include <iostream>
#include <fstream>

using namespace std;

void ELU_simulations::runBKM(uint16_t fractional_bits) {
    printf("ELU BKM range test...\n");
    ofstream file;
    file.open("ELU_BKM_range" + to_string(fractional_bits) + ".txt");

    uint16_t integer_bits = 15 - fractional_bits;

    int j = 0;

    for (short i = -32766; i < 32767; i++){
        Fixed_point i_fxp = Fixed_point((uint16_t)i, integer_bits, fractional_bits);
        uint16_t result = ELU_BKM(i_fxp, Fixed_point(1.0, integer_bits, fractional_bits), 8).getNumber();


        file<<short(i)<< "," << short(result) << endl;
    }

    file.close();
}

void ELU_simulations::runCORDIC(uint16_t fractional_bits) {
        printf("ELU CORDIC range test...\n");
        ofstream file;
        file.open("ELU_CORDIC_range" + to_string(fractional_bits) + ".txt");

        uint16_t integer_bits = 15 - fractional_bits;

        int j = 0;

        for (short i = -32766; i < 32767; i++){
            Fixed_point i_fxp = Fixed_point((uint16_t)i, integer_bits, fractional_bits);
            uint16_t result = ELU_CORDIC(i_fxp, 8, -2).getNumber();


            file<<short(i)<< "," << short(result) << endl;
        }

        file.close();

}

void ELU_simulations::perform_run() {
    for (uint16_t i = 4; i < 10; i++){
        runBKM(i);
        runCORDIC(i);
        runLinear(i);
    }
}

void ELU_simulations::perform_test() {
    for (uint16_t i = 4; i < 10; i++){
        printf("Testing bit length of: %d\n", i);
        testLinear(i, true);
        testBKM(i, true);
        testCORDIC(i, true);
    }
}

void ELU_simulations::runLinear(uint16_t fractional_bits) {
    printf("ELU Linear interpolation range test...\n");
    ofstream file;
    file.open("ELU_Linear_range" + to_string(fractional_bits) + ".txt");

    uint16_t integer_bits = 15 - fractional_bits;

    int j = 0;

    for (short i = -32766; i < 32767; i++){
        Fixed_point i_fxp = Fixed_point((uint16_t)i, integer_bits, fractional_bits);
        uint16_t result = ELU_Linear(i_fxp).getNumber();


        file<<short(i)<< "," << short(result) << endl;
    }

    file.close();
}

void ELU_simulations::testBKM(uint16_t fractional_bits, bool writeFile) {
    printf("BKM ELU approximation test...\n");
    double i = ;
    double di = (double) 1 /(double)(1<<fractional_bits);
    uint16_t integer_bits = 15 - fractional_bits;
    ofstream file;
    ofstream file2;
    ofstream file3;
    if(writeFile) {
        file.open("ELU_BKM" + to_string(fractional_bits) + ".txt");
        file2.open("ELU_BKM_relative" + to_string(fractional_bits) + ".txt");
        file3.open("ELU_BKM_absolute" + to_string(fractional_bits) + ".txt");
    }

    int j = 0;
    double sum = 0;
    double max_abs_error = 0;

    while (i < 0.0){
        Fixed_point i_fxp = Fixed_point(i, integer_bits, fractional_bits);
        Fixed_point e0 = Fixed_point(1.0, integer_bits, fractional_bits);
        double result = ELU_BKM(i, fractional_bits, e0, 8).getDoubleValue();
        double precise = elu(i);
        //printf("For i: %f\t Result: %f\t Precise result: %f\n", i_fxp.getDoubleValue(), result, precise);


        double abs_error = absolute_error(precise, result);
        double rel_error = relative_error(precise, result);
        if(abs_error > max_abs_error){
            max_abs_error = abs_error;
            /*printf("Number: %f\tResult: %f\tPrecise result: %f\tError: %f\n",i,  result, precise, abs_error);
            printf("Number: %f\tFixed point number: %f\tRepresentation: %u\n", i, i_fxp.getDoubleValue(), i_fxp.getNumber());*/
        }

        if(writeFile){
            file<<i<<","<<result<<endl;
            file2<<i<<","<<rel_error<<endl;
            file3<<i<<","<<abs_error<<endl;
        }

        sum += abs_error;
        j+=1;
        i += di;
    }

    if(writeFile){
        file.close();
        file2.close();
        file3.close();
    }

    double average_absolute_error = sum/((double) j);
    printf("Average absolute error: %f\t Maximal absolute error: %f\n", average_absolute_error, max_abs_error);
}

void ELU_simulations::testCORDIC(uint16_t fractional_bits, bool writeFile) {
    printf("CORDIC ELU approximation test...\n");
    double i = -8.0;
    double di = (double) 1 /(double)(1<<fractional_bits);
    uint16_t integer_bits = 15 - fractional_bits;
    ofstream file;
    ofstream file2;
    ofstream file3;
    if(writeFile) {
        file.open("ELU_CORDIC" + to_string(fractional_bits) + ".txt");
        file2.open("ELU_CORDIC_relative" + to_string(fractional_bits) + ".txt");
        file3.open("ELU_CORDIC_absolute" + to_string(fractional_bits) + ".txt");
    }

    int j = 0;
    double sum = 0;
    double max_abs_error = 0;

    while (i < 0.0){
        Fixed_point i_fxp = Fixed_point(i, integer_bits, fractional_bits);
        Fixed_point e0 = Fixed_point(1.0, integer_bits, fractional_bits);
        double result = ELU_CORDIC(i, fractional_bits, 8, -2).getDoubleValue();
        double precise = elu(i);
        //printf("For i: %f\t Result: %f\t Precise result: %f\n", i_fxp.getDoubleValue(), result, precise);


        double abs_error = absolute_error(precise, result);
        double rel_error = relative_error(precise, result);
        if(abs_error > max_abs_error){
            max_abs_error = abs_error;
            /*printf("Number: %f\tResult: %f\tPrecise result: %f\tError: %f\n",i,  result, precise, abs_error);
            printf("Number: %f\tFixed point number: %f\tRepresentation: %u\n", i, i_fxp.getDoubleValue(), i_fxp.getNumber());*/
        }

        if(writeFile){
            file<<i<<","<<result<<endl;
            file2<<i<<","<<rel_error<<endl;
            file3<<i<<","<<abs_error<<endl;
        }

        sum += abs_error;
        j+=1;
        i += di;
    }

    if(writeFile){
        file.close();
        file2.close();
        file3.close();
    }

    double average_absolute_error = sum/((double) j);
    printf("Average absolute error: %f\t Maximal absolute error: %f\n", average_absolute_error, max_abs_error);
}

void ELU_simulations::testLinear(uint16_t fractional_bits, bool writeFile) {
    printf("Linear ELU approximation test...\n");
    double i = -8.0;
    double di = (double) 1 /(double)(1<<fractional_bits);
    uint16_t integer_bits = 15 - fractional_bits;
    ofstream file;
    ofstream file2;
    ofstream file3;
    if(writeFile) {
        file.open("ELU_Linear" + to_string(fractional_bits) + ".txt");
        file2.open("ELU_Linear_relative" + to_string(fractional_bits) + ".txt");
        file3.open("ELU_Linear_absolute" + to_string(fractional_bits) + ".txt");
    }

    int j = 0;
    double sum = 0;
    double max_abs_error = 0;

    while (i < 0.0){
        Fixed_point i_fxp = Fixed_point(i, integer_bits, fractional_bits);
        Fixed_point e0 = Fixed_point(1.0, integer_bits, fractional_bits);
        double result = ELU_Linear(i, fractional_bits).getDoubleValue();
        double precise = elu(i);
        //printf("For i: %f\t Result: %f\t Precise result: %f\n", i_fxp.getDoubleValue(), result, precise);


        double abs_error = absolute_error(precise, result);
        double rel_error = relative_error(precise, result);
        if(abs_error > max_abs_error){
            max_abs_error = abs_error;
            /*printf("Number: %f\tResult: %f\tPrecise result: %f\tError: %f\n",i,  result, precise, abs_error);
            printf("Number: %f\tFixed point number: %f\tRepresentation: %u\n", i, i_fxp.getDoubleValue(), i_fxp.getNumber());*/
        }

        if(writeFile){
            file<<i<<","<<result<<endl;
            file2<<i<<","<<rel_error<<endl;
            file3<<i<<","<<abs_error<<endl;
        }

        sum += abs_error;
        j+=1;
        i += di;
    }

    if(writeFile){
        file.close();
        file2.close();
        file3.close();
    }

    double average_absolute_error = sum/((double) j);
    printf("Average absolute error: %f\t Maximal absolute error: %f\n", average_absolute_error, max_abs_error);
}

double ELU_simulations::elu(double x) {
    if(x >= 0.0){
        return  x;
    }else{
        return exp(x) - 1.0;
    }
}

