//
// Created by emema on 7/26/2020.
//

#ifndef ROADRUNNER_ICONSTANTS_H
#define ROADRUNNER_ICONSTANTS_H

#include <iostream>
#include <vector>
#include <unordered_map>

class iConstants {
public:
    iConstants();
    void getLimits();                                   //Obtener los limites de un archivo.
    void printLimits();                                 //Funcion para mostrar los puntos de los limites.
    float getRandom(float a,float b);                   //Funcion para obtener un random.
    std::vector<float> START_POINT{0,130};              //Punto inicial.
    std::vector<float> END_POINT = {1800,145};          //Punto final.
    std::unordered_multimap<float,float> LIMIT_POINTS;  //Todos los puntos que forman los limites.
    float MAX_SIZE_LINE = 2000;                         //Hipotenusa entre altura: maximo(872) y base: maximo(1800)
    int CONFIGURATIONS_QUANTITY = 30;                   //Cantidad de configuraciones
    std::vector<int> POPULATION_LENGTH_RANGE{0,1000};   //Rango de poblacion.
    std::vector<int> SENSORS_QUANTITY_RANGE{1,10};      //Rango de sensores.
    std::vector<int> GENERATION_QUANTITY_RANGE{0,1000}; //Rango de generaciones.
    std::vector<int> KILL_PERCENTAGE_RANGE{10,100};     //Rango de porcentaje de muerte.
    std::vector<int> MAX_SENSORS_ANGLE_RANGE{0,180};    //Rango del maximo para rango de angulo de sensores.
    std::vector<int> MIN_SENSORS_ANGLE_RANGE{0,180};    //Rango del minimo para rango de angulo de sensores.
    std::vector<int> SECURITY_DISTANCE{2,100};           //Distancia antes del limite.
    int individualSize = 10;                            //mitad del individuo.
};


#endif //ROADRUNNER_ICONSTANTS_H
