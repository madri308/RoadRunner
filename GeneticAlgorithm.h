#ifndef ROADRUNNER_GENETICALGORITHM_H
#define ROADRUNNER_GENETICALGORITHM_H

#include "Calculator.h"
#include "Individual.h"
#include "iConstants.h"
#include "Configuration.h"

class GeneticAlgorithm: public iConstants {

public:
    GeneticAlgorithm(Configuration *configuration);

    float score;
    int individualsKilled;
    Configuration *configuration;
    Calculator calculator;
    std::vector<Individual*> population;
    Individual *winner;

    Individual* crossover();
    void start();
    void generateInitialPopulation();
    void fitness();
    void mutate();
    int killIndividuals();
    void showPopulation(int generation);
};


#endif //ROADRUNNER_GENETICALGORITHM_H
