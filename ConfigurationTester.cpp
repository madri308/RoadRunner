#pragma clang diagnostic push
#pragma ide diagnostic ignored "openmp-use-default-none"
//
// Created by emema on 7/27/2020.
//

#include "ConfigurationTester.h"

ConfigurationTester::ConfigurationTester() {

}
//Crea matroids de manera iterativa con el while.
//Cada matroid contiene configuraciones los cuales
//prueba con GAs de manera paralela cada uno
//https://bisqwit.iki.fi/story/howto/openmp/
void ConfigurationTester::test() {
    int testQuantity = 0;
    while(testQuantity < MAX_TEST_QUANTITY){
        Matroid *matroid = new Matroid();
        matroid->configurationsList = generateConfigurations();
        #pragma omp parallel//CREA UN TEAM
        {
            #pragma omp for ordered schedule(dynamic)//DIVIDE EL TEAM EN PORCIONES DEL LOOP
            for(int configurationID = 0 ; configurationID < CONFIGURATIONS_QUANTITY ; configurationID++){
                Configuration *configuration = matroid->configurationsList.at(configurationID);
                GeneticAlgorithm *geneticAlgorithm = new GeneticAlgorithm(configuration);
                geneticAlgorithm->start();
                #pragma omp ordered
                matroid->compareWithBestGA(geneticAlgorithm);
            }
        }
        compareWithBestMatroid(matroid);
        //CREAR NUEVOS RANGOS EN BASE AL MATROID ANTERIOR
        testQuantity += 1;
    }
}
//Crea CONFIGURATIONS_QUANTITY configuraciones para un matroid.
std::vector<Configuration*> ConfigurationTester::generateConfigurations() {
    std::vector<Configuration*> configurationsList;
    for(int configurationID = 0 ; configurationID < CONFIGURATIONS_QUANTITY ; configurationID++){
        int populationLength = (rand() % populationLengthRange.at(1)) + populationLengthRange.at(0);
        int sensorsQuantity = (rand() % sensorsQuantityRange.at(1)) + sensorsQuantityRange.at(0);
        int generationQuantity = (rand() % generationQuantityRange.at(1)) + generationQuantityRange.at(0);
        int killPercentage = (rand() % killPercentageRange.at(1)) + killPercentageRange.at(0);
        Configuration *configuration = new Configuration(populationLength,sensorsQuantity,generationQuantity,killPercentage);
        configurationsList.push_back(configuration);
    }
    return configurationsList;
}
//Evalua cual matroid es mejor y lo guarda.
void ConfigurationTester::compareWithBestMatroid(Matroid *matroid) {
    if(this->bestMatroid->bestGeneticAlgorithm->score < matroid->bestGeneticAlgorithm->score){
        this->bestMatroid = matroid;
    }
}


