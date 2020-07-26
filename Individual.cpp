//
// Created by emema on 7/26/2020.
//

#include "Individual.h"

void Individual::addSensor(float sensor) {
    this->sensors.push_back({sensor,0.0});
}

void Individual::addPosition(std::vector<float> position) {
    this->position = position;
}

Individual::Individual() {

}
