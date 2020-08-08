//
// Created by emema on 7/28/2020.
//

#include <iterator>
#include "Instructions.h"

Instructions::Instructions(std::vector<std::vector<float>> *instructions) {
    this->instructions = instructions;
}

void Instructions::createTxt() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    std::string day = std::to_string(ltm->tm_mday);
    std::string month = std::to_string(1+ltm->tm_mon);
    std::string year = std::to_string(1900+ltm->tm_year);
    std::string name = "../run_"+day+"-"+month+"-"+year+"_EstebanMadrigal.txt";
    std::ofstream output_file(name);
    for(int instruction = 0 ; instruction < instructions.size() ; instruction++){
        output_file <<instructions.at(instruction).at(0)<<","<<instructions.at(instruction).at(1)<< std::endl;
    }
}
