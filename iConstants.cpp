//
// Created by emema on 7/26/2020.
//

#include <fstream>
#include <sstream>
#include <iterator>
#include <random>
#include "iConstants.h"

void iConstants::getLimits() {
    std::ifstream file(R"(C:\Users\emema\Documents\TEC\2020\SEM_I\Analisis\RoadRunner\documentation\limits.txt)");
    std::string str;
    std::vector<float> limits;
    while (std::getline(file, str))
    {
        std::vector<float> limit;
        std::istringstream iss(str);
        std::copy(std::istream_iterator<float>(iss),
                  std::istream_iterator<float>(),
                  std::back_inserter(limit));
        LIMIT_POINTS.insert(LIMIT_POINTS.begin(),std::pair<float,float>(limit.at(0),limit.at(1)));
    }
}

void iConstants::printLimits() {
    for(int x = 1 ; x<=1800 ; x++){
        auto pairs = LIMIT_POINTS.equal_range(x);
        for(auto pair = pairs.first ; pair != pairs.second ; pair++){
            std::cout << pair->first << '\t' << pair->second << std::endl;
        }
        std::cout<<std::endl;
    }
}

iConstants::iConstants() {
}

float iConstants::getRandom(float a , float b) {
    //std::random_device rd; // obtain a random number from hardware
    static std::mt19937 generator(std::random_device{}()); // seed the generator
    std::uniform_int_distribution<> distr(a, b); // define the range
    return distr(generator);
}
