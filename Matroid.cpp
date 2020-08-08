#pragma clang diagnostic push
#pragma ide diagnostic ignored "openmp-use-default-none"
//
// Created by emema on 7/27/2020.
//

#include "Matroid.h"

Matroid::Matroid() {

}
//Compara cual genetico es mejor y lo guarda.
void Matroid::compareWithBestGA(GeneticAlgorithm *geneticAlgorithm) {
    if(this->bestGeneticAlgorithm->score < geneticAlgorithm->score){
        this->bestGeneticAlgorithm = geneticAlgorithm;
    }
}
//Algoritmo voraz.
//Subestructura: conjunto de rangos.
//Etapa: rango.
//Optimo local: datos de cada rango.
//Optimo globa: todos los datos para la cantidad de configuraciones que quiero.
void Matroid::fillConfigurationsList() {
    //Guarda los rangos con los que se van a hacer las configuraciones.
    std::vector<std::vector<int>>configsRange{POPULATION_LENGTH_RANGE
                                             ,SENSORS_QUANTITY_RANGE
                                             ,GENERATION_QUANTITY_RANGE
                                             ,KILL_PERCENTAGE_RANGE
                                             ,MAX_SENSORS_ANGLE_RANGE
                                             ,MIN_SENSORS_ANGLE_RANGE};
    std::vector<std::vector<int>>evaluationCriteria{{POPULATION_LENGTH_RANGE.at(1)-100,POPULATION_LENGTH_RANGE.at(1)}
                                                    ,{SENSORS_QUANTITY_RANGE.at(1)-5,SENSORS_QUANTITY_RANGE.at(1)}
                                                    ,{GENERATION_QUANTITY_RANGE.at(1)-100,GENERATION_QUANTITY_RANGE.at(1)}
                                                    ,{((KILL_PERCENTAGE_RANGE.at(1)-KILL_PERCENTAGE_RANGE.at(0))/2)-15,((KILL_PERCENTAGE_RANGE.at(1)-KILL_PERCENTAGE_RANGE.at(0))/2)+15}
                                                    ,{((MAX_SENSORS_ANGLE_RANGE.at(1)-MAX_SENSORS_ANGLE_RANGE.at(0))/2),((MAX_SENSORS_ANGLE_RANGE.at(1)-MAX_SENSORS_ANGLE_RANGE.at(0))/2)+50}
                                                    ,{((MIN_SENSORS_ANGLE_RANGE.at(1)-MIN_SENSORS_ANGLE_RANGE.at(0))/2)-50,((MIN_SENSORS_ANGLE_RANGE.at(1)-MIN_SENSORS_ANGLE_RANGE.at(0))/2)}};
    for(int i = 0 ; i <evaluationCriteria.size() ; i++){
        std::cout<<evaluationCriteria.at(i).at(0)<<" - "<<evaluationCriteria.at(i).at(1)<<std::endl;
    }

    //poblaciones,sensores,generaciones,porcentajeMuerte,maxRangoAnguloSensores,minRangoAnguloSensores
    std::vector<std::vector<int>> configsData{{},{},{},{},{},{}};
    for(int etapa = 0 ; etapa < configsRange.size() ; etapa++){
        while(configsData.at(etapa).size()<CONFIGURATIONS_QUANTITY){
            int value = getRandom(configsRange.at(etapa).at(0),configsRange.at(etapa).at(1));
            if(evaluationCriteria.at(etapa).at(0)<value && evaluationCriteria.at(etapa).at(1)>value){
                configsData.at(etapa).push_back(value);
            }
        }
    }
    for(int valuePosition = 0 ; valuePosition<configsData.at(0).size() ; valuePosition++){
        std::vector<int> data{};
        for(int configType = 0 ; configType < configsData.size() ; configType++){
            data.push_back(configsData.at(configType).at(valuePosition));
        }
        Configuration *newConfiguration = new Configuration(data.at(0),data.at(1),data.at(2),data.at(3),{(float)data.at(5),(float)data.at(4)});
        this->configurationsList.push_back(newConfiguration);
    }
    showConfigurationList();
}

void Matroid::showConfigurationList() {
    for(int config = 0 ; config<this->configurationsList.size() ; config++){
        std::cout<<"\n==CONFIGURACION #"<<config<<std::endl;
        std::cout<<"poblacion: "<<this->configurationsList.at(config)->populationLength<<std::endl;
        std::cout<<"sensores: "<<this->configurationsList.at(config)->sensorsQuantity<<std::endl;
        std::cout<<"generaciones: "<<this->configurationsList.at(config)->generationQuantity<<std::endl;
        std::cout<<"porcentaje de muerte: "<<this->configurationsList.at(config)->killPercentage<<std::endl;
        std::cout<<"rango sensores: "<<this->configurationsList.at(config)->sensorRange.at(0)<<"-"<<this->configurationsList.at(config)->sensorRange.at(1)<<std::endl;
    }
}

void Matroid::getBestConfiguration() {
    #pragma omp parallel//CREA UN TEAM
    {
        #pragma omp for ordered schedule(dynamic)//DIVIDE EL TEAM EN PORCIONES DEL LOOP
        for(int configurationID = 0 ; configurationID < CONFIGURATIONS_QUANTITY ; configurationID++){
            Configuration *configuration = this->configurationsList.at(configurationID);
            GeneticAlgorithm *geneticAlgorithm = new GeneticAlgorithm(configuration);
            geneticAlgorithm->start();
            #pragma omp ordered
            this->compareWithBestGA(geneticAlgorithm);
        }
    }
}



#pragma clang diagnostic pop