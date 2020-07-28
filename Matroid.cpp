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


