//
//  Structure.hpp
//  CRO_Algorithm
//
//  Created by Domen Osojnik on 10/07/2021.
//

#ifndef Structure_h
#define Structure_h

#include <iostream>
#include <string>
#include <math.h>
#include <random>
#include <stdexcept>

class Structure {
private:
#pragma region Variables
    std::vector<std::string> u;
    std::vector<int> e;
    int energyValue = 0;
#pragma endregion Variables

public:
#pragma region Variables
    int value = 0, repairCount = 0;
    std::vector<std::string> d;
#pragma endregion Variables

#pragma region Functions
    // Increase in performance functions
    std::vector<std::string> increasePerformance1(std::string s, std::vector<std::string>& u);
    std::vector<std::string> increasePerformance2(std::string s, std::vector<std::string>  d, char monomer);
    std::vector<std::string> increasePerformance3(std::string s, std::vector<std::string>  d, std::vector<std::string>  target);

    // On wall innefective collision functions
    std::vector<std::string> onWallInnefectiveCollision(std::string s, std::vector<std::string>  popI);
    std::vector<std::string> onWallIneffectiveCollision1(std::string s, std::vector<std::string>  popI, std::vector<std::string>  u);
    std::vector<std::string> onWallIneffectiveCollision2(std::string s, std::vector<std::string>& popI);

    // Decomposition functions
    std::vector<std::vector<std::string> > decomposition(std::string s, std::vector<std::string>  u1);
    std::vector<std::vector<std::string> > decomposition1(std::string s, std::vector<std::string>  popI, std::vector<std::string>   su);
    std::vector<std::vector<std::string> > decomposition2(std::string s, std::vector<std::string>  u1);

    // Inter molecular ineffective collision
    std::vector<std::vector<std::string>> interMolecularIneffectiveCollision(std::string s, std::vector<std::string>& popI, std::vector<std::string>& popJ);
    std::vector<std::vector<std::string>> interMolecularIneffectiveCollision1(std::string s, std::vector<std::string> popI, std::vector<std::string>& popJ, std::vector<std::string>& u1);
    std::vector<std::vector<std::string>> interMolecularIneffectiveCollision2(std::string s, std::vector<std::string>& popI, std::vector<std::string>& popJ);

    // Synthesis functions
    std::vector<std::string> synthesis(std::string s, std::vector<std::string>  cki, std::vector<std::string>  ckj);
    std::vector<std::string> synthesis1(std::string s, std::vector<std::string>  cki, std::vector<std::string>  ckj, std::vector<std::string>  u1);
    std::vector<std::string> synthesis2(std::string s, std::vector<std::string>  cki, std::vector<std::string>  ckj);

    // Getters/setters
    void setE(std::vector<int>  e);
    std::vector<int> getE();
    void setU(std::vector<std::string>   u);
    std::vector<std::string> getU();
    void setEnergyValue(int energyValue);
    int getEnergyValue();

    // Extra functions
    static double uniform();
    static int poisson(int lambda);
    bool overlap(std::string s, std::vector<std::string>  d);
    bool hasDistance(std::string s, int i);
    int hammingDistance(std::string s, std::vector<std::string>  presentDir, std::vector<std::string>  targetDir);
    std::vector<int> getEnergy(std::string s, std::vector<std::string>  u);
    int getEnergyByPos(std::string s, std::vector<std::string>  u, int pos);
    int numOfH(std::string sequence, int start, int end);
    std::vector<std::string> Hcomplience(std::string s, std::vector<std::string>  u);
    std::vector<std::string> Pcomplience(std::string s, std::vector<std::string>  u, std::vector<std::string>  target);
    std::vector<std::string> evaluate(std::string s, std::vector<std::string>  d);
    std::vector<std::string> repairAndEvaluate(std::string s, std::vector<std::string>  u);
    std::string opp(std::string d);
#pragma endregion Functions
};

#endif /* Structure_hpp */
