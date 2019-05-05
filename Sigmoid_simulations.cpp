//
// Created by Karol on 4. 5. 2019.
//

#include "Sigmoid_simulations.h"


void Sigmoid_simulations::testPLAN(uint16_t fractional_bits, bool writeFile){
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
        double result = PLAN(i, fractional_bits).getDoubleValue();
        double precise = sigmoid(i);
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

void Sigmoid_simulations::testA_LAW(uint16_t fractional_bits, bool writeFile){
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
        double result = A_LAW(i, fractional_bits).getDoubleValue();
        double precise = sigmoid(i);

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

void Sigmoid_simulations::testIterative(int q, uint16_t fractional_bits, bool writeFile){
    printf("Iterative %d approximation test...\n", q);
    double i = -15.0;
    double di = (double) 1 /(double)(1<<fractional_bits);
    uint16_t integer_bits = 15 - fractional_bits;
    ofstream file;
    ofstream file2;
    ofstream file3;
    if(writeFile) {
        file.open("Iterative_without_rounding" + to_string(fractional_bits)+"_"+ to_string(q) + ".txt");
        file2.open("Iterative_relative_without_rounding_fxp" + to_string(fractional_bits) + "_" + to_string(q) + ".txt");
        file3.open("Iterative_absolute_without_rounding_fxp" + to_string(fractional_bits) + "_" + to_string(q) + ".txt");
    }


    int j = 0;
    double sum = 0;
    double max_abs_error = 0;

    while (i < 15.0){
        Fixed_point i_fxp = Fixed_point(i, integer_bits, fractional_bits);
        double result = ITERATIVE(i, q, fractional_bits).getDoubleValue();
        double precise = sigmoid(i);
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

void Sigmoid_simulations::testALIPPI(uint16_t fractional_bits, bool writeFile){
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
        double result = ALIPPI(i, fractional_bits).getDoubleValue();
        double precise = sigmoid(i);
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

void Sigmoid_simulations::testPOLYNOMIAL(uint16_t fractional_bits, bool writeFile){
    printf("Polynomial approximation test...\n");
    double i = -15.0;
    double di = (double) 1 /(double)(1<<fractional_bits);
    uint16_t integer_bits = 15 - fractional_bits;
    ofstream file;
    ofstream file2;
    ofstream file3;
    if(writeFile) {
        file.open("Polynomial_without_rounding" + to_string(fractional_bits) + ".txt");
        file2.open("Polynomial_relative_without_rounding" + to_string(fractional_bits) + ".txt");
        file3.open("Polynomial_absolute_without_rounding" + to_string(fractional_bits) + ".txt");
    }

    int j = 0;
    double sum = 0;
    double max_abs_error = 0;

    while (i < 15.0){
        Fixed_point i_fxp = Fixed_point(i, integer_bits, fractional_bits);
        double result = POLYNOMIALLINEAR(i, fractional_bits).getDoubleValue();
        double precise = sigmoid(i);
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

void Sigmoid_simulations::testPOLYNOMIALQUADRATIC(uint16_t fractional_bits, bool writeFile){
    printf("Polynomial quadratic approximation test...\n");
    double i = -15.0;
    double di = (double) 1 /(double)(1<<fractional_bits);
    uint16_t integer_bits = 15 - fractional_bits;
    ofstream file;
    ofstream file2;
    ofstream file3;
    if(writeFile) {
        file.open("Polynomial_quadratic_without_rounding" + to_string(fractional_bits) + ".txt");
        file2.open("Polynomial_quadratic_relative_without_rounding" + to_string(fractional_bits) + ".txt");
        file3.open("Polynomial_quadratic_absolute_without_rounding" + to_string(fractional_bits) + ".txt");
    }

    int j = 0;
    double sum = 0;
    double max_abs_error = 0;

    while (i < 15.0){
        Fixed_point i_fxp = Fixed_point(i, integer_bits, fractional_bits);
        double result = POLYNOMIALQUADRATIC(i, fractional_bits).getDoubleValue();
        double precise = sigmoid(i);
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

void Sigmoid_simulations::runPLAN(uint16_t fractional_bits){
    printf("PLAN range test...\n");
    ofstream file;
    file.open("PLAN_range" + to_string(fractional_bits) + ".txt");

    uint16_t integer_bits = 15 - fractional_bits;

    int j = 0;

    for (uint16_t i = 0; i < 0xFFFF; i++){
        Fixed_point i_fxp = Fixed_point(i, integer_bits, fractional_bits);
        uint16_t result = PLAN(i_fxp).getNumber();


        file<<short(i)<< "," << result << endl;
    }

    file.close();
}

void runALIPPI(uint16_t fractional_bits){
    printf("ALIPPI range test...\n");
    ofstream file;
    file.open("ALIPPI_range" + to_string(fractional_bits) + ".txt");

    uint16_t integer_bits = 15 - fractional_bits;

    int j = 0;

    for (uint16_t i = 0; i < 0xFFFF; i++){
        Fixed_point i_fxp = Fixed_point(i, integer_bits, fractional_bits);
        uint16_t result = ALIPPI(i_fxp).getNumber();


        file<<short(i)<< "," << result << endl;
    }

    file.close();
}

void Sigmoid_simulations::runA_LAW(uint16_t fractional_bits){
    printf("A_LAW range test...\n");
    ofstream file;
    file.open("A_LAW_range" + to_string(fractional_bits) + ".txt");

    uint16_t integer_bits = 15 - fractional_bits;

    int j = 0;

    for (uint16_t i = 0; i < 0xFFFF; i++){
        Fixed_point i_fxp = Fixed_point(i, integer_bits, fractional_bits);
        uint16_t result = A_LAW(i_fxp).getNumber();


        file<<short(i)<< "," << result << endl;
    }

    file.close();
}

void Sigmoid_simulations::runIterative(int q,uint16_t fractional_bits){
    cout<<"Iterative " + to_string(q) + " range test..."<<endl;
    ofstream file;
    file.open("Iterative_" + to_string(q) + "_range" + to_string(fractional_bits) + ".txt");

    uint16_t integer_bits = 15 - fractional_bits;

    int j = 0;

    for (uint16_t i = 0; i < 0xFFFF; i++){
        Fixed_point i_fxp = Fixed_point(i, integer_bits, fractional_bits);
        uint16_t result = ITERATIVE(i_fxp, q).getNumber();


        file<<short(i)<< "," << result << endl;
    }

    file.close();
}

void Sigmoid_simulations::runLinear(uint16_t fractional_bits){
    printf("Linear range test...\n");
    ofstream file;
    file.open("Linear_range" + to_string(fractional_bits) + ".txt");

    uint16_t integer_bits = 15 - fractional_bits;

    int j = 0;

    for (uint16_t i = 0; i < 0xFFFF; i++){
        Fixed_point i_fxp = Fixed_point(i, integer_bits, fractional_bits);
        uint16_t result = POLYNOMIALLINEAR(i_fxp).getNumber();


        file<<short(i)<< "," << short(result) << endl;
    }

    file.close();
}

void Sigmoid_simulations::runQuadratic(uint16_t fractional_bits){
    printf("Quadratic range test...\n");
    ofstream file;
    file.open("Quadratic_range" + to_string(fractional_bits) + ".txt");

    uint16_t integer_bits = 15 - fractional_bits;

    int j = 0;

    for (uint16_t i = 0; i < 0xFFFF; i++){
        Fixed_point i_fxp = Fixed_point(i, integer_bits, fractional_bits);
        uint16_t result = POLYNOMIALQUADRATIC(i_fxp).getNumber();


        file<<short(i)<< "," << short(result) << endl;
    }

    file.close();
}