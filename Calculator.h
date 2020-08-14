#ifndef ROADRUNNER_CALCULATOR_H
#define ROADRUNNER_CALCULATOR_H

#include <iostream>
#include <vector>
#include <cmath>
#include "iConstants.h"

class Calculator:public iConstants {
public:
    Calculator();
    float calculateDistanceToLimit(float angle,std::vector<float> point,float originalDirection,int securityDistance);
    std::vector<float> calculateNewPosition(std::vector<float> point , float angle , float distance, float originalDirection);
};


#endif //ROADRUNNER_CALCULATOR_H
