//
// Created by Karol on 4. 5. 2019.
//

#include "Simulator.h"
#include <cmath>

double Simulator::absolute_error(double precise, double approximate){
    return std::abs(precise - approximate);
}
double Simulator::relative_error(double precise, double approximate){
    return std::abs(1-(approximate/precise));
}