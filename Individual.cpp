//
// Created by emema on 7/26/2020.
//

#include "Individual.h"
//Le agrega un sensor al indiviuo.
void Individual::addSensor(float sensor) {
    this->sensors.push_back({sensor,0.0});
}
//Le establece la pisicion al individuo
void Individual::addPosition(std::vector<float> position) {
    this->position = position;
}

Individual::Individual() {
}

void Individual::setStepsQueue(std::vector<std::vector<float>> *queue) {
    this->stepsQueue = queue;
}
