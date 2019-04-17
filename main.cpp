#include <iostream>
#include <cmath>
#include <fstream>
#include "Fixed_point.h"
#include "Approximations.h"

using namespace std;

double sigmoid(double x);
void basicExamples();
void averageAndMaximalError(int print, uint16_t fractional_bits);
void operatorsTest();
void testPLAN(uint16_t fractional_bits, bool writeFile);
void testA_LAW(uint16_t fractional_bits, bool writeFile);
void testALIPPI(uint16_t fractional_bits, bool writeFile);
void testIterative(int q, uint16_t fractional_bits, bool writeFile);
void testPOLYNOMIAL(uint16_t fractional_bits, bool writeFile);
void testPOLYNOMIALQUADRATIC(uint16_t fractional_bits, bool writeFile);
double absolute_error(double precise, double approximate);
double relative_error(double precise, double approximate);

int main() {
    basicExamples();
    //averageAndMaximalError(0);
    operatorsTest();

    /*for (uint16_t i = 4; i < 14; i++) {
        averageAndMaximalError(false, i);
    }*/
    
    for(uint16_t i = 4; i < 13; i++) {
        printf("Testing the approximations for fractional bits: %u\n", i);
        testPLAN(i, true);
        testA_LAW(i, true);
        testALIPPI(i, true);
        testIterative(0, i, true);
        testIterative(1, i, true);
        testIterative(2, i, true);
        testIterative(3, i, true);
        testPOLYNOMIAL(i, true);
        testPOLYNOMIALQUADRATIC(i, true);
        putchar('\n');
        putchar('\n');
    }

    return 0;
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

double sigmoid(double x){
    return (double)1/((double)1 + exp(-x));
}

void testPLAN(uint16_t fractional_bits, bool writeFile){
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

void testA_LAW(uint16_t fractional_bits, bool writeFile){
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

void testIterative(int q, uint16_t fractional_bits, bool writeFile){
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

void testALIPPI(uint16_t fractional_bits, bool writeFile){
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

void testPOLYNOMIAL(uint16_t fractional_bits, bool writeFile){
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

void testPOLYNOMIALQUADRATIC(uint16_t fractional_bits, bool writeFile){
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

double absolute_error(double precise, double approximate){
    return abs(precise - approximate);
}
double relative_error(double precise, double approximate){
    return abs(1-(approximate/precise));
}