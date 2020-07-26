//
// Created by emema on 7/26/2020.
//

#ifndef ROADRUNNER_INDIVIDUAL_H
#define ROADRUNNER_INDIVIDUAL_H
#include <iostream>
#include <vector>

class Individual {
public:
    Individual();
    std::vector<float> position;
    std::vector<std::vector<float>> sensors;
    float fitness = 0;
    void addSensor(float sensor);
    void addPosition(std::vector<float> position);
};


#endif //ROADRUNNER_INDIVIDUAL_H
