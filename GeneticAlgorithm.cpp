//
// Created by emema on 7/26/2020.
//

#include <algorithm>
#include <cstdlib>
#include "GeneticAlgorithm.h"

//Genera la poblacion inicial con sus respectivos sensores aleatorios y posicion inicial.
void GeneticAlgorithm::generateInitialPopulation() {
    //Itera por la cantidad de poblacion.
    for(int individualID = 0 ; individualID < configuration->populationLength; individualID++){
        //Crea un individuo.
        Individual *initialIndividual = new Individual();
        initialIndividual->frontDirection = 90;
        initialIndividual->addPosition(START_POINT);//Le pone su posicion(inicio)
        initialIndividual->setStepsQueue(new std::vector<std::vector<float>>);//Le inicializa una cola
        //Le establece los senores
        float distribution = (configuration->sensorRange.at(1)-configuration->sensorRange.at(0))/configuration->sensorsQuantity;
        for(int sensor = 0 ; sensor < configuration->sensorsQuantity ; sensor++){
            float newSensor = getRandom(configuration->sensorRange.at(0)+(distribution*sensor),configuration->sensorRange.at(0)+(distribution*(sensor+1)));
            //float newSensor = getRandom(configuration->sensorRange.at(0),configuration->sensorRange.at(1));
            initialIndividual->addSensor(newSensor);
        }
        population.push_back(initialIndividual);
    }
}
//Evalua cada individuo dependiendo de que tanto se pueden movilizar en base a sus sensores.
void GeneticAlgorithm::fitness() {
    for(Individual *individual:population){
        float fitness = 0;
        for(std::vector<float> &sensor:individual->sensors){
            //Saca la distancia que mide ese sensor que puede moverse sin chocar
            float distance = calculator.calculateDistanceToLimit(sensor.at(0),individual->position,individual->frontDirection,configuration->securityDistance);
            sensor.at(1) = distance; //Le establece calificacion a ese cromosoma
            fitness += distance; //La calificacion del individuo es la sumatoria de distancias de los sensores.
        }
        float distanceToEnd = sqrt(pow((individual->position.at(0)-END_POINT.at(0)),2) + pow((individual->position.at(1)-END_POINT.at(1)),2));
        individual->fitness = fitness/distanceToEnd;
    }
}
//Cruza dos individuos aleatorios, genera un random entre los senores
//para obtener el nuevo senor del hijo, despues evalua con sensor me
//mide mas distancia para mover el hijo hacia esa direccion.
Individual * GeneticAlgorithm::crossover() {
    //For por la cantidad de individuos necesarios.
    //Por cada iteracion genera un hijo.
    //std::cout<<"==CROSSOVER:"<<std::endl;
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
        //                  {x,y,angulo,distancia}
        std::vector<float> forQueue{0,0,0,0};
        //Creo al nuevo individuo
        Individual *newIndividual = new Individual();
        //Itero por la cantidad de cromosomas(sensores)
        for(int sensorID = 0 ; sensorID < configuration->sensorsQuantity ; sensorID++){
            //Creo un nuevo sensor en base a los sensores de los padres
            float minSensor = std::min(sensorsA.at(sensorID).at(0),sensorsB.at(sensorID).at(0));
            float maxSensor = std::max(sensorsA.at(sensorID).at(0),sensorsB.at(sensorID).at(0));
            float newSensor = getRandom(minSensor,maxSensor);

            newIndividual->addSensor(newSensor); //Se inserta a mi nuevo individuo ese sensor.

            //Calculo la distancia que se puede mover ese sensor.
            float distance = calculator.calculateDistanceToLimit(newSensor,bestParent->position,bestParent->frontDirection,configuration->securityDistance);
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
        std::vector<float> newPosition = calculator.calculateNewPosition(bestParent->position,forQueue.at(2)+bestParent->frontDirection-90,forQueue.at(3));
        newIndividual->addPosition(newPosition);    //Le digo al nuevo individuo su posicion.
        newIndividual->frontDirection = forQueue.at(2);     //Le digo al nuevo individuo hacia donde apunta.
        bestParent->stepsQueue->push_back(forQueue);    //Guarda el paso en la cola.
        newIndividual->setStepsQueue(bestParent->stepsQueue);   //Cola del nuevo individuo es la del mejor papa
        population.push_back(newIndividual);    //Lo inserto en la poblacion
        //Si un individuo llego a la meta
        if(newIndividual->position.at(0) > END_POINT.at(0)){
            return newIndividual;   //Lo retorna
        }
    }
    return nullptr;
}
//Elimina cierto porcentaje de individuos.
int GeneticAlgorithm::killIndividuals() {
    int killedAmount = configuration->populationLength*configuration->killPercentage/100;
    std::cout<<"\n-> poblacion:"<<population.size()<<" asesinados:"<<killedAmount<<std::endl;
    std::sort(population.begin(),population.end(),[](Individual *A,Individual *B){
        return A->fitness > B->fitness;
    });
    population.erase(population.end()-killedAmount,population.end());
    return killedAmount;
}

//Empieza el genetico.
Individual* GeneticAlgorithm::start() {
    generateInitialPopulation();
    Individual *best = nullptr;
    for(int generation = 0 ; generation < 3/*configuration->generationQuantity && best == nullptr*/; generation++){
        std::cout<<"=======GENERACION#"<<generation<<"======"<<std::endl;
        fitness();
        showPopulation();
        individualsKilled = killIndividuals();
        best = crossover();
        //mutar.
    }
    return best;
}

//Construye el objeto, recibe las configuraciones con las que trabajara.
GeneticAlgorithm::GeneticAlgorithm(Configuration *configuration) {
    this->configuration = configuration;
}

void GeneticAlgorithm::showPopulation() {
    for(Individual *individual:this->population){
        std::cout<<"Individuo:\n"<<"  Pos: "<<individual->position.at(0)<<", "<<individual->position.at(1)<<"\n  Calif: "<<individual->fitness<<"\n  Dir: "<<individual->frontDirection<<std::endl;
        for(std::vector<float>sensor:individual->sensors){
            std::cout<<"  S -> ang: "<<sensor.at(0)<<" calif:"<<sensor.at(1)<<std::endl;
        }
    }
}
