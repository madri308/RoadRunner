//
// Created by emema on 7/27/2020.
//

#ifndef ROADRUNNER_MATROID_H
#define ROADRUNNER_MATROID_H


#include <vector>

class Matroid {
public:
    std::vector<std::vector<float>> configurationsList;
    std::vector<int> bestConfiguration;

    void insertConfiguration();
    void insertBestConfiguration();
};


#endif //ROADRUNNER_MATROID_H
