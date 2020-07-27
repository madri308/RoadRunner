//
// Created by emema on 7/27/2020.
//

#ifndef ROADRUNNER_CONFIGURATIONTESTER_H
#define ROADRUNNER_CONFIGURATIONTESTER_H
#include <vector>
#include ""

class ConfigurationTester {
public:
    ConfigurationTester();
    std::vector<int> populationLengthRange{0,1000};
    std::vector<int> sensorsQuantityRange{1,10};
    std::vector<int> generationQuantityRange{0,1000};
    std::vector<float> killPercentageRange{10.0,20.0};
    void test();
    void generateConfiguration();
};


#endif //ROADRUNNER_CONFIGURATIONTESTER_H
