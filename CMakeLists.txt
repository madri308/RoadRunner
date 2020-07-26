cmake_minimum_required(VERSION 3.16)
project(RoadRunner)

set(CMAKE_CXX_STANDARD 14)

add_executable(RoadRunner main.cpp GeneticAlgorithm.cpp GeneticAlgorithm.h Calculator.cpp Calculator.h Individual.cpp Individual.h iConstants.cpp iConstants.h)