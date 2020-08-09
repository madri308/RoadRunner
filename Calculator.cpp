//
// Created by emema on 7/26/2020.
//

#include "Calculator.h"

Calculator::Calculator() {
    getLimits();
}
//Calcula la distancia entre un punto y el limite, evaluando todos los puntos de la linea
//con los puntos del limite, hasta que lo ecnuentre entonces saca distancia entre puntos.
float Calculator::calculateDistanceToLimit(float angle, std::vector<float> point, float originalDirection) {
    float backUp = 0;
    float angleAdapted = angle+originalDirection-90; //Adapta el angulo dependiendo de la direccion de mi individuo.
    //GUARDA PUNTO INICIAL Y FINAL DE LA LINEA.
    //std::cout<<"AnguloOriginal:"<<angle<<" AnguloAdaptado:"<<angleAdapted<<std::endl;
    std::vector<float> startPoint = point;
    //std::cout<<"PuntoInicial: "<<startPoint.at(0)<<", "<<startPoint.at(1)<<std::endl;
    std::vector<float> endPoint = calculateNewPosition(startPoint,angleAdapted,MAX_SIZE_LINE);
    //std::cout<<"PuntoFinal: "<<endPoint.at(0)<<", "<<endPoint.at(1)<<std::endl;

    //SACA LOS COMPONENTES DE LA FUNCION DE LA LINEA.
    float slope = (startPoint.at(1)-endPoint.at(1))/(startPoint.at(0)-endPoint.at(0));
    float b = startPoint.at(1) - startPoint.at(0)*slope;

    int initialX = std::min(startPoint.at(0),endPoint.at(0));
    int endX = std::max(startPoint.at(0),endPoint.at(0));
    for(int x = initialX ; x<=endX ; x++){
        int y = slope*x + b;
        std::vector<std::vector<int>>corners{{x+individualSize,y+individualSize}
                                            ,{x-individualSize,y-individualSize}
                                            ,{x+individualSize,y-individualSize}
                                            ,{x-individualSize,y+individualSize}};
        for(std::vector<int>corner:corners){
            auto pairs = LIMIT_POINTS.equal_range(corner.at(0));
            for(auto pair = pairs.first ; pair != pairs.second ; pair++){
                if(pair->second == corner.at(1)){
                    //std::cout<<"PuntoLimite: "<<pair->first<<", "<<pair->second<<std::endl;
                    return sqrt(pow((x-startPoint.at(0)),2) + pow((y-startPoint.at(1)),2));
                }else if(pair->second+3 > y && pair->second-3 < y){
                    backUp = sqrt(pow((x-startPoint.at(0)),2) + pow((y-startPoint.at(1)),2));
                }
            }
        }
    }
    return backUp;
}
//Calcula un nuevo punto en base a un punto inicial, un angulo y una distancia con
//razones trigonometricas.
// https://stackoverflow.com/questions/50311279/how-can-i-find-end-point-using-start-point-angle-and-distance/50318756#50318756
std::vector<float> Calculator::calculateNewPosition(std::vector<float> point, float angle, float distance) {
    float normalizedAngle = angle-90; //Esto se hace porque el rango original es de -90 a 90, no de 0 a 180
    float angle_rad = normalizedAngle * 3.1415927f / 180.0f;
    float oppositeSide = sin(angle_rad)*distance;
    float adjacentSide = cos(angle_rad)*distance;
    std::vector<float> endPoint{point.at(0)+adjacentSide , point.at(1)+oppositeSide};
    return endPoint;
}
