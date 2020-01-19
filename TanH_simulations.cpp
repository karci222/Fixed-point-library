//
// Created by Karol on 5. 5. 2019.
//

#include "TanH_simulations.h"
#include "Approximations_tanh.h"
#include <cmath>
#include <cstdint>
#include <iostream>
#include <fstream>

using namespace std;

double TanH_simulations::TanH(double x) {
    return tanh(x);
}

void TanH_simulations::runPLAN(uint16_t fractional_bits) {
    printf("TanH PLAN range test...\n");
    ofstream file;
    file.open("TanH_PLAN_range" + to_string(fractional_bits) + ".txt");

    uint16_t integer_bits = 15 - fractional_bits;

    int j = 0;

    for (short i = -32766; i < 32767; i++){
        Fixed_point i_fxp = Fixed_point((uint16_t)i, integer_bits, fractional_bits);
        uint16_t result = TanH_PLAN(i_fxp).getNumber();


        file<<short(i)<< "," << short(result) << endl;
    }

    file.close();
}

void TanH_simulations::runALIPPI(uint16_t fractional_bits) {
    printf("TanH ALIPPI range test...\n");
    ofstream file;
    file.open("TanH_ALIPPI_range" + to_string(fractional_bits) + ".txt");

    uint16_t integer_bits = 15 - fractional_bits;

    int j = 0;

    for (short i = -32766; i < 32767; i++){
        //printf("%d\n", i);
        Fixed_point i_fxp = Fixed_point((uint16_t)i, integer_bits, fractional_bits);
        uint16_t result = TanH_ALIPPI(i_fxp).getNumber();


        file<<short(i)<< "," << short(result) << endl;
    }

    file.close();
}

void TanH_simulations::runA_LAW(uint16_t fractional_bits) {
    printf("TanH A_LAW range test...\n");
    ofstream file;
    file.open("TanH_A_LAW_range" + to_string(fractional_bits) + ".txt");

    uint16_t integer_bits = 15 - fractional_bits;

    int j = 0;

    for (short i = -32766; i < 32767; i++){
        Fixed_point i_fxp = Fixed_point((uint16_t)i, integer_bits, fractional_bits);
        uint16_t result = TanH_A_LAW(i_fxp).getNumber();


        file<<short(i)<< "," << short(result) << endl;
    }

    file.close();
}

void TanH_simulations::runPLATanH(uint16_t fractional_bits) {
    printf("TanH PLATanH range test...\n");
    ofstream file;
    file.open("TanH_PLATanH_range" + to_string(fractional_bits) + ".txt");

    uint16_t integer_bits = 15 - fractional_bits;

    int j = 0;

    for (short i = -32766; i < 32767; i++){
        Fixed_point i_fxp = Fixed_point((uint16_t)i, integer_bits, fractional_bits);
        uint16_t result = PLATanH(i_fxp).getNumber();


        file<<short(i)<< "," << short(result) << endl;
    }

    file.close();
}

void TanH_simulations::runLinear(uint16_t fractional_bits) {
    printf("TanH linear interpolation range test...\n");
    ofstream file;
    file.open("TanH_Linear_range" + to_string(fractional_bits) + ".txt");

    uint16_t integer_bits = 15 - fractional_bits;

    int j = 0;

    for (short i = -32766; i < 32767; i++){
        Fixed_point i_fxp = Fixed_point((uint16_t)i, integer_bits, fractional_bits);
        uint16_t result = LinearInterpolation(i_fxp).getNumber();


        file<<short(i)<< "," << short(result) << endl;
    }

    file.close();
}

void TanH_simulations::runQuadratic(uint16_t fractional_bits) {
    printf("TanH quadratic range test...\n");
    ofstream file;
    file.open("TanH_Quadratic_range" + to_string(fractional_bits) + ".txt");

    uint16_t integer_bits = 15 - fractional_bits;

    int j = 0;

    for (short i = -32766; i < 32767; i++){
        Fixed_point i_fxp = Fixed_point((uint16_t)i, integer_bits, fractional_bits);
        uint16_t result = QuadraticInterpolation(i_fxp).getNumber();


        file<<short(i)<< "," << short(result) << endl;
    }

    file.close();
}

void TanH_simulations::perform_run() {
    for (uint16_t i = 4; i < 14; i++){
        runA_LAW(i);
        runALIPPI(i);
        runPLAN(i);
        /*runPLATanH(i);
        runLinear(i);
        runQuadratic(i);*/
    }
}

void TanH_simulations::testPLAN(uint16_t fractional_bits, bool writeFile) {
    printf("PLAN approximation test...\n");
    ofstream file;
    ofstream file2;
    ofstream file3;
    if(writeFile) {
        file.open("PLAN_without_rounding" + to_string(fractional_bits) + ".txt");
        file2.open("PLAN_relative_without_rounding_fxp" + to_string(fractional_bits) + ".txt");
        file3.open("PLAN_absolute_without_error_fxp" + to_string(fractional_bits) + ".txt");
    }
    double i = -15.0;
    double di = (double) 1 /(double)(1<<fractional_bits);

    uint16_t integer_bits = 15 - fractional_bits;

    int j = 0;
    double sum = 0;
    double max_abs_error = 0;

    while (i < 15.0){
        Fixed_point i_fxp = Fixed_point(i, integer_bits, fractional_bits);
        double result = TanH_PLAN(i, fractional_bits).getDoubleValue();
        double precise = TanH(i);
        //printf("For i: %f\t Result: %f\t Precise result: %f\n", i_fxp.getDoubleValue(), result, precise);

        double abs_error = absolute_error(precise, result);
        double rel_error = relative_error(precise, result);
        if(abs_error > max_abs_error){
            max_abs_error = abs_error;
            /*printf("Number: %f\tResult: %f\tPrecise result: %f\tError: %f\n",i,  result, precise, abs_error);
            printf("Number: %f\tFixed point number: %f\tRepresentation: %u\n", i, i_fxp.getDoubleValue(), i_fxp.getNumber());*/
        }

        if(writeFile) {
            file<<i<< "," << result << endl;
            file2<<i<<","<<rel_error<<endl;
            file3<<i<<","<<abs_error<<endl;
        }

        sum += abs_error;
        j+=1;
        i += di;
    }

    double average_absolute_error = sum/((double) j);
    printf("Average absolute error: %f\t Maximal absolute error: %f\n", average_absolute_error, max_abs_error);
    if(writeFile) {
        file.close();
        file2.close();
        file3.close();
    }
}

void TanH_simulations::testA_LAW(uint16_t fractional_bits, bool writeFile) {
    printf("A-Law approximation test...\n");
    double i = -15.0;
    double di = (double) 1 /(double)(1<<fractional_bits);
    uint16_t integer_bits = 15 - fractional_bits;
    ofstream file;
    ofstream file2;
    ofstream file3;
    if(writeFile) {
        file.open("A_LAW_without_rounding" + to_string(fractional_bits) + ".txt");
        file2.open("A_LAW_relative_without_rounding_fxp" + to_string(fractional_bits) + ".txt");
        file3.open("A_LAW_absolute_without_rounding_fxp" + to_string(fractional_bits) + ".txt");
    }


    int j = 0;
    double sum = 0;
    double max_abs_error = 0;
    while (i < 15.0){
        Fixed_point i_fxp = Fixed_point(i, integer_bits, fractional_bits);
        double result = TanH_A_LAW(i, fractional_bits).getDoubleValue();
        double precise = TanH(i);

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
    }

    double average_absolute_error = sum/((double) j);
    printf("Average absolute error: %f\t Maximal absolute error: %f\n", average_absolute_error, max_abs_error);
}

