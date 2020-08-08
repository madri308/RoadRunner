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
    iConstants();
    void getLimits();
    void printLimits();
    float getRandom(float a,float b);
    std::vector<float> START_POINT{1,130};
    std::unordered_multimap<float,float> LIMIT_POINTS;
    float MAX_SIZE_LINE = 2000;//medida de la diagonal que se forma en el rectangulo de ancho maximo(872) y largo maximo(1800)
    int CONFIGURATIONS_QUANTITY = 30;
    int END_POINT = 1800;
    std::vector<int> POPULATION_LENGTH_RANGE{0,1000};
    std::vector<int> SENSORS_QUANTITY_RANGE{1,10};
    std::vector<int> GENERATION_QUANTITY_RANGE{0,1000};
    std::vector<int> KILL_PERCENTAGE_RANGE{10,100};
    std::vector<int> MAX_SENSORS_ANGLE_RANGE{0,180};
    std::vector<int> MIN_SENSORS_ANGLE_RANGE{0,180};
};


#endif //ROADRUNNER_ICONSTANTS_H
