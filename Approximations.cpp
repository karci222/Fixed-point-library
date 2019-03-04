//
// Created by Karol on 21. 2. 2019.
//

#include <cstdio>
#include <cstdlib>
#include "Approximations.h"

Fixed_point PLAN(Fixed_point x) {
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

Fixed_point A_LAW(Fixed_point x){
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
Fixed_point ALIPPI(Fixed_point x){
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

Fixed_point ITERATIVE(Fixed_point x, int q){
    double delta = 0.30895;
    bool negative = true;

    if (x.getDoubleValue() >= 0){
        double new_x = (-1)*x.getDoubleValue();
        x = new_x;
        negative = false;
    }

    switch(q){
        case 0:
            delta = 0.30895;
            break;
        case 1:
            delta = 0.28094;
            break;
        case 2:
            delta = 0.26588;
            break;
        case 3:
            delta = 0.26380;
            break;
        default:
            printf("Wrong q... Using q = 2\n");
            q = 2;
            delta = 0.26588;
    }

    Fixed_point fxpdelta = Fixed_point(delta, x.getInteger_bits(), x.getFractional_bits());
    Fixed_point g = Fixed_point(0.0, x.getInteger_bits(), x.getFractional_bits());
    Fixed_point h = (Fixed_point(1.0, x.getInteger_bits(), x.getFractional_bits()) + x>>1)>>1;

    for (int i = 0; i <= q; i++){
        Fixed_point g_dot = (g > h) ? g: h;
        h = (g + h + fxpdelta)>>1;
        g = g_dot;
        fxpdelta = fxpdelta>>2;
    }

    g = g > h ? g: h;

    if(negative){
        return g;
    }else{
        return Fixed_point(1.0, x.getInteger_bits(), x.getFractional_bits()) - g;
    }

}

Fixed_point PLAN(double x, uint16_t fractional_bits){
    if (abs(x) > Fixed_point(0.0, 15-fractional_bits, fractional_bits).largestNum()){
        if (x > 0){
            return Fixed_point(1.0, (uint16_t )15-fractional_bits, fractional_bits);
        }else{
            return Fixed_point(0.0, (uint16_t )15-fractional_bits, fractional_bits);
        }
    }else{
        return PLAN(Fixed_point(x, (uint16_t )15-fractional_bits, fractional_bits));
    }
}

Fixed_point A_LAW(double x, uint16_t fractional_bits){
    if (abs(x) > Fixed_point(0.0, 15-fractional_bits, fractional_bits).largestNum()){
        if (x > 0){
            return Fixed_point(1.0, (uint16_t )15-fractional_bits, fractional_bits);
        }else{
            return Fixed_point(0.0, (uint16_t )15-fractional_bits, fractional_bits);
        }
    }else{
        return A_LAW(Fixed_point(x, (uint16_t )15-fractional_bits, fractional_bits));
    }
}

Fixed_point ALIPPI(double x, uint16_t fractional_bits){
    if (abs(x) > Fixed_point(0.0, 15-fractional_bits, fractional_bits).largestNum()){
        if (x > 0){
            return Fixed_point(1.0, (uint16_t )15-fractional_bits, fractional_bits);
        }else{
            return Fixed_point(0.0, (uint16_t )15-fractional_bits, fractional_bits);
        }
    }else{
        return ALIPPI(Fixed_point(x, (uint16_t )15-fractional_bits, fractional_bits));
    }
}

Fixed_point ITERATIVE(double x, int q, uint16_t fractional_bits){
    if (abs(x) > Fixed_point(0.0, 15-fractional_bits, fractional_bits).largestNum()){
        if (x > 0){
            return Fixed_point(1.0, (uint16_t )15-fractional_bits, fractional_bits);
        }else{
            return Fixed_point(0.0, (uint16_t )15-fractional_bits, fractional_bits);
        }
    }else{
        return ITERATIVE(Fixed_point(x, (uint16_t )15-fractional_bits, fractional_bits), q);
    }
}