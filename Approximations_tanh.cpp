//
// Created by Karol on 4. 5. 2019.
//

#include "Approximations_tanh.h"
#include <cmath>

Fixed_point ALIPPI_SIGMOID(Fixed_point x){
    uint16_t frac_part = x.getFractionalPart();
    Fixed_point x_abs = x.absoluteValue();
    uint16_t integer_part = x_abs.getIntegerPart();





    if(x.getDoubleValue() > 0){
        Fixed_point y = (Fixed_point(0.5, x.getInteger_bits(), x.getFractional_bits()) - (Fixed_point(frac_part, x.getInteger_bits(), x.getFractional_bits()) >> 2)) >> integer_part;
        return Fixed_point(1.0, x.getInteger_bits(), x.getFractional_bits()) - y;
    }else{
        Fixed_point y = (Fixed_point(0.5, x.getInteger_bits(), x.getFractional_bits()) + (Fixed_point(frac_part, x.getInteger_bits(), x.getFractional_bits()) >> 2)) >> integer_part;
        return y;
    }
}

Fixed_point TanH_ALIPPI(Fixed_point x){
    if (x.getNumber() > 0x3FFF && x.getNumber() < 0x8000){
        return {1.0, x.getInteger_bits(), x.getFractional_bits()};
    }else if(x.getNumber() > 0x7FFF && x.getNumber() < 0xC000){
        return {-1.0, x.getInteger_bits(), x.getFractional_bits()};
    }

    Fixed_point x_new = x*Fixed_point(2.0, x.getInteger_bits(), x.getFractional_bits());
    Fixed_point result = ALIPPI_SIGMOID(x_new);
    result = result*Fixed_point(2.0, x.getInteger_bits(), x.getFractional_bits());
    result = result - Fixed_point(1.0, x.getInteger_bits(), x.getFractional_bits());

    return result;
}

Fixed_point TanH_PLAN(Fixed_point x) {
    if (x.getNumber() > 0x3FFF && x.getNumber() < 0x8000){
        return {1.0, x.getInteger_bits(), x.getFractional_bits()};
    }else if(x.getNumber() > 0x7FFF && x.getNumber() < 0xC000){
        return {-1.0, x.getInteger_bits(), x.getFractional_bits()};
    }

    Fixed_point x_new = x << 1;
    Fixed_point result = PLAN_SIGMOID(x_new);
    result = result << 1;
    result = result - Fixed_point(1.0, x.getInteger_bits(), x.getFractional_bits());

    return result;
}

Fixed_point PLAN_SIGMOID(Fixed_point x) {
    Fixed_point y = Fixed_point(0.0, x.getInteger_bits(), x.getFractional_bits());

    Fixed_point x_abs = x.absoluteValue();
    //printf("%f\n", x.absoluteValue().getDoubleValue());
    //printf("%f\n", x.getDoubleValue());

    if (x.absoluteValue().getDoubleValue() >= 5){
        y=Fixed_point(1.0, x.getInteger_bits(), x.getFractional_bits());
    }else if (x.absoluteValue().getDoubleValue() < 5 && x.absoluteValue().getDoubleValue() >= 2.375){
        y = (x.absoluteValue() >> 5) + Fixed_point(0.84375, x.getInteger_bits(), x.getFractional_bits());
    }else if (x.absoluteValue().getDoubleValue() < 2.375 && x.absoluteValue().getDoubleValue() >= 1){
        y = (x.absoluteValue() >> 3) + Fixed_point(0.625, x.getInteger_bits(), x.getFractional_bits());
    }else if (x.absoluteValue().getDoubleValue() < 1 && x.absoluteValue().getDoubleValue() >= 0){
        y = (x.absoluteValue() >> 2) + Fixed_point(0.5, x.getInteger_bits(), x.getFractional_bits());
    }

    if (x.getDoubleValue() < 0){

        y = Fixed_point(1.0, x.getInteger_bits(), x.getFractional_bits()) - y;

        return y;
    }else{
        return y;
    }
}

