//
// Created by emema on 7/27/2020.
//

#ifndef ROADRUNNER_CONFIGURATION_H
#define ROADRUNNER_CONFIGURATION_H

#include <vector>

class Configuration {
public:
    Configuration(int populationLength, int sensorsQuantity, int generationQuantity, float killPercentage, std::vector<float> sensorRange, int securityDistance);
    int populationLength;
    int sensorsQuantity;
    int generationQuantity;
    float killPercentage;
    std::vector<float> sensorRange;
    int securityDistance;
};


#endif //ROADRUNNER_CONFIGURATION_H
