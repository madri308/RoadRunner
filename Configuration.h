//
// Created by emema on 7/27/2020.
//

#ifndef ROADRUNNER_CONFIGURATION_H
#define ROADRUNNER_CONFIGURATION_H


#include <vector>
#include "Configuration.h"

class Configuration {
public:
    std::vector<int> populationLength;
    std::vector<int> sensorsQuantity;
    std::vector<int> generationQuantity;
    std::vector<float> killPercentage;
};


#endif //ROADRUNNER_CONFIGURATION_H