Fixed_point TanH_A_LAW(Fixed_point x) {
    if (x.getNumber() > 0x3FFF && x.getNumber() < 0x8000){
        return {1.0, x.getInteger_bits(), x.getFractional_bits()};
    }else if(x.getNumber() > 0x7FFF && x.getNumber() < 0xC000){
        return {-1.0, x.getInteger_bits(), x.getFractional_bits()};
    }

    Fixed_point x_new = x << 1;
    Fixed_point result = A_LAW_SIGMOID(x_new);
    result = result << 1;
    result = result - Fixed_point(1.0, x.getInteger_bits(), x.getFractional_bits());

    return result;
}

Fixed_point A_LAW_SIGMOID(Fixed_point x) {
    if (x.getDoubleValue() >= 8){
        return {1.0, x.getInteger_bits(), x.getFractional_bits()};
    }else if(x.getDoubleValue() < 8 && x.getDoubleValue() >= 4){
        return (x>>6) + Fixed_point(0.875, x.getInteger_bits(), x.getFractional_bits());
    }else if(x.getDoubleValue() < 4 && x.getDoubleValue() >= 2){
        return (x>>5) + Fixed_point(0.8125, x.getInteger_bits(), x.getFractional_bits());
    }else if(x.getDoubleValue() < 2 && x.getDoubleValue() >= 1){
        return (x>>3) + Fixed_point(0.625, x.getInteger_bits(), x.getFractional_bits());
    }else if(x.getDoubleValue() < 1 && x.getDoubleValue() >= -1){
        return (x>>2) + Fixed_point(0.5, x.getInteger_bits(), x.getFractional_bits());
    }else if(x.getDoubleValue() < -1.0 && x.getDoubleValue() >= -2){
        return (x>>3) + Fixed_point(0.375, x.getInteger_bits(), x.getFractional_bits());
    }else if(x.getDoubleValue() < -2.0 && x.getDoubleValue() >= -4){
        return (x>>5) + Fixed_point(0.1875, x.getInteger_bits(), x.getFractional_bits());
    }else if(x.getDoubleValue() < -4.0 && x.getDoubleValue() >= -8){
        return (x>>6) + Fixed_point(0.125, x.getInteger_bits(), x.getFractional_bits());
    }else{
        return {0.0, x.getInteger_bits(), x.getFractional_bits()};
    }
}

Fixed_point PLATanH(Fixed_point x) {
    Fixed_point a = Fixed_point(5.5799959, x.getInteger_bits(), x.getFractional_bits());
    Fixed_point b = Fixed_point(3.02, x.getInteger_bits(), x.getFractional_bits());
    Fixed_point c = Fixed_point(2.02, x.getInteger_bits(), x.getFractional_bits());
    Fixed_point d = Fixed_point(1.475, x.getInteger_bits(), x.getFractional_bits());
    Fixed_point e = Fixed_point(1.125, x.getInteger_bits(), x.getFractional_bits());
    Fixed_point f = Fixed_point(0.5, x.getInteger_bits(), x.getFractional_bits());



    Fixed_point x_abs = x.absoluteValue();
    Fixed_point y;

    if (x_abs.getDoubleValue() > a.getDoubleValue()){
        y = Fixed_point(1.0, x.getInteger_bits(), x.getFractional_bits());
    }else if (x_abs.getDoubleValue() <= a.getDoubleValue() && x_abs.getDoubleValue() > b.getDoubleValue()){
        y = (x_abs >> 12) + Fixed_point(0.9986377, x.getInteger_bits(), x.getFractional_bits());
    }else if (x_abs.getDoubleValue() <= b.getDoubleValue() && x_abs.getDoubleValue() > c.getDoubleValue()){
        y = (x_abs >>  5) + Fixed_point(0.905, x.getInteger_bits(), x.getFractional_bits());
    }else if (x_abs.getDoubleValue() <= c.getDoubleValue() && x_abs.getDoubleValue() > d.getDoubleValue()){
        y = (x_abs >>  3) + Fixed_point(0.715625, x.getInteger_bits(), x.getFractional_bits());
    }else if (x_abs.getDoubleValue() <= d.getDoubleValue() && x_abs.getDoubleValue() > e.getDoubleValue()){
        y = (x_abs >>  2) + Fixed_point(0.53125, x.getInteger_bits(), x.getFractional_bits());
    }else if (x_abs.getDoubleValue() <= e.getDoubleValue() && x_abs.getDoubleValue() > f.getDoubleValue()){
        y = (x_abs >>  1) + Fixed_point(0.25, x.getInteger_bits(), x.getFractional_bits());
    }else{
        y = x_abs;
    }

    if (x.isNegative()){
        y = Fixed_point(0.0, x.getInteger_bits(), x.getFractional_bits()) - y;
        return y;
    }else{
        return y;
    }
}

