//
// Created by emema on 7/27/2020.
//

#include "Configuration.h"
//Recibe los parametros que van a conformar esta configuracion.
Configuration::Configuration(int populationLength, int sensorsQuantity, int generationQuantity, float killPercentage){
    this->populationLength = populationLength;
    this->sensorsQuantity = sensorsQuantity;
    this->generationQuantity = generationQuantity;
    this->killPercentage = killPercentage;
}
