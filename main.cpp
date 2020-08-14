#include <iostream>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <omp.h>
#include "Instructions.h"
#include "Matroid.h"
int mayor = 0;
void Hello(int n){
    int my_rank = omp_get_thread_num();
    int thread_count = omp_get_num_threads();
    if(n> mayor){
        mayor = n;
    }
    printf("hello from thread %d of %d,bigger is %d\n",my_rank,thread_count,mayor);
}
int main(int argc,char* argv[]) {
    //TEST DE SORT DE VECTOR DE VECTORES
    /*
    std::vector<std::vector<float>> sensorsA = {{1,2},{2,8},{1,1}};
    std::sort(sensorsA.begin(),sensorsA.end(),[](std::vector<float> a,std::vector<float> b){
        return a[1] < b[1];
    });

    for(int i = 0 ; i < sensorsA.size() ; i++){
        std::cout << sensorsA.at(i).at(0)<<" , "<< sensorsA.at(i).at(1)<< std::endl;
    }*/
    //TEST DE HILOS
    /*
    std::vector<int> m{4,2,7,9,3,5,6,1,8};
    #pragma omp parallel
    {
        #pragma omp for ordered schedule(dynamic)
        for(int n = 0 ; n< m.size() ; n++){
            #pragma omp ordered
            Hello(m.at(n));
        }
    }
    printf("mayor: %d\n",mayor);
    */
    //TEST DEL TXT
    /*
    std::vector<std::vector<float>>total{};
    for(int i = 0 ; i < 1000 ; i++){
        std::vector<float>ins{static_cast<float>(rand() % 1000),static_cast<float>(rand() % 1000)};
        total.push_back(ins);
    }
    Instructions *instructions = new Instructions(total);
    instructions->createTxt();
    return 0;
     */
    //TEST DE ORDENAR Y SACAR MAYOR
    /*
    auto *parentA = new Individual();
    parentA->fitness = 40;
    Individual *parentB = new Individual();
    parentB->fitness = 1000;
    auto *parentC = new Individual();
    parentC->fitness = 5;
    Individual *parentD = new Individual();
    parentD->fitness = 200;
    std::vector<Individual*> parents{parentA,parentB,parentC,parentD};
    std::cout <<parents.at(3)->fitness<< std::endl;
    std::sort(parents.begin(),parents.end(),[](Individual *a,Individual *b){
        return a->fitness > b->fitness;
    });
    std::cout <<parents.at(0)->fitness<< std::endl;
    */
    //TEST LIMITES

    /*iConstants *iconstants = new iConstants();
    iconstants->getLimits();
    iconstants->printLimits();*/


    /*Configuration *configuration = new Configuration(20,7,50,50,{0,175},20);
    GeneticAlgorithm *ga = new GeneticAlgorithm(configuration);
    //printf("poblacion: %d sensores: %d generaciones: %d muerte: %f\n",ga->configuration->populationLength,ga->configuration->sensorsQuantity,ga->configuration->generationQuantity,ga->configuration->killPercentage);
    Individual *best = ga->start();*/


    //DRIVER CODE
    Matroid *m = new Matroid();
    m->fillConfigurationsList();//Lleno S: Voraz
    m->getBestConfiguration();//Consigo I: Paralelismo
    Instructions *instructions = new Instructions(m->bestGeneticAlgorithm->winner->stepsQueue);
    instructions->createTxt();
}