void TanH_simulations::testALIPPI(uint16_t fractional_bits, bool writeFile) {
    printf("Alippi approximation test...\n");
    double i = -15.0;
    double di = (double) 1 /(double)(1<<fractional_bits);
    uint16_t integer_bits = 15 - fractional_bits;
    ofstream file;
    ofstream file2;
    ofstream file3;
    if(writeFile) {
        file.open("ALIPPI_without_rounding" + to_string(fractional_bits) + ".txt");
        file2.open("ALIPPI_relative_without_rounding" + to_string(fractional_bits) + ".txt");
        file3.open("ALIPPI_absolute_without_rounding" + to_string(fractional_bits) + ".txt");
    }

    int j = 0;
    double sum = 0;
    double max_abs_error = 0;

    while (i < 15.0){
        Fixed_point i_fxp = Fixed_point(i, integer_bits, fractional_bits);
        double result = TanH_ALIPPI(i, fractional_bits).getDoubleValue();
        double precise = TanH(i);
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

void TanH_simulations::testPLATanH(uint16_t fractional_bits, bool writeFile) {
    printf("PLATanH approximation test...\n");
    double i = -15.0;
    double di = (double) 1 /(double)(1<<fractional_bits);
    uint16_t integer_bits = 15 - fractional_bits;
    ofstream file;
    ofstream file2;
    ofstream file3;
    if(writeFile) {
        file.open("PLATanH_without_rounding" + to_string(fractional_bits) + ".txt");
        file2.open("PLATanH_relative_without_rounding" + to_string(fractional_bits) + ".txt");
        file3.open("PLATanH_absolute_without_rounding" + to_string(fractional_bits) + ".txt");
    }

    int j = 0;
    double sum = 0;
    double max_abs_error = 0;

    while (i < 15.0){
        Fixed_point i_fxp = Fixed_point(i, integer_bits, fractional_bits);
        double result = PLATanH(i, fractional_bits).getDoubleValue();
        double precise = TanH(i);
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

void TanH_simulations::testLinear(uint16_t fractional_bits, bool writeFile) {
    printf("Linear approximation test...\n");
    double i = -15.0;
    double di = (double) 1 /(double)(1<<fractional_bits);
    uint16_t integer_bits = 15 - fractional_bits;
    ofstream file;
    ofstream file2;
    ofstream file3;
    if(writeFile) {
        file.open("Linear_without_rounding" + to_string(fractional_bits) + ".txt");
        file2.open("Linear_relative_without_rounding" + to_string(fractional_bits) + ".txt");
        file3.open("Linear_absolute_without_rounding" + to_string(fractional_bits) + ".txt");
    }

    int j = 0;
    double sum = 0;
    double max_abs_error = 0;

    while (i < 15.0){
        Fixed_point i_fxp = Fixed_point(i, integer_bits, fractional_bits);
        double result = Linear_interpolation(i, fractional_bits).getDoubleValue();
        double precise = TanH(i);
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

void TanH_simulations::testQuadratic(uint16_t fractional_bits, bool writeFile) {
    printf("Quadratic approximation test...\n");
    double i = -15.0;
    double di = (double) 1 /(double)(1<<fractional_bits);
    uint16_t integer_bits = 15 - fractional_bits;
    ofstream file;
    ofstream file2;
    ofstream file3;
    if(writeFile) {
        file.open("Quadratic_without_rounding" + to_string(fractional_bits) + ".txt");
        file2.open("Quadratic_relative_without_rounding" + to_string(fractional_bits) + ".txt");
        file3.open("Quadratic_absolute_without_rounding" + to_string(fractional_bits) + ".txt");
    }

    int j = 0;
    double sum = 0;
    double max_abs_error = 0;

    while (i < 15.0){
        Fixed_point i_fxp = Fixed_point(i, integer_bits, fractional_bits);
        double result = Quadratic_interpolation(i, fractional_bits).getDoubleValue();
        double precise = TanH(i);
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

void TanH_simulations::perform_test() {
    for (int i = 4; i <= 12; ++i) {
        printf("For fractional bits: %d\n", i);
        testA_LAW(i, true);
        //testALIPPI(i, true);
        testPLAN(i, true);
        /*testPLATanH(i, true);
        testLinear(i, true);
        testQuadratic(i, true);*/
    }
}

