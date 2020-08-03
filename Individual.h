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
    void setStepsQueue(std::vector<std::vector<float>> *queue);
    void addSensor(float sensor);
    void addPosition(std::vector<float> position);
    std::vector<std::vector<float>> *stepsQueue;
    std::vector<float> position;
    std::vector<std::vector<float>> sensors;
    float fitness = 0;
    float frontDirection;
};


#endif //ROADRUNNER_INDIVIDUAL_H
