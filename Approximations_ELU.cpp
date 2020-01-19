//
// Created by Karol on 27. 5. 2019.
//

#include <cstdlib>
#include <cstdio>
#include "Approximations_ELU.h"
#include "BKM.h"
#include "CORDIC.h"

Fixed_point ELU_BKM(Fixed_point x, Fixed_point e0, int iterations)
{
    if (x.isNegative()) {
        if(x > Fixed_point(-8.0, x.getInteger_bits(), x.getFractional_bits())) {
            BKM bkm = BKM(x.getFractional_bits(), x.getInteger_bits());
            Fixed_point *result = bkm.bkm_range_reduced(x, e0, iterations);

            return result[0] - e0;
        }else{
            return Fixed_point(0.0, x.getInteger_bits(), x.getFractional_bits()) - e0;
        }
    }else
    {
        return x;
    }
}
Fixed_point ELU_CORDIC(Fixed_point x, int max_iterations, int m)
{
    if (x.isNegative()) {
        if(x > Fixed_point(-5.16, x.getInteger_bits(), x.getFractional_bits())) {

            CORDIC cordic = CORDIC(x.getFractional_bits(), x.getInteger_bits());
            Fixed_point *result = cordic.cordic_rotate(
                    Fixed_point(10.81507534030689, x.getInteger_bits(), x.getFractional_bits()),
                    Fixed_point(0.0, x.getInteger_bits(), x.getFractional_bits()),
                    x,
                    -1, 8, -2);

            return (result[0] + result[1]) - Fixed_point(1.0, x.getInteger_bits(), x.getFractional_bits());
        } else{
            return Fixed_point(-1.0, x.getInteger_bits(), x.getFractional_bits());
        }
    } else{
        return x;
    }
}
Fixed_point ELU_Linear(Fixed_point x){
    double const coefficients[32][2]  = {{ 0.01950959, -0.90364599},
                                         { 0.02210726, -0.89358001},
                                         { 0.02505081, -0.88254171},
                                         { 0.02838629, -0.87045061},
                                         { 0.03216588, -0.85722204},
                                         { 0.03644872, -0.84276746},
                                         { 0.04130181, -0.82699492},
                                         { 0.04680108, -0.8098097 },
                                         { 0.05303257, -0.79111522},
                                         { 0.06009377, -0.77081426},
                                         { 0.06809517, -0.74881043},
                                         { 0.07716193, -0.72501017},
                                         { 0.08743592, -0.69932519},
                                         { 0.09907788, -0.67167554},
                                         { 0.11226995, -0.64199339},
                                         { 0.12721852, -0.61022768},
                                         { 0.14415747, -0.57634978},
                                         { 0.16335181, -0.54036038},
                                         { 0.18510185, -0.50229781},
                                         { 0.20974788, -0.46224802},
                                         { 0.23767549, -0.42035661},
                                         { 0.26932161, -0.37684319},
                                         { 0.30518136, -0.3320185 },
                                         { 0.34581579, -0.28630477},
                                         { 0.39186063, -0.24025993},
                                         { 0.44403626, -0.19460625},
                                         { 0.50315901, -0.15026419},
                                         { 0.57015385, -0.10839242},
                                         { 0.64606895, -0.07043486},
                                         { 0.73209203, -0.03817621},
                                         { 0.82956896, -0.01380698},
                                         { 0.94002478,  0.        }};

    int index = x.absoluteValue().getNumber();
    index =  31 - (index >> (x.getFractional_bits() - 3));


    Fixed_point  y;

    if(!x.isNegative()){
        return x;
    }else if (x.getDoubleValue() <= -4.0){
        return Fixed_point(-1.0, x.getInteger_bits(), x.getFractional_bits() );
    }else{
        y= x * Fixed_point(coefficients[index][0], x.getInteger_bits(), x.getFractional_bits()) + Fixed_point(coefficients[index][1], x.getInteger_bits(), x.getFractional_bits());
        return y;
    }
}

Fixed_point ELU_BKM(double x, int  fractional_bits, Fixed_point e0, int iterations)
{
    return ELU_BKM(Fixed_point(x, e0.getInteger_bits(), e0.getFractional_bits()), e0, iterations);
}
Fixed_point ELU_CORDIC(double x, int fractional_bits, int max_iterations, int m)
{
    return ELU_CORDIC(Fixed_point(x, (uint16_t )16 - (uint16_t  )fractional_bits, (uint16_t) fractional_bits), max_iterations, m);
}
Fixed_point ELU_Linear(double x, int fractional_bits)
{
    return ELU_Linear(Fixed_point(x, (uint16_t)16 - (uint16_t)fractional_bits, (uint16_t)fractional_bits));
}
