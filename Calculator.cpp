//
// Created by emema on 7/26/2020.
//

#include "Calculator.h"

Calculator::Calculator() {

}
//Calcula la distancia entre un punto y el limite, evaluando todos los puntos de la linea
//con los puntos del limite, hasta que lo ecnuentre entonces saca distancia entre puntos.
int Calculator::calculateDistanceToLimit(float angle, std::vector<float> point) {

    //GUARDA PUNTO INICIAL Y FINAL DE LA LINEA.
    std::vector<float> startPoint = point;
    std::vector<float> endPoint = calculateNewPosition(startPoint,angle,MAX_SIZE_LINE);

    //SACA LOS COMPONENTES DE LA FUNCION DE LA LINEA.
    float slope = (startPoint.at(1)-endPoint.at(1))/(startPoint.at(0)-endPoint.at(0));
    float b = startPoint.at(1) - startPoint.at(0)*slope;

    //ITERA POR LAS X ENTRE EL PUNTO INICIAL Y FINAL HASTA ENCONTRAR EL PAR QUE ESTA EN EL LIMITE Y EN LA LINEA
    bool found = false;
    float initialX = std::min(startPoint.at(0),endPoint.at(0));
    std::vector<float> limitPoint{initialX,0};
    while(true){
        limitPoint.at(1) = slope*limitPoint.at(0) + b;
        auto pairs = LIMIT_POINTS.equal_range(limitPoint.at(0));
        for(auto pair = pairs.first ; pair != pairs.second ; pair++){
            if(pair->second == limitPoint.at(1)){
                found = true;
            }
        }
        if(found){
            break;
        }else{
            limitPoint.at(0) += 1;
        }
    }
    return sqrt(pow((limitPoint.at(0)-startPoint.at(0)),2) + pow((limitPoint.at(1)-startPoint.at(1)),2));
}
//Calcula un nuevo punto en base a un punto inicial, un angulo y una distancia con
//razones trigonometricas.
// https://stackoverflow.com/questions/50311279/how-can-i-find-end-point-using-start-point-angle-and-distance/50318756#50318756
std::vector<float> Calculator::calculateNewPosition(std::vector<float> point, float angle, float distance) {
    float angle_rad = angle * 3.1415927f / 180.0f;
    float oppositeSide = sin(angle_rad)*distance;
    float adjacentSide = cos(angle_rad)*distance;
    std::vector<float> endPoint{point.at(0)+adjacentSide , point.at(1)+oppositeSide};
    return endPoint;
}
