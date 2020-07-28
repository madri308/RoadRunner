#pragma clang diagnostic push
#pragma ide diagnostic ignored "openmp-use-default-none"
#include <iostream>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <omp.h>
#include "Instructions.h"
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
}

#pragma clang diagnostic pop