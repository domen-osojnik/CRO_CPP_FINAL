//
//  Operators.hpp
//  CRO_Algorithm
//
//  Created by Domen Osojnik on 10/07/2021.
//

#ifndef Operators_h
#define Operators_h

#include <iostream>
#include <string>
#include <math.h>
#include <random>
#include <stdexcept>
#include "Structure.h"
#include <algorithm>
#include <iterator>
#include <vector>
#include <chrono> 

class Operators {
public:
#pragma region Variables
    int energyValue = 0, div = 0, speed = 0, length = 0, repairCount = 0;
    std::string sequence;
    Structure struc;
    std::vector<std::string> target;
#pragma endregion Variables

#pragma region Functions
    double CRO_PSP(int pop_size, std::string s, double moleCol, double initialKE, double KELossRate);
    std::vector<std::vector<std::string> > search_space_creation(std::string s, int pop_size, std::vector<std::string> target);
    void print(std::vector<std::string> direc);
    bool stoppingConditionMet(int max);
    std::vector<std::vector<int> > getCoordinates(std::string s, std::vector<std::string> u);
    std::vector<std::vector<int> > getCoordinates(std::string s, std::vector<std::string> u, int len);
#pragma endregion Functions
};

#endif /* Operators_hpp */