Fixed_point LinearInterpolation(Fixed_point x) {
    double const coefficients[16][2]  = {{0.99482401, 0.        },
                    {0.96452529, 0.00378734},
                    {0.90750989, 0.01804119},
                    {0.83007807, 0.04707812},
                    {0.73986052, 0.0921869 },
                    {0.64439384, 0.15185357},
                    {0.55005321, 0.22260904},
                    {0.46150842, 0.30008574},
                    {0.38165531, 0.37993884},
                    {0.31186056, 0.45845794},
                    {0.25234448, 0.53285304},
                    {0.20257243, 0.60128961},
                    {0.16158377, 0.66277259},
                    {0.12823451, 0.71696515},
                    {0.10135777, 0.76399943},
                    {0.07985856, 0.80431046}};

    int index = x.absoluteValue().getNumber();
    index = index >> (x.getFractional_bits() - 3);


    Fixed_point  y;

    if(x.getDoubleValue() >= 2.0){
        return Fixed_point(1.0, x.getInteger_bits(), x.getFractional_bits() );
    }else if (x.getDoubleValue() <= -2.0){
        return Fixed_point(-1.0, x.getInteger_bits(), x.getFractional_bits() );
    }else{
        y= x.absoluteValue() * Fixed_point(coefficients[index][0], x.getInteger_bits(), x.getFractional_bits()) + Fixed_point(coefficients[index][1], x.getInteger_bits(), x.getFractional_bits());
    }

    if (x.isNegative()){
        return Fixed_point(-1.0, x.getInteger_bits(), x.getFractional_bits()) * y;
    }else{
        return y;
    }
}

Fixed_point QuadraticInterpolation(Fixed_point x) {
    double const coefficients[8][3] = {{ 1.00997338, -0.12119492,  0.        },
                                        { 1.10108943, -0.30972727, -0.01099574},
                                        { 1.16946058, -0.38186672, -0.02714645},
                                        { 1.12559439, -0.35417918, -0.00982105},
                                        { 0.97491074, -0.27917902,  0.06586244},
                                        { 0.77495096, -0.19908818,  0.19067023},
                                        { 0.57844962, -0.13339707,  0.33761723},
                                        { 0.41309638, -0.08599686,  0.48182225}};

    int index = x.absoluteValue().getNumber();
    index = index >> (x.getFractional_bits() - 2);


    Fixed_point  y;

    if(x.getDoubleValue() >= 2.0){
        return Fixed_point(1.0, x.getInteger_bits(), x.getFractional_bits() );
    }else if (x.getDoubleValue() <= -2.0){
        return Fixed_point(-1.0, x.getInteger_bits(), x.getFractional_bits() );
    }else{
        Fixed_point c_1 = Fixed_point(coefficients[index][1], x.getInteger_bits(), x.getFractional_bits());
        Fixed_point c_2 = Fixed_point(coefficients[index][0], x.getInteger_bits(), x.getFractional_bits());
        Fixed_point c_3 = Fixed_point(coefficients[index][2], x.getInteger_bits(), x.getFractional_bits());
        y= x.absoluteValue() * c_1 + c_2;
        y = x.absoluteValue()*y + c_3;
    }

    if (x.isNegative()){
        return Fixed_point(-1.0,x.getInteger_bits(), x.getFractional_bits()) * y;
    }else{
        return y;
    }
}

