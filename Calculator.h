#ifndef ROADRUNNER_CALCULATOR_H
#define ROADRUNNER_CALCULATOR_H

#include <iostream>
#include <vector>

class Calculator {
public:
    Calculator();
    int calculateDistanceToLimit(float angle , std::vector<float> point);
    std::vector<float> calculateNewPosition(std::vector<float> point , float angle , float distance);
};


#endif //ROADRUNNER_CALCULATOR_H
