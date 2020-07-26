#ifndef ROADRUNNER_GENETICALGORITHM_H
#define ROADRUNNER_GENETICALGORITHM_H

#include "Calculator.h"
class GeneticAlgorithm {

public:
    int populationLength;
    int sensorsQuantity;
    int generationQuantity;
    float killPercentage;
    int individualsKilled;
    Calculator calculator;

    void generateInitialPopulation();
    void fitness();
    void cross();
    int killIndividuals();
    void start();
};


#endif //ROADRUNNER_GENETICALGORITHM_H
