//
// Created by emema on 7/26/2020.
//

#ifndef ROADRUNNER_ICONSTANTS_H
#define ROADRUNNER_ICONSTANTS_H

#include <iostream>
#include <vector>
#include <unordered_map>

class iConstants {
public:
    std::vector<float> START_POINT{10,10};
    std::unordered_multimap<float,float> LIMIT_POINTS;
    float MAX_SIZE_LINE = 2000;//medida de la diagonal que se forma en el rectangulo de ancho maximo(872) y largo maximo(1800)
    int CONFIGURATIONS_QUANTITY = 10;
    int MAX_TEST_QUANTITY = 10;
};


#endif //ROADRUNNER_ICONSTANTS_H
