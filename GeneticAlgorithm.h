#ifndef ROADRUNNER_GENETICALGORITHM_H
#define ROADRUNNER_GENETICALGORITHM_H

#include "Calculator.h"
#include "Individual.h"
#include "iConstants.h"
class GeneticAlgorithm: public iConstants {

public:
    int populationLength;
    int sensorsQuantity;
    int generationQuantity;
    float killPercentage;
    int individualsKilled;
    Calculator calculator;
    std::vector<Individual*> population;
    void generateInitialPopulation();
    void fitness();
    void crossover();
    int killIndividuals();
    void start();
};


#endif //ROADRUNNER_GENETICALGORITHM_H