Fixed_point TanH_A_LAW(double x, uint16_t fractional_bits){
    if (std::abs(x) > Fixed_point(0.0, 15-fractional_bits, fractional_bits).largestNum()){
        if (x > 0){
            return Fixed_point(1.0, (uint16_t )15-fractional_bits, fractional_bits);
        }else{
            return Fixed_point(-1.0, (uint16_t )15-fractional_bits, fractional_bits);
        }
    }else{
        return TanH_A_LAW(Fixed_point(x, (uint16_t )15-fractional_bits, fractional_bits));
    }
}

Fixed_point TanH_PLAN(double x, uint16_t fractional_bits){
    if (std::abs(x) > Fixed_point(0.0, 15-fractional_bits, fractional_bits).largestNum()){
        if (x > 0){
            return Fixed_point(1.0, (uint16_t )15-fractional_bits, fractional_bits);
        }else{
            return Fixed_point(-1.0, (uint16_t )15-fractional_bits, fractional_bits);
        }
    }else{
        return TanH_PLAN(Fixed_point(x, (uint16_t )15-fractional_bits, fractional_bits));
    }
}

Fixed_point TanH_ALIPPI(double x, uint16_t fractional_bits){
    if (std::abs(x) > Fixed_point(0.0, 15-fractional_bits, fractional_bits).largestNum()){
        if (x > 0){
            return Fixed_point(1.0, (uint16_t )15-fractional_bits, fractional_bits);
        }else{
            return Fixed_point(-1.0, (uint16_t )15-fractional_bits, fractional_bits);
        }
    }else{
        return TanH_ALIPPI(Fixed_point(x, (uint16_t )15-fractional_bits, fractional_bits));
    }
}

Fixed_point PLATanH(double x, uint16_t fractional_bits){
    if (std::abs(x) > Fixed_point(0.0, 15-fractional_bits, fractional_bits).largestNum()){
        if (x > 0){
            return Fixed_point(1.0, (uint16_t )15-fractional_bits, fractional_bits);
        }else{
            return Fixed_point(-1.0, (uint16_t )15-fractional_bits, fractional_bits);
        }
    }else{
        return PLATanH(Fixed_point(x, (uint16_t )15-fractional_bits, fractional_bits));
    }
}

Fixed_point Linear_interpolation(double x, uint16_t fractional_bits){
    if (std::abs(x) > Fixed_point(0.0, 15-fractional_bits, fractional_bits).largestNum()){
        if (x > 0){
            return Fixed_point(1.0, (uint16_t )15-fractional_bits, fractional_bits);
        }else{
            return Fixed_point(-1.0, (uint16_t )15-fractional_bits, fractional_bits);
        }
    }else{
        return LinearInterpolation(Fixed_point(x, (uint16_t )15-fractional_bits, fractional_bits));
    }
}

Fixed_point Quadratic_interpolation(double x, uint16_t fractional_bits){
    if (std::abs(x) > Fixed_point(0.0, 15-fractional_bits, fractional_bits).largestNum()){
        if (x > 0){
            return Fixed_point(1.0, (uint16_t )15-fractional_bits, fractional_bits);
        }else{
            return Fixed_point(-1.0, (uint16_t )15-fractional_bits, fractional_bits);
        }
    }else{
        return QuadraticInterpolation(Fixed_point(x, (uint16_t )15-fractional_bits, fractional_bits));
    }
}
