//
// Created by emema on 7/26/2020.
//

#include <algorithm>
#include "GeneticAlgorithm.h"
//Genera la poblacion inicial con sus respectivos
//sensores aleatorios y posicion inicial.
void GeneticAlgorithm::generateInitialPopulation() {
    //Itera por la cantidad de poblacion.
    for(int individualID = 0 ; individualID < configuration->populationLength; individualID++){
        //Crea un individuo.
        Individual *initialIndividual = new Individual();
        initialIndividual->addPosition(START_POINT);//Le pone su posicion(inicio)
        initialIndividual->setStepsQueue(new std::vector<std::vector<float>>);//Le inicializa una cola
        //Le establece los senores
        float lastSensor = 0;
        for(int sensor = 0 ; sensor < configuration->sensorsQuantity ; sensor++){
            float newSensor = (rand() % 180) + lastSensor;
            initialIndividual->addSensor(newSensor);
            lastSensor = newSensor;
        }
        population.push_back(initialIndividual);
    }
}
//Evalua cada individuo dependiendo de que tanto se pueden movilizar
//en base a sus sensores. Falta corregir que no solo se trata de movilizacion sino de cercania al final
void GeneticAlgorithm::fitness() {
    //Itera por la poblacion
    for(int individualID = 0 ; individualID < configuration->populationLength ; individualID++){
        Individual *individual = population.at(individualID);//Consigue un individuo
        //Itera por sus cromosomas
        for(int sensorID = 0 ; sensorID < individual->sensors.size() ; sensorID++){
            std::vector<float> sensor = individual->sensors.at(sensorID);//Guarda su cromosoma(sensor)
            //Saca la distancia que mide ese sensor que puede moverse sin chocar
            float distance = calculator.calculateDistanceToLimit(sensor.at(0),individual->position);//FALTA LO DE EVALUAR CON EL FINAL
            //Le establece calificacion a ese cromosoma
            sensor.at(1) = distance;
            //La calificacion del individuo es la sumatoria de distancias de los sensores.
            individual->fitness += distance;
        }
    }
    //Llama a matar individuos.
    individualsKilled = killIndividuals();
}
//Cruza dos individuos aleatorios, genera un random entre los senores
//para obtener el nuevo senor del hijo, despues evalua con sensor me
//mide mas distancia para mover el hijo hacia esa direccion.
void GeneticAlgorithm::crossover() {
    //For por la cantidad de individuos necesarios.
    //Por cada iteracion genera un hijo.
    for(int newIndividualID = 0 ; newIndividualID < individualsKilled ; newIndividualID++){
        //Selecciono dos individuos randoms.
        Individual *parentA = population.at((rand() % population.size()) + 0);
        Individual *parentB = population.at((rand() % population.size()) + 0);
        //Saco al mejor padre.
        std::vector<Individual*> parents{parentA,parentB};
        std::sort(parents.begin(),parents.end(),[](Individual *p1,Individual *p2){
            return p1->fitness > p2->fitness;
        });
        Individual *bestParent = parents.at(0);
        //Saco los sensores de los individuos y los ordeno de mayor a menor dependiendo de su calificacion.
        std::vector<std::vector<float>> sensorsA = parentA->sensors;
        std::sort(sensorsA.begin(),sensorsA.end(),[](std::vector<float> sensorA,std::vector<float> sensorB){
            return sensorA[1] > sensorB[1];
        });

        std::vector<std::vector<float>> sensorsB = parentB->sensors;
        std::sort(sensorsB.begin(),sensorsB.end(),[](std::vector<float> sensorA,std::vector<float> sensorB){
            return sensorA[1] > sensorB[1];
        });
        //Guardo mi paso que insertare en la cola de pasos del mejor papa.
        //                  {x,y,angulo,distania}
        std::vector<float> forQueue{0,0,0,0};
        //Creo al nuevo individuo
        Individual *newIndividual = new Individual();
        //Itero por la cantidad de cromosomas(sensores)
        for(int sensorID = 0 ; sensorID < configuration->sensorsQuantity ; sensorID++){
            //Creo un nuevo sensor en base a los sensores de los padres
            float minSensor = std::min(sensorsA.at(sensorID).at(0),sensorsB.at(sensorID).at(0));
            float maxSensor = std::max(sensorsA.at(sensorID).at(0),sensorsB.at(sensorID).at(0));
            float newSensor = rand() % int(maxSensor) + minSensor;
            //Se insertio a mi nuevo individuo ese senor.
            newIndividual->addSensor(newSensor);
            //Calculo la distancia que se puede mover ese sensor.
            float distance = calculator.calculateDistanceToLimit(newSensor,bestParent->position);
            //Evaluo si el sensor es mejor a el que tengo guardado para cambiarlo.
            if(distance > forQueue.at(3)){
                //Si es mejor entonces guardo todas las cualidades de ese sensor
                forQueue.at(0) = bestParent->position.at(0);//x
                forQueue.at(1) = bestParent->position.at(1);//y
                forQueue.at(2) = newSensor;//angulo
                forQueue.at(3) = distance;//distancia
            }
        }
        //Establezco la nueva posicion del nuevo individuo con el mejor sensor y el mejor padre
        std::vector<float> newPosition = calculator.calculateNewPosition(bestParent->position,forQueue.at(2),forQueue.at(3));
        //Le digo al nuevo individuo su posicion
        newIndividual->addPosition(newPosition);
        //Guarda el paso en la cola
        bestParent->stepsQueue->push_back(forQueue);
        //Ahora la cola del nuevo individuo es la del mejor papa
        newIndividual->setStepsQueue(bestParent->stepsQueue);
        //Lo inserto en la poblacion
        population.push_back(newIndividual);
    }
}
//Elimina cierto porcentaje de individuos.
int GeneticAlgorithm::killIndividuals() {
    int killedAmount = configuration->populationLength*configuration->killPercentage/100;
    population.erase(population.end()-killedAmount,population.end());
    return killedAmount;
}
//Empieza el genetico.
void GeneticAlgorithm::start() {
    generateInitialPopulation();
    for(int generation = 0 ; generation < configuration->generationQuantity ; generation++){
        fitness();
        crossover();
    }
    //RETORNAR ALGO.
}
//Construye el objeto, recibe las configuraciones con las que trabajara.
GeneticAlgorithm::GeneticAlgorithm(Configuration *configuration) {
    this->configuration = configuration;
}
