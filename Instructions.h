//
// Created by emema on 7/28/2020.
//

#ifndef ROADRUNNER_INSTRUCTIONS_H
#define ROADRUNNER_INSTRUCTIONS_H

#include <fstream>
#include <vector>
#include <ctime>
#include <sstream>

class Instructions {
public:
    std::vector<std::vector<float>> *instructions;
    Instructions(std::vector<std::vector<float>> *instructions);
    void createTxt();
};


#endif //ROADRUNNER_INSTRUCTIONS_H
