//
// Created by emema on 7/26/2020.
//

#include <algorithm>
#include "GeneticAlgorithm.h"

void GeneticAlgorithm::generateInitialPopulation() {
    for(int individualID = 0 ; individualID < populationLength; individualID++){
        Individual *newIndividual = new Individual();
        newIndividual->addPosition(startPoint);
        float lastSensor = 0;
        for(int sensor = 0 ; sensor < sensorsQuantity ; sensor++){
            float newSensor = (rand() % 180) + lastSensor;
            newIndividual->addSensor(newSensor);
            population.push_back(newIndividual);
            lastSensor = newSensor;
        }
    }
}

void GeneticAlgorithm::fitness() {
    for(int individualID = 0 ; individualID < populationLength ; individualID++){
        Individual *individual = population.at(individualID);
        for(int sensorID = 0 ; sensorID < individual->sensors.size() ; sensorID++){
            std::vector<float> sensor = individual->sensors.at(sensorID);
            int distance = calculator.calculateDistanceToLimit(sensor.at(0),individual->position);//FALTA LO DE EVALUAR CON EL FINAL
            sensor.at(1) = distance;
            individual->fitness += distance;
        }
    }
    individualsKilled = killIndividuals();
}

void GeneticAlgorithm::crossover() {
    for(int newIndividualID = 0 ; newIndividualID < individualsKilled ; newIndividualID++){
        Individual *parentA = population.at((rand() % population.size()) + 0);
        Individual *parentB = population.at((rand() % population.size()) + 0);

        std::vector<float> parentsPositionAvrg = {(parentA->position.at(0)+parentB->position.at(0))/2 , (parentA->position.at(1)+parentB->position.at(1))/2};

        std::vector<std::vector<float>> sensorsA = parentA->sensors;
        std::sort(sensorsA.begin(),sensorsA.end(),[](std::vector<float> a,std::vector<float> b){
            return a[1] < b[1];
        });

        std::vector<std::vector<float>> sensorsB = parentB->sensors;
        std::sort(sensorsB.begin(),sensorsB.end(),[](std::vector<float> a,std::vector<float> b){
            return a[1] < b[1];
        });
        //                  punto(x,y),angulo,distania
        std::vector<float> forQueue{0,0,0,0};

        Individual *newIndividual = new Individual();

        for(int sensorID = 0 ; sensorID < sensorsQuantity ; sensorID++){
            float newSensor = (rand() % int(sensorsA.at(sensorID).at(0))) + sensorsB.at(sensorID).at(0);
            newIndividual->addSensor(newSensor);
            int distance = calculator.calculateDistanceToLimit(newSensor,parentsPositionAvrg);
            if(distance > forQueue.at(3)){
                forQueue.at(0) = parentsPositionAvrg.at(0);
                forQueue.at(1) = parentsPositionAvrg.at(1);
                forQueue.at(2) = newSensor;
                forQueue.at(3) = distance;
            }
        }
        std::vector<float> newPosition = calculator.calculateNewPosition(parentsPositionAvrg,forQueue.at(2),forQueue.at(3));
        newIndividual->addPosition(newPosition);
        population.push_back(newIndividual);
        //GUARDA EL FORQUEUE.
    }
}

int GeneticAlgorithm::killIndividuals() {
    int killedAmount = populationLength*killPercentage/100;
    population.erase(population.end()-killedAmount,population.end());
    return killedAmount;
}

void GeneticAlgorithm::start() {
    generateInitialPopulation();
    for(int generation = 0 ; generation < generationQuantity ; generation++){
        fitness();
        crossover();
    }
}
