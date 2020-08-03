//
// Created by emema on 7/26/2020.
//

#include <algorithm>
#include <cstdlib>
#include "GeneticAlgorithm.h"
//Genera la poblacion inicial con sus respectivos
//sensores aleatorios y posicion inicial.
void GeneticAlgorithm::generateInitialPopulation() {
    //Itera por la cantidad de poblacion.
    for(int individualID = 0 ; individualID < configuration->populationLength; individualID++){
        //Crea un individuo.
        Individual *initialIndividual = new Individual();
        initialIndividual->frontDirection = 90;
        initialIndividual->addPosition(START_POINT);//Le pone su posicion(inicio)
        initialIndividual->setStepsQueue(new std::vector<std::vector<float>>);//Le inicializa una cola
        //std::cout<<"Individuo#"<<individualID<<" posicion: "<<initialIndividual->position.at(0)<<","<<initialIndividual->position.at(1)<<" "<<std::endl;
        //Le establece los senores
        for(int sensor = 0 ; sensor < configuration->sensorsQuantity ; sensor++){
            float newSensor = getRandom(configuration->sensorRange.at(0),configuration->sensorRange.at(1));
            //float newSensor = (rand() % (int)configuration->sensorRange.at(1))+configuration->sensorRange.at(0) ;
            initialIndividual->addSensor(newSensor);
            //std::cout<<"s"<<sensor<<": "<<initialIndividual->sensors.at(sensor).at(0)<<std::endl;
        }
        population.push_back(initialIndividual);
    }
}
//Evalua cada individuo dependiendo de que tanto se pueden movilizar
//en base a sus sensores. Falta corregir que no solo se trata de movilizacion sino de cercania al final
void GeneticAlgorithm::fitness() {
    //Itera por la poblacion
    for(int individualID = 0 ; individualID < configuration->populationLength ; individualID++){
        std::cout<<"==FITNESS:"<<std::endl;
        Individual *individual = population.at(individualID);//Consigue un individuo
        std::cout<<"Individuo#"<<individualID<<
                    "\nPosicion: "<<individual->position.at(0)<<", "<<individual->position.at(1)<<
                    "\nDireccion: "<<individual->frontDirection<<std::endl;
        for(int sensorID = 0 ; sensorID < individual->sensors.size() ; sensorID++){ //Itera por sus cromosomas
            std::vector<float> sensor = individual->sensors.at(sensorID);//Guarda su cromosoma(sensor)
            //Saca la distancia que mide ese sensor que puede moverse sin chocar
            float distance = calculator.calculateDistanceToLimit(sensor.at(0),individual->position,individual->frontDirection);//FALTA LO DE EVALUAR CON EL FINAL
            sensor.at(1) = distance;  //Le establece calificacion a ese cromosoma
            std::cout<<"s"<<sensorID<<": "<<sensor.at(0)<<" calificacion: "<<sensor.at(1)<<std::endl;
            //La calificacion del individuo es la sumatoria de distancias de los sensores.
            individual->fitness += distance;
        }
        std::cout<<"Calificacion individuo#"<<individualID<<": "<<individual->fitness<<"\n"<<std::endl;
    }
}
//Cruza dos individuos aleatorios, genera un random entre los senores
//para obtener el nuevo senor del hijo, despues evalua con sensor me
//mide mas distancia para mover el hijo hacia esa direccion.
Individual * GeneticAlgorithm::crossover() {
    //For por la cantidad de individuos necesarios.
    //Por cada iteracion genera un hijo.
    std::cout<<"==CROSSOVER:"<<std::endl;
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
            //float newSensor = (rand() % int(maxSensor)) + minSensor;
            std::cout<<"\nsPadre1: "<< minSensor<<", sPadre2: "<<maxSensor<<", sHijo:"<<newSensor<<std::endl;

            newIndividual->addSensor(newSensor); //Se inserta a mi nuevo individuo ese sensor.

            //Calculo la distancia que se puede mover ese sensor.
            float distance = calculator.calculateDistanceToLimit(newSensor,bestParent->position,bestParent->frontDirection);
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
        std::cout<<"posicionHijo: "<<newPosition.at(0)<<", "<<newPosition.at(1)<<"\ndireccionHijo: "<<forQueue.at(2)<<std::endl;
        bestParent->stepsQueue->push_back(forQueue);    //Guarda el paso en la cola.
        newIndividual->setStepsQueue(bestParent->stepsQueue);   //Cola del nuevo individuo es la del mejor papa
        population.push_back(newIndividual);    //Lo inserto en la poblacion
        //Si un individuo llego a la meta
        if(newIndividual->position.at(0) > END_POINT){
            return newIndividual;   //Lo retorna
        }
    }
    return nullptr;
}
//Elimina cierto porcentaje de individuos.
int GeneticAlgorithm::killIndividuals() {
    int killedAmount = configuration->populationLength*configuration->killPercentage/100;
    std::cout<<"-> poblacion:"<<population.size()<<" asesinados:"<<killedAmount<<"\n"<<std::endl;
    population.erase(population.end()-killedAmount,population.end());
    return killedAmount;
}
//Empieza el genetico.
Individual* GeneticAlgorithm::start() {
    generateInitialPopulation();
    Individual *best = nullptr;
    for(int generation = 0 ; generation < configuration->generationQuantity /*&& best == nullptr*/; generation++){
        std::cout<<"\n=======GENERACION#"<<generation<<"======"<<std::endl;
        fitness();
        individualsKilled = killIndividuals();
        best = crossover();
    }
    return best;
}
//Construye el objeto, recibe las configuraciones con las que trabajara.
GeneticAlgorithm::GeneticAlgorithm(Configuration *configuration) {
    this->configuration = configuration;
}
