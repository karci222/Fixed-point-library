//
// Created by Karol on 21. 2. 2019.
//

#include <cstdio>
#include <cstdlib>
#include "Approximations.h"


Fixed_point POLYNOMIALLINEAR(Fixed_point x){
    double const coefficients[32][2] = {{0.24967499, 0.5       },
                           {0.24773702, 0.50024225},
                           {0.24392079, 0.5011963 },
                           {0.23834185, 0.50328841},
                           {0.23116427, 0.5068772 },
                           {0.22259068, 0.51223569},
                           {0.21285063, 0.51954073},
                           {0.20218841, 0.52887017},
                           {0.19085127, 0.54020731},
                           {0.17907899, 0.55345112},
                           {0.16709533, 0.5684307 },
                           {0.15510159, 0.58492209},
                           {0.14327249, 0.60266575},
                           {0.13175412, 0.62138309},
                           {0.12066366, 0.64079139},
                           {0.11009055, 0.66061599},
                           {0.10009862, 0.68059983},
                           {0.09072903, 0.70051021},
                           {0.08200336, 0.72014298},
                           {0.07392692, 0.73932452},
                           {0.06649191, 0.75791204},
                           {0.05968033, 0.77579245},
                           {0.05346656, 0.7928803 },
                           {0.04781965, 0.80911517},
                           {0.04270516, 0.82445864},
                           {0.03808672, 0.83889126},
                           {0.03392727, 0.85240948},
                           {0.03018998, 0.86502284},
                           {0.02683899, 0.87675131},
                           {0.0238399 , 0.88762301},
                           {0.02116013, 0.89767213},
                           {0.01876915, 0.9069372 }};

    int index = x.absoluteValue().getNumber();
    index = index >> (x.getFractional_bits() - 3);


    Fixed_point  y;

    if(x.getDoubleValue() >= 4.0){
        return Fixed_point(1.0, x.getInteger_bits(), x.getFractional_bits() );
    }else if (x.getDoubleValue() <= -4.0){
        return Fixed_point(0.0, x.getInteger_bits(), x.getFractional_bits() );
    }else{
        y= x.absoluteValue() * Fixed_point(coefficients[index][0], x.getInteger_bits(), x.getFractional_bits()) + coefficients[index][1];
    }

    if (x.isNegative()){
        return Fixed_point(1.0,x.getInteger_bits(), x.getFractional_bits()) - y;
    }else{
        return y;
    }
}

Fixed_point POLYNOMIALLINEAR(double x, uint16_t fractional_bits){
    if (abs(x) > Fixed_point(0.0, 15-fractional_bits, fractional_bits).largestNum()){
        if (x > 0){
            return Fixed_point(1.0, (uint16_t )15-fractional_bits, fractional_bits);
        }else{
            return Fixed_point(0.0, (uint16_t )15-fractional_bits, fractional_bits);
        }
    }else{
        return POLYNOMIALLINEAR(Fixed_point(x, (uint16_t )15-fractional_bits, fractional_bits));
    }
}

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