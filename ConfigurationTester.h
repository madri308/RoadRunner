//
// Created by emema on 7/27/2020.
//

#ifndef ROADRUNNER_CONFIGURATIONTESTER_H
#define ROADRUNNER_CONFIGURATIONTESTER_H
#include <vector>
#include "Configuration.h"
#include "iConstants.h"
#include "Matroid.h"
#include "GeneticAlgorithm.h"

class ConfigurationTester:public iConstants {
public:
    ConfigurationTester();
    std::vector<int> populationLengthRange{0,1000};
    std::vector<int> sensorsQuantityRange{1,10};
    std::vector<int> generationQuantityRange{0,1000};
    std::vector<int> killPercentageRange{10,20};
    Matroid *bestMatroid;
    void compareWithBestMatroid(Matroid *matroid);
    void test();
    std::vector<Configuration*> generateConfigurations();

};


#endif //ROADRUNNER_CONFIGURATIONTESTER_H
