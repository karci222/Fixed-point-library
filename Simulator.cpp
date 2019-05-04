//
// Created by Karol on 4. 5. 2019.
//

#include "Simulator.h"

double Simulator::absolute_error(double precise, double approximate){
    return abs(precise - approximate);
}
double Simulator::relative_error(double precise, double approximate){
    return abs(1-(approximate/precise));
}