//
// Created by Karol on 4. 5. 2019.
//

#ifndef APPROXIMATIONTESTS_SIMULATOR_H
#define APPROXIMATIONTESTS_SIMULATOR_H


class Simulator {
public:
    double absolute_error(double precise, double approximate);
    double relative_error(double precise, double approximate);
};


#endif //APPROXIMATIONTESTS_SIMULATOR_H
