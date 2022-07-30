//
//  Structure.cpp
//  CRO_Algorithm
//
//  Created by Domen Osojnik on 10/07/2021.
//

#include "Structure.h"
#include "Operators.h"
#include <fstream>

#pragma region Performance increase functions
std::vector<std::string> Structure::increasePerformance1(std::string s, std::vector<std::string> & u)
{

    int len = s.length();
    Operators op;

    std::vector<std::vector<int> > direc_coordinate = op.getCoordinates(s, u);

    int x, y, z, count;

    getEnergy(s, u);

    std::string direc = u[0];
    char monomer = s[0];
    int start = 1, end;

    count = 0;

    getEnergy(s, u);
    int mainE = getEnergyValue();

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, (len / 5) - 1); // -1, last number is inclusive in int distribution

    int arrSize = 1 + dist(mt);

    std::vector<int> partArr(arrSize);
    int partLen = len / arrSize;

    for (int i = 0; i < arrSize; i++)
    {
        for (int j = i * partLen; j < (i * partLen + partLen); j++)
        {
            if (!hasDistance(u[j], j))
            {
                partArr[i]++;
            }
        }
    }

    int min = partArr[0];
    int p = 0;

    for (int i = 1; i < arrSize; i++)
    {
        if (min >= partArr[i])
        {
            min = partArr[i];
            p = i;
        }
    }

    count = 0;
    // TODO:
    for (int k = partLen * p + 1; k < (partLen * p + partLen); k++)
    {
        if (hasDistance(u[k], k))
        {
            std::vector<std::string> tempDirec = u;
            bool check;

            x = direc_coordinate[k - 1][0];
            y = direc_coordinate[k - 1][1];
            z = direc_coordinate[k - 1][2];

            int has = 0;
            for (int j = 0; j < len; j++)
            {
                if (direc_coordinate[j][0] == x + 1 && direc_coordinate[j][1] == y && direc_coordinate[j][2] == z)
                {
                    has = 1;
                    break;
                }
            }
            if (has == 0)
            {
                tempDirec[k] = 'R';
                tempDirec = repairAndEvaluate(s, tempDirec);

                getEnergy(s, tempDirec);
                int e = getEnergyValue();

                if (e > mainE)
                {
                    u = tempDirec;
                    mainE = e;
                }
            }

            has = 0;
            for (int j = 0; j < len; j++)
            {
                if (direc_coordinate[j][0] == x - 1 && direc_coordinate[j][1] == y && direc_coordinate[j][2] == z)
                {
                    has = 1;
                    break;
                }
            }
            if (has == 0)
            {
                tempDirec[k] = 'L';

                tempDirec = repairAndEvaluate(s, tempDirec);
                getEnergy(s, tempDirec);
                int e = getEnergyValue();

                if (e > mainE)
                {
                    u = tempDirec;
                    mainE = e;
                }
            }

            has = 0;
            for (int j = 0; j < len; j++)
            {
                if (direc_coordinate[j][0] == x && direc_coordinate[j][1] == y + 1 && direc_coordinate[j][2] == z)
                {
                    has = 1;
                    break;
                }
            }
            if (has == 0)
            {
                tempDirec[k] = 'U';
                tempDirec = repairAndEvaluate(s, tempDirec);
                getEnergy(s, tempDirec);
                int e = getEnergyValue();

                if (e > mainE)
                {
                    u = tempDirec;
                    mainE = e;
                }
            }

            has = 0;
            for (int j = 0; j < len; j++)
            {
                if (direc_coordinate[j][0] == x && direc_coordinate[j][1] == y - 1 && direc_coordinate[j][2] == z)
                {
                    has = 1;
                    break;
                }
            }
            if (has == 0)
            {
                tempDirec[k] = 'D';
                tempDirec = repairAndEvaluate(s, tempDirec);
                getEnergy(s, tempDirec);
                int e = getEnergyValue();

                if (e > mainE)
                {
                    u = tempDirec;
                    mainE = e;
                }
            }

            has = 0;
            for (int j = 0; j < len; j++)
            {
                if (direc_coordinate[j][0] == x && direc_coordinate[j][1] == y && direc_coordinate[j][2] == z + 1)
                {
                    has = 1;
                    break;
                }
            }
            if (has == 0)
            {
                tempDirec[k] = 'F';
                tempDirec = repairAndEvaluate(s, tempDirec);
                getEnergy(s, tempDirec);
                int e = getEnergyValue();

                if (e > mainE)
                {
                    u = tempDirec;
                    mainE = e;
                }
            }

            has = 0;
            for (int j = 0; j < len; j++)
            {
                if (direc_coordinate[j][0] == x && direc_coordinate[j][1] == y && direc_coordinate[j][2] == z - 1)
                {
                    has = 1;
                    break;
                }
            }
            if (has == 0)
            {
                tempDirec[k] = 'B';
                tempDirec = repairAndEvaluate(s, tempDirec);
                getEnergy(s, tempDirec);
                int e = getEnergyValue();

                if (e > mainE)
                {
                    u = tempDirec;
                    mainE = e;
                }
            }
        }
    }
    return u;
}

std::vector<std::string> Structure::increasePerformance2(std::string s, std::vector<std::string> tempDirec, char monomer)
{
    repairCount = 0;

    int len = s.length();
    Operators op;
    std::vector<std::vector<int> > direc_coordinate = op.getCoordinates(s, tempDirec);
    int x, y, z;

    int count;
    std::string direc = tempDirec[0];
    int start = 1, end;

    getEnergy(s, tempDirec);
    int mainE = getEnergyValue();

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, (len / 5) - 1);

    count = 0;

    std::vector<std::string> direc_name({ "L", "R", "U", "D", "F", "B" });

    for (int k = 1; k < len; k++)
    {
        if (s[k] == monomer)
        {
            count++;
            continue;
        }
        else
        {
            if (count > 2)
            {
                end = k - 1;
                for (int i = start; i <= end; i++)
                {
                    if (hasDistance(tempDirec[k], k))
                    {
                        direc_coordinate = op.getCoordinates(s, tempDirec);
                        bool check;

                        x = direc_coordinate[i - 1][0];
                        y = direc_coordinate[i - 1][1];
                        z = direc_coordinate[i - 1][2];

                        int has = 0;
                        for (int j = 0; j < len; j++)
                        {
                            if (direc_coordinate[j][0] == x + 1 && direc_coordinate[j][1] == y && direc_coordinate[j][2] == z)
                            {
                                has = 1;
                                break;
                            }
                        }
                        if (has == 0)
                        {
                            tempDirec[k] = 'R';
                            tempDirec = repairAndEvaluate(s, tempDirec);
                            repairCount++;
                            getEnergy(s, tempDirec);
                            int e = getEnergyValue();

                            if (e > mainE)
                            {
                                mainE = e;
                            }
                        }

                        has = 0;
                        for (int j = 0; j < len; j++)
                        {
                            if (direc_coordinate[j][0] == x - 1 && direc_coordinate[j][1] == y && direc_coordinate[j][2] == z)
                            {
                                has = 1;
                                break;
                            }
                        }
                        if (has == 0)
                        {
                            tempDirec[k] = 'L';
                            tempDirec = repairAndEvaluate(s, tempDirec);
                            repairCount++;
                            getEnergy(s, tempDirec);
                            int e = getEnergyValue();

                            if (e > mainE)
                            {
                                mainE = e;
                            }
                        }

                        has = 0;
                        for (int j = 0; j < len; j++)
                        {
                            if (direc_coordinate[j][0] == x && direc_coordinate[j][1] == y + 1 && direc_coordinate[j][2] == z)
                            {
                                has = 1;
                                break;
                            }
                        }
                        if (has == 0)
                        {
                            tempDirec[k] = 'U';
                            tempDirec = repairAndEvaluate(s, tempDirec);
                            repairCount++;
                            getEnergy(s, tempDirec);
                            int e = getEnergyValue();

                            if (e > mainE)
                            {
                                mainE = e;
                            }
                        }

                        has = 0;
                        for (int j = 0; j < len; j++)
                        {
                            if (direc_coordinate[j][0] == x && direc_coordinate[j][1] == y - 1 && direc_coordinate[j][2] == z)
                            {
                                has = 1;
                                break;
                            }
                        }
                        if (has == 0)
                        {
                            tempDirec[k] = 'D';
                            tempDirec = repairAndEvaluate(s, tempDirec);
                            repairCount++;
                            getEnergy(s, tempDirec);
                            int e = getEnergyValue();

                            if (e > mainE)
                            {
                                mainE = e;
                            }
                        }

                        has = 0;
                        for (int j = 0; j < len; j++)
                        {
                            if (direc_coordinate[j][0] == x && direc_coordinate[j][1] == y && direc_coordinate[j][2] == z + 1)
                            {
                                has = 1;
                                break;
                            }
                        }
                        if (has == 0)
                        {
                            tempDirec[k] = 'F';
                            tempDirec = repairAndEvaluate(s, tempDirec);
                            repairCount++;
                            getEnergy(s, tempDirec);
                            int e = getEnergyValue();

                            if (e > mainE)
                            {
                                mainE = e;
                            }
                        }

                        has = 0;
                        for (int j = 0; j < len; j++)
                        {
                            if (direc_coordinate[j][0] == x && direc_coordinate[j][1] == y && direc_coordinate[j][2] == z - 1)
                            {
                                has = 1;
                                break;
                            }
                        }
                        if (has == 0)
                        {
                            tempDirec[k] = 'B';
                            tempDirec = repairAndEvaluate(s, tempDirec);
                            repairCount++;
                            getEnergy(s, tempDirec);
                            int e = getEnergyValue();

                            if (e > mainE)
                            {
                                mainE = e;
                            }
                        }
                    }

                }

            }

            count = 0;
            start = k;
        }
    }
    return tempDirec;
}

std::vector<std::string> Structure::increasePerformance3(std::string s, std::vector<std::string> tempDirec, std::vector<std::string> target)
{
    unsigned long len = s.length();
    Operators op;

    std::vector<std::vector<int> > direc_coordinate = op.getCoordinates(s, tempDirec);

    int x, y, z, count;

    getEnergy(s, tempDirec);

    int mainE = getEnergyValue();

    std::string direc = tempDirec[0];
    char monomer = s[0];
    int start = 1, end;

    count = 0;


    for (int i = 0; i < len; i++)
    {
        if (hasDistance(tempDirec[i], i))
        {
            if (direc == tempDirec[i])
            {
                count++;
                continue;
            }
            else
            {
                if (count > 2)
                {
                    end = i - 1;

                    for (int k = start; k <= end; k++)
                    {

                        x = direc_coordinate[k - 1][0];
                        y = direc_coordinate[k - 1][1];
                        z = direc_coordinate[k - 1][2];

                        int has = 0;

                        for (int j = 0; i < len; j++)
                        {
                            if (direc_coordinate[j][0] == x + 1 && direc_coordinate[j][1] == y && direc_coordinate[j][2] == z)
                            {
                                has = 1;
                                break;
                            }
                        }
                        if (has == 0)
                        {
                            tempDirec[k] = "R";
                            tempDirec = repairAndEvaluate(s, tempDirec);

                            getEnergy(s, tempDirec);

                            int e = getEnergyValue();

                            if (e > mainE)
                            {
                                mainE = e;
                            }
                        }

                        has = 0;

                        for (int j = 0; j < len; j++)
                        {
                            if (direc_coordinate[j][0] == x - 1 && direc_coordinate[j][1] == y && direc_coordinate[j][2] == z)
                            {
                                has = 1;
                                break;
                            }
                        }
                        if (has == 0)
                        {
                            tempDirec[k] = "L";

                            tempDirec = repairAndEvaluate(s, tempDirec);

                            getEnergy(s, tempDirec);

                            int e = getEnergyValue();

                            if (e > mainE)
                            {
                                mainE = e;
                            }
                        }

                        has = 0;

                        for (int j = 0; j < len; j++)
                        {
                            if (direc_coordinate[j][0] == x && direc_coordinate[j][1] == y + 1 && direc_coordinate[j][2] == z)
                            {
                                has = 1;
                                break;
                            }
                        }
                        if (has == 0)
                        {
                            tempDirec[k] = "U";

                            tempDirec = repairAndEvaluate(s, tempDirec);

                            getEnergy(s, tempDirec);

                            int e = getEnergyValue();

                            if (e > mainE)
                            {
                                mainE = e;
                            }
                        }

                        has = 0;

                        for (int j = 0; j < len; j++)
                        {
                            if (direc_coordinate[j][0] == x && direc_coordinate[j][1] == y - 1 && direc_coordinate[j][2] == z)
                            {
                                has = 1;
                                break;
                            }
                        }
                        if (has == 0)
                        {
                            tempDirec[k] = 'D';

                            tempDirec = repairAndEvaluate(s, tempDirec);

                            getEnergy(s, tempDirec);

                            int e = getEnergyValue();

                            if (e > mainE)
                            {
                                mainE = e;
                            }
                        }

                        has = 0;

                        for (int j = 0; j < len; j++)
                        {
                            if (direc_coordinate[j][0] == x && direc_coordinate[j][1] == y && direc_coordinate[j][2] == z + 1)
                            {
                                has = 1;
                                break;
                            }
                        }
                        if (has == 0)
                        {
                            tempDirec[k] = 'F';

                            tempDirec = repairAndEvaluate(s, tempDirec);

                            getEnergy(s, tempDirec);

                            int e = getEnergyValue();

                            if (e > mainE)
                            {
                                mainE = e;
                            }
                        }

                        has = 0;

                        for (int j = 0; j < len; j++)
                        {
                            if (direc_coordinate[j][0] == x && direc_coordinate[j][1] == y && direc_coordinate[j][2] == z - 1)
                            {
                                has = 1;
                                break;
                            }
                        }
                        if (has == 0)
                        {
                            tempDirec[k] = 'B';

                            tempDirec = repairAndEvaluate(s, tempDirec);

                            getEnergy(s, tempDirec);

                            int e = getEnergyValue();

                            if (e > mainE)
                            {
                                mainE = e;
                            }
                        }
                    }
                }
                count = 0;
                start = i;
                direc = tempDirec[i];
                monomer = s[i];
            }
        }
    }
    return tempDirec;
}
#pragma endregion Performance increase functions

#pragma region Innefective collision functions
std::vector<std::string> Structure::onWallInnefectiveCollision(std::string s, std::vector<std::string>  popI)
{
    int len = s.length();

    std::string temp;
    std::vector<std::string> direc_name({ "L", "R", "U", "D", "F", "B" });
    int select;

    std::random_device rd;
    std::mt19937 mt(rd());

    int nPoint = 1 + poisson(3);
    std::uniform_int_distribution<int> dist(0, (len - nPoint) - 1);
    int r = dist(mt);

    for (int i = r; i < r + nPoint; i++)
    {
        select = (int)poisson(6);

        if (popI[i] == direc_name[select])
        {
            i--;
            continue;
        }

        popI[i] = direc_name[select];
    }

    return popI;
}

std::vector<std::string> Structure::onWallIneffectiveCollision1(std::string s, std::vector<std::string> popI, std::vector<std::string> u)
{
    int len = s.length();
    std::string temp;

    std::random_device rd;
    std::mt19937 mt(rd());

    std::uniform_int_distribution<int> dist(0, len - 1);
    int nPoint = dist(mt);
    dist = std::uniform_int_distribution<int>(0, len - nPoint - 1);
    int r = dist(mt);

    std::vector<std::string> direction({ "L", "R", "U", "D", "F", "B" });

    int min = 1000, value = 0, pos = 0;

    for (int i = r; i < r + nPoint; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            popI[i] = direction[j];
            value = hammingDistance(s, popI, u);
            if (min > value)
            {
                min = value;
                pos = j;
            }
        }
        if (u[i] == direction[pos])
        {
            popI[i] = direction[pos];
        }
        else
        {
            popI[i] = u[i];
        }
    }
    return popI;
}

std::vector<std::string> Structure::onWallIneffectiveCollision2(std::string s, std::vector<std::string> & popI)
{
    int len = s.length();
    std::string temp;

    std::random_device rd;
    std::mt19937 mt(rd());

    std::uniform_int_distribution<int> dist(0, len - 1);

    int r = dist(mt);;
    r = 33;
    popI[r] = opp(popI[r]);
    return popI;
}
#pragma endregion Innefective collision functions

#pragma region Decomposition functions
std::vector<std::vector<std::string> > Structure::decomposition(std::string s, std::vector<std::string> u1)
{
    int len = s.length();
    std::string temp;
    std::vector<std::string> cki(len);
    std::vector<std::string> ckj(len);
    std::vector<std::vector<std::string> > returnArr(2, std::vector<std::string>(len));
    int mid = (int)poisson(len);

    std::vector<std::string> direc({ "R", "L", "U", "D", "F", "B" });

    for (int i = 0; i < mid; i++)
    {
        cki[i] = u1[i];
        temp = u1[i];
        if (hasDistance(u1[i], i))
        {
            ckj[i] = opp(temp);
        }
        else
        {
            ckj[i] = temp;
        }
        ckj[i] = u1[i];
    }
    for (int i = mid; i < len; i++) {
        temp = u1[i];

        if (hasDistance(u1[i], i)) {
            cki[i] = opp(temp);
        }
        else
        {
            cki[i] = temp;
        }
        ckj[i] = u1[i];
    }

    returnArr[0] = cki;
    returnArr[1] = ckj;

    return returnArr;
}

std::vector<std::vector<std::string> > Structure::decomposition1(std::string s, std::vector<std::string> popI, std::vector<std::string> u)
{
    std::vector<std::string> u1 = popI;
    int len = s.length();

    std::random_device rd;
    std::mt19937 mt(rd());

    std::uniform_int_distribution<int> dist(0, 1);
    std::uniform_real_distribution<double> dist2(0, 1);
    int arrSize = 1 + dist(mt);

    std::vector<int> partArr(arrSize);
    std::string temp;

    std::vector<std::string> cki(len);
    std::vector<std::string> ckj(len);

    cki = u1;
    ckj = u1;

    std::vector<std::vector<std::string> > returnArr(2, std::vector<std::string>(len));

    int partLen = len / arrSize;
    int maind = hammingDistance(s, u1, u);

    for (int i = 0; i < arrSize; i++)
    {
        partArr[i] = 0;

        for (int j = i * partLen; j < (i * partLen + partLen); j++)
        {
            if (u1[j] == u[j])
            {
                partArr[i]++;
            }
        }
    }

    int min = partArr[0];
    int p = 0;

    for (int i = 1; i < arrSize; i++)
    {
        if (min > partArr[i])
        {
            min = partArr[i];
            p = i;
        }
    }

    int i = 0;
    int select;
    std::vector<std::string> direc_name({ "L", "R", "U", "D", "F", "B" });

    for (int i = 0; i < (p * partLen + (partLen / 2)); i++)
    {
        temp = u[i];

        select = (int)(dist2(mt) * 6); // dist2 generator will generate double between 0 and 1

        if (temp != u[i])
        {
            cki[i] = temp;
            continue;
        }
    }

    for (int j = i; j < (p * partLen + (partLen / 2)); j++)
    {
        temp = u[j];

        select = (int)(dist2(mt) * 6); // This random is used from Math library

        if (temp != u[j])
        {
            ckj[j] = u[j];
            continue;
        }
    }

    returnArr[0] = cki;
    returnArr[1] = ckj;

    return returnArr;
}

std::vector<std::vector<std::string> > Structure::decomposition2(std::string s, std::vector<std::string> u1)
{
    int len = s.length();
    std::string temp;
    std::vector<std::string> cki(len);
    std::vector<std::string> ckj(len);
    std::vector<std::vector<std::string> > returnArr(2, std::vector<std::string>(len, ""));

    std::random_device rd;
    std::mt19937 mt(rd());

    std::uniform_real_distribution<double> dist(0, 1);

    int mid = 1 + (int)(dist(mt) * len);

    for (int i = 0; i < mid; i++)
    {
        cki[i] = u1[i];
        temp = u1[i];
        ckj[i] = opp(temp);
    }
    for (int i = mid; i < len; i++)
    {
        temp = u1[i];
        cki[i] = opp(temp);
        ckj[i] = u1[i];
    }

    returnArr[0] = cki;
    returnArr[1] = ckj;

    return returnArr;
}
#pragma endregion Decomposition functions

#pragma region Collision functions
std::vector<std::vector<std::string> > Structure::interMolecularIneffectiveCollision(std::string s, std::vector<std::string> & popI, std::vector<std::string> & popJ)
{
    int len = s.length();

    int nPoint = 1 + poisson(2);
    int r = poisson(len);

    std::string temp;

    if (nPoint % 2 != 0)
    {
        if (hasDistance(popI[r], r))
        {
            popI[r] = opp(popI[r]);
        }

        if (hasDistance(popJ[r], r))
        {
            popJ[r] = opp(popJ[r]);
        }
    }

    if (nPoint % 2 == 0)
    {
        for (int i = r; i < len; i++)
        {
            if (hasDistance(popI[r], r))
            {
                popJ[r] = opp(popJ[r]);
            }

            if (hasDistance(popJ[r], r))
            {
                popJ[r] = opp(popJ[r]);
            }
        }

    }

    std::vector<std::vector<std::string> > returnArr(2, std::vector<std::string>(len));

    returnArr[0] = popI;
    returnArr[1] = popJ;

    return returnArr;
}

std::vector<std::vector<std::string> > Structure::interMolecularIneffectiveCollision1(std::string s, std::vector<std::string> popI, std::vector<std::string> & popJ, std::vector<std::string> & u1)
{
    int len = s.length();

    std::random_device rd;
    std::mt19937 mt(rd());

    std::uniform_int_distribution<int> dist(0, 1);
    int nPoint = 1 + dist(mt);
    dist = std::uniform_int_distribution<int>(0, len - 1);

    int r = dist(mt);

    std::string temp;

    if (nPoint % 2 != 0)
    {
        temp = popI[r];
        popI[r] = popJ[r];
        popJ[r] = temp;
    }
    if (nPoint % 2 == 0)
    {
        for (int i = r; i < len; i++)
        {
            temp = popI[i];
            popI[i] = popJ[i];
            popJ[i] = temp;
        }
    }

    std::vector<std::vector<std::string> > returnArr(2, std::vector<std::string>(len));;

    returnArr[0] = popI;
    returnArr[1] = popJ;

    return returnArr;
}

std::vector<std::vector<std::string> > Structure::interMolecularIneffectiveCollision2(std::string s, std::vector<std::string> & popI, std::vector<std::string> & popJ)
{
    int len = s.length();

    std::random_device rd;
    std::mt19937 mt(rd());

    std::uniform_int_distribution<int> dist(0, len - 1);
    int r = 29;
    std::string temp;
    temp = popI[r];
    popI[r] = popJ[r];
    popJ[r] = temp;

    std::vector<std::vector<std::string> > returnArr(2, std::vector<std::string>(len));

    returnArr[0] = popI;
    returnArr[1] = popJ;

    return returnArr;
}
#pragma endregion Collision functions

#pragma region Synth functions
std::vector<std::string> Structure::synthesis(std::string s, std::vector<std::string> cki, std::vector<std::string> ckj)
{
    int len = s.length();

    std::vector<std::string> returnArr(len);
    returnArr = cki;

    int partNum = (int)(1 + (poisson(5)));
    int partLen = len / partNum;

    std::vector<int> partArr1(partNum);
    std::vector<int> partArr2(partNum);

    getEnergy(s, cki);

    for (int i = 0; i < partNum; i++)
    {
        partArr1[i] = 0;
        for (int j = i * partLen; j < (i * partLen + partLen); j++)
        {
            if (!hasDistance(cki[j], j))
            {
                partArr1[i]++;
            }
        }
    }
    getEnergy(s, ckj);

    for (int i = 0; i < partNum; i++)
    {
        partArr2[i] = 0;

        for (int j = i * partLen; j < (i * partLen + partLen); j++)
        {
            if (!hasDistance(ckj[j], j))
            {
                partArr2[i]++;
            }
        }
    }

    for (int i = 0; i < partNum; i++)
    {
        if (partArr1[i] >= partArr2[i])
        {
            for (int j = i * partLen; j < (i * partLen + partLen); j++)
            {
                returnArr[j] = cki[j];
            }
        }
        else
        {
            for (int j = i * partLen; j < (i * partLen + partLen); j++)
            {
                returnArr[j] = ckj[j];
            }
        }
    }

    return returnArr;
}

std::vector<std::string> Structure::synthesis1(std::string s, std::vector<std::string> cki, std::vector<std::string> ckj, std::vector<std::string> u1)
{
    int len = s.length();

    std::vector<std::string> returnArr(len);
    returnArr = cki;

    std::random_device rd;
    std::mt19937 mt(rd());

    std::uniform_real_distribution<> dist(0, 1);

    int partNum = (int)(1 + (dist(mt) * (10)));

    std::vector<int> partArr1(partNum);
    std::vector<int> partArr2(partNum);

    int partLen = len / partNum;

    for (int i = 0; i < partNum; i++)
    {
        partArr1[i] = 0;
        for (int j = i * partLen; j < (i * partLen + partLen); j++)
        {
            if (cki[j] == u1[j])
            {
                partArr1[i]++;
            }
        }
    }

    getEnergy(s, ckj);

    for (int i = 0; i < partNum; i++)
    {
        partArr2[i] = 0;

        for (int j = i * partLen; j < (i * partLen + partLen); j++)
        {
            if (ckj[j] == u1[j])
            {
                partArr2[i]++;
            }
        }
    }

    for (int i = 0; i < partNum; i++)
    {
        if (partArr1[i] >= partArr2[i])
        {
            for (int j = i * partLen; j < (i * partLen + partLen); j++)
            {
                returnArr[j] = cki[j];
            }

        }
        else
        {
            for (int j = i * partLen; j < (i * partLen + partLen); j++)
            {
                returnArr[j] = ckj[j];
            }
        }
    }

    return returnArr;
}

std::vector<std::string> Structure::synthesis2(std::string s, std::vector<std::string> cki, std::vector<std::string> ckj)
{
    int len = s.length();

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dist(0, len - 1);
    int r = dist(mt);

    std::string temp;

    for (int i = r; i < len; i++)
    {
        temp = cki[i];
        cki[i] = ckj[i];
        ckj[i] = temp;
    }

    getEnergy(s, cki);

    int e1 = getEnergyValue();

    getEnergy(s, ckj);

    int e2 = getEnergyValue();

    if (e1 < e2)
    {
        return ckj;
    }
    else
    {
        return cki;
    }
}
#pragma endregion Synth functions

#pragma region Misc
// Function will generate a random double number between 0 and 1
double Structure::uniform()
{
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<> distr(0, 1); // Generate a random double number between 0.0 and 1.0
    return distr(eng);
}

int Structure::poisson(int lambda)
{
    int k = 0;
    double p = 1.0;

    double expLambda = exp(-lambda);

    do
    {
        k++;
        p *= uniform();
    } while (p >= expLambda);

    if (k <= 6)
    {
        return k - 1;
    }
    else
    {
        std::cout << k % lambda;
        return k % lambda;
    }
}

bool Structure::overlap(std::string s, std::vector<std::string> d)
{
    Operators op;
    std::vector<std::vector<int> > direc_coordinate = op.getCoordinates(s, u);

    int overlap = 0;
    int len = s.length();
    int x, y, z;

    for (int k = 0; k < len; k++)
    {
        x = direc_coordinate[k][0];
        y = direc_coordinate[k][0];
        z = direc_coordinate[k][0];

        for (int m = 0; m < len; m++)
        {
            if (direc_coordinate[m][0] == x && direc_coordinate[m][1] == y && direc_coordinate[m][2] == z)
            {
                overlap = 1;
                break;
            }
        }
    }
    if (overlap == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Structure::hasDistance(std::string s, int i)
{
    if (d[i] == s)
    {
        return false;
    }

    return true;
}

int Structure::hammingDistance(std::string s, std::vector<std::string> presentDir, std::vector<std::string> targetDir)
{
    unsigned long len = s.length();
    int diff = 0;
    for (int i = 1; i < len; i++)
    {
        if (presentDir[i] != targetDir[i])
        {
            diff++;
        }
    }
    return diff;
}

std::vector<int> Structure::getEnergy(std::string s, std::vector<std::string> u)
{
    unsigned long len = s.length();

    int x, y, z, x1, y1, z1, i;
    std::vector<int> e(len, 0);
    Operators op;
    std::vector<std::vector<int> > direc_coordinate = op.getCoordinates(s, u);

    for (i = 0; i < len; i++)
    {
        int energySum = 0;

        if (s[i] == 'H')
        {
            x = direc_coordinate[i][0];
            y = direc_coordinate[i][1];
            z = direc_coordinate[i][2];

            for (int j = i + 2; j < len; j++)
            {
                if (s[j] == 'H')
                {
                    x1 = direc_coordinate[j][0];
                    y1 = direc_coordinate[j][1];
                    z1 = direc_coordinate[j][2];

                    if ((x + 1 == x1 || x - 1 == x1) && y == y1 && z == z1)
                    {
                        energySum++;
                    }
                    else if (x == x1 && (y + 1 == y1 || y - 1 == y1) && z == z1)
                    {
                        energySum++;
                    }
                    else if (x == x1 && y == y1 && (z + 1 == z1 || z - 1 == z1))
                    {
                        energySum++;
                    }
                }
            }
        }

        e[i] = energySum;
    }

    int energySum = 0;

    for (int l = 0; l < len; l++)
    {
        energySum += e[l];
    }

    setEnergyValue(energySum);
    this->e = e;

    return e;
}

int Structure::getEnergyByPos(std::string s, std::vector<std::string> u, int pos)
{
    int len = pos;

    int x, y, z, x1, y1, z1, i;
    std::vector<int> e(len, 0);

    Operators op;
    std::vector<std::vector<int> > direc_coordinate = op.getCoordinates(s, u, len);

    for (i = 0; i < len; i++)
    {
        int energySum = 0;

        if (s[i] == 'H')
        {
            x = direc_coordinate[i][0];
            y = direc_coordinate[i][1];
            z = direc_coordinate[i][2];

            for (int j = i + 2; j < len; j++)
            {
                if (s[j] == 'H')
                {
                    x1 = direc_coordinate[j][0];
                    y1 = direc_coordinate[j][1];
                    z1 = direc_coordinate[j][2];

                    if ((x + 1 == x1 || x - 1 == x1) && y == y1 && z == z1)
                    {
                        energySum++;
                    }
                    else if (x == x1 && (y + 1 == y1 || y - 1 == y1) && z == z1)
                    {
                        energySum++;
                    }
                    else if (x == x1 && y == y1 && (z + 1 == z1 || z - 1 == z1))
                    {
                        energySum++;
                    }
                }
            }
        }

        e[i] = energySum;
    }

    int energySum = 0;

    for (int l = 0; l < len; l++)
    {
        energySum += e[l];
    }

    setEnergyValue(energySum);

    return energySum;
}

int Structure::numOfH(std::string sequence, int start, int end)
{
    int count = 0;

    for (int i = start; i < end; i++)
    {
        if (sequence[i] == 'H')
        {
            count++;
        }
    }

    return count;
}

std::vector<std::string> Structure::Hcomplience(std::string s, std::vector<std::string> u)
{
    std::vector<std::string> preDir = u;
    int len = s.length();
    Operators op;
    std::vector<std::vector<int> > coordinate(len, std::vector<int>(3, 0)); /// TODO: Should it be initialized with len and 3?

    coordinate = op.getCoordinates(s, preDir);

    int centerX = 0, centerY = 0, centerZ = 0;
    int count = 0;
    int flag = 0;

    for (int i = 0; i < len; i++)
    {
        if (s[i] == 'H')
        {
            centerX = coordinate[i][0];
            centerY = coordinate[i][1];
            centerZ = coordinate[i][2];
            break;
        }
    }

    for (int i = len - 1; i > 0; i--)
    {
        if (s[i] == 'H')
        {
            centerX = coordinate[i][0];
            centerY = coordinate[i][1];
            centerZ = coordinate[i][2];
            break;
        }
    }

    centerX /= 2;
    centerY /= 2;
    centerZ /= 2;

    count = 0;

    std::vector<std::vector<double> > hc(len, std::vector<double>(6));
    double min = 1000, max = 0;
    int dir = 0;
    getEnergy(s, preDir);
    int energy1st = getEnergyValue();
    std::vector<int> energy(6);
    std::vector<std::string> direc_name({ "R", "L", "U", "D", "B", "F" });
    preDir = u;

    coordinate = op.getCoordinates(s, preDir);
    int start = 0, end;

    for (int i = 0; i < len; i++)
    {
        if (hasDistance(s, i))
        {
            if (s[i] == 'H')
            {
                count++;
            }
            else
            {
                if (count > 4)
                {
                    end = i - 1;
                    for (int l = start; l <= end; l++)
                    {
                        for (int j = 0; j < 6; j++)
                        {
                            preDir[l] = direc_name[j];
                            preDir = repairAndEvaluate(s, preDir);
                            coordinate = op.getCoordinates(s, preDir);

                            hc[l][j] = sqrt(pow(centerX - coordinate[l][0], 2) + pow((centerY - coordinate[l][1]), 2) + pow((centerZ - coordinate[l][2]), 2));

                            if (hc[l][j] < min)
                            {
                                min = hc[l][j];
                                u = preDir;
                            }
                        }
                    }
                }
            }

            count = 0;
            start = i;
        }
    }

    return u;
}

std::vector<std::string> Structure::Pcomplience(std::string s, std::vector<std::string> u, std::vector<std::string> target)
{
    std::vector<std::string> preDir = u;
    int len = s.length();
    Operators op;
    std::vector<std::vector<int> > coordinate = op.getCoordinates(s, preDir);

    int centerX = 0, centerY = 0, centerZ = 0;
    int count, flag = 0;

    for (int i = 0; i < len; i++)
    {
        if (s[i] == 'H')
        {
            centerX = coordinate[i][0];
            centerY = coordinate[i][1];
            centerZ = coordinate[i][2];
            break;
        }
    }

    for (int i = len - 1; i > 0; i--)
    {
        if (s[i] == 'H')
        {
            centerX += coordinate[i][0];
            centerY += coordinate[i][1];
            centerZ += coordinate[i][2];
            break;
        }
    }

    centerX /= 2;
    centerY /= 2;
    centerZ /= 2;

    count = 0;

    std::vector<std::vector<double> > hc(len, std::vector<double>(6));
    double min = 1000, max = 0;
    int dir = 0;
    getEnergy(s, preDir);
    int energy1st = getEnergyValue();
    std::vector<int> energy(6);
    std::vector<std::string> direc_name({ "R", "L", "U", "D", "F", "B" });
    preDir = u;
    coordinate = op.getCoordinates(s, preDir);

    int start = 0, end;

    for (int i = 0; i < len; i++)
    {
        if (s[i] == 'P')
        {
            count++;
        }
        else
        {
            if (count > 4)
            {
                end = i - 1;

                for (int l = start; l <= end; l++)
                {
                    for (int j = 0; j < 6; j++)
                    {
                        preDir[l] = direc_name[j];

                        preDir = repairAndEvaluate(s, preDir);
                        coordinate = op.getCoordinates(s, preDir);
                        hc[l][j] = sqrt(pow((centerX - coordinate[l][0]), 2) + pow((centerY - coordinate[l][1]), 2) + pow((centerZ - coordinate[l][2]), 2));
                        if (hc[l][j] > max)
                        {
                            max = hc[l][j];
                            u = preDir;
                        }
                    }
                }
            }
            count = 0;
            start = i;
        }
    }
    return u;
}

std::vector<std::string> Structure::evaluate(std::string s, std::vector<std::string> d)
{
    repairCount = 0;

    int len = s.length();
    Operators op;
    std::vector<std::vector<int> > direc_coordinate = op.getCoordinates(s, d);
    int x, y, z;

    getEnergy(s, d);
    int mainE = getEnergyValue();
    std::vector<std::string> tempDirec = d;
    for (int k = len - 1; k > 0; k--)
    {
        if (hasDistance(tempDirec[k], k))
        {
            
            bool check;

            x = direc_coordinate[k - 1][0];
            y = direc_coordinate[k - 1][1];
            z = direc_coordinate[k - 1][2];

            int has = 0;

            for (int j = 0; j < len; j++)
            {
                if (direc_coordinate[j][0] == x + 1 && direc_coordinate[j][1] == y && direc_coordinate[j][2] == z)
                {
                    has = 1;
                    break;
                }

            }
            if (has == 0)
            {
                tempDirec[k] = 'R';
                tempDirec = repairAndEvaluate(s, tempDirec);
                repairCount++;
                getEnergy(s, tempDirec);

                int e = getEnergyValue();

                if (e > mainE)
                {
                    mainE = e;
                }
            }
            has = 0;

            for (int j = 0; j < len; j++)
            {
                if (direc_coordinate[j][0] == x - 1 && direc_coordinate[j][1] == y && direc_coordinate[j][2] == z)
                {
                    has = 1;
                    break;
                }

            }
            if (has == 0)
            {
                tempDirec[k] = 'L';
                tempDirec = repairAndEvaluate(s, tempDirec);
                repairCount++;
                getEnergy(s, tempDirec);

                int e = getEnergyValue();

                if (e > mainE)
                {
                    mainE = e;
                }
            }
            has = 0;

            for (int j = 0; j < len; j++)
            {
                if (direc_coordinate[j][0] == x && direc_coordinate[j][1] == y + 1 && direc_coordinate[j][2] == z)
                {
                    has = 1;
                    break;
                }

            }
            if (has == 0)
            {
                tempDirec[k] = 'U';
                tempDirec = repairAndEvaluate(s, tempDirec);
                repairCount++;
                getEnergy(s, tempDirec);

                int e = getEnergyValue();

                if (e > mainE)
                {
                    mainE = e;
                }
            }
            has = 0;

            for (int j = 0; j < len; j++)
            {
                if (direc_coordinate[j][0] == x && direc_coordinate[j][1] == y - 1 && direc_coordinate[j][2] == z)
                {
                    has = 1;
                    break;
                }

            }
            if (has == 0)
            {
                tempDirec[k] = 'D';
                tempDirec = repairAndEvaluate(s, tempDirec);
                repairCount++;
                getEnergy(s, tempDirec);

                int e = getEnergyValue();

                if (e > mainE)
                {
                    mainE = e;
                }
            }
            has = 0;

            for (int j = 0; j < len; j++)
            {
                if (direc_coordinate[j][0] == x && direc_coordinate[j][1] == y && direc_coordinate[j][2] == z + 1)
                {
                    has = 1;
                    break;
                }

            }
            if (has == 0)
            {
                tempDirec[k] = 'F';
                tempDirec = repairAndEvaluate(s, tempDirec);
                repairCount++;
                getEnergy(s, tempDirec);

                int e = getEnergyValue();

                if (e > mainE)
                {
                    mainE = e;
                }
            }
            has = 0;

            for (int j = 0; j < len; j++)
            {
                if (direc_coordinate[j][0] == x && direc_coordinate[j][1] == y && direc_coordinate[j][2] == z - 1)
                {
                    has = 1;
                    break;
                }

            }
            if (has == 0)
            {
                tempDirec[k] = 'B';
                tempDirec = repairAndEvaluate(s, tempDirec);
                repairCount++;
                getEnergy(s, tempDirec);

                int e = getEnergyValue();

                if (e > mainE)
                {
                    mainE = e;
                }
            }
        }
    }
    return tempDirec;
}

std::vector<std::string> Structure::repairAndEvaluate(std::string s, std::vector<std::string> u)
{
    int len = s.length();
    Operators op;
    std::vector<std::vector<int> > direc_coordinate = op.getCoordinates(s, u);
    int x, y, z;

    int overlap = 0;
    int count = 0;
    while (true)
    {
        count++;
        for (int i = len - 1; i >= 0; i--)
        {
            x = direc_coordinate[i][0];
            y = direc_coordinate[i][1];
            z = direc_coordinate[i][2];

            overlap = 0;
            int pos = i;

            for (int j = pos - 1; j >= 0; j--)
            {
                if (direc_coordinate[j][0] == x && direc_coordinate[j][1] == y && direc_coordinate[j][2] == z)
                {
                    overlap = 1;
                    break;
                }
            }

            std::string changedDirection = u[pos];

            if (overlap == 1)
            {
                x = direc_coordinate[pos - 1][0];
                y = direc_coordinate[pos - 1][1];
                z = direc_coordinate[pos - 1][2];

                int has;

                while (true)
                {
                    has = 0;

                    for (int j = 0; j < len; j++)
                    {
                        if (direc_coordinate[j][0] == x + 1 && direc_coordinate[j][1] == y && direc_coordinate[j][2] == z)
                        {
                            has = 1;
                            break;
                        }
                    }

                    if (has == 0 && u[pos - 1] != "L")
                    {
                        x = x + 1;
                        changedDirection = 'R';
                        break;
                    }

                    has = 0;

                    for (int j = 0; j < len; j++)
                    {
                        if (direc_coordinate[j][0] == x - 1 && direc_coordinate[j][1] == y && direc_coordinate[j][2] == z)
                        {
                            has = 1;
                            break;
                        }
                    }

                    if (has == 0 && u[pos - 1] != "R")
                    {
                        x = x - 1;
                        changedDirection = 'L';
                        break;
                    }

                    has = 0;

                    for (int j = 0; j < len; j++)
                    {
                        if (direc_coordinate[j][0] == x && direc_coordinate[j][1] == y + 1 && direc_coordinate[j][2] == z)
                        {
                            has = 1;
                            break;
                        }
                    }

                    if (has == 0 && u[pos - 1] != "D")
                    {
                        y = y + 1;
                        changedDirection = 'U';
                        break;
                    }

                    has = 0;

                    for (int j = 0; j < len; j++)
                    {
                        if (direc_coordinate[j][0] == x && direc_coordinate[j][1] == y - 1 && direc_coordinate[j][2] == z)
                        {
                            has = 1;
                            break;
                        }
                    }

                    if (has == 0 && u[pos - 1] != "U")
                    {
                        y = y - 1;
                        changedDirection = 'D';
                        break;
                    }

                    has = 0;

                    for (int j = 0; j < len; j++)
                    {
                        if (direc_coordinate[j][0] == x && direc_coordinate[j][1] == y && direc_coordinate[j][2] == z + 1)
                        {
                            has = 1;
                            break;
                        }
                    }

                    if (has == 0 && u[pos - 1] != "B")
                    {
                        z = z + 1;
                        changedDirection = 'F';
                        break;
                    }

                    has = 0;

                    for (int j = 0; j < len; j++)
                    {
                        if (direc_coordinate[j][0] == x && direc_coordinate[j][1] == y && direc_coordinate[j][2] == z - 1)
                        {
                            has = 1;
                            break;
                        }
                    }

                    if (has == 0 && u[pos - 1] != "F")
                    {
                        z = z - 1;
                        changedDirection = 'B';
                        break;
                    }
                    else
                    {
                        pos--;
                        if (pos < 1)
                        {
                            break;
                        }
                        x = direc_coordinate[pos - 1][0];
                        y = direc_coordinate[pos - 1][1];
                        z = direc_coordinate[pos - 1][2];
                    }
                }
                if (has == 0)
                {
                    direc_coordinate[pos][0] = x;
                    direc_coordinate[pos][1] = y;
                    direc_coordinate[pos][2] = z;
                    u[pos] = changedDirection;
                }
            }
        }
        overlap = 0;
        direc_coordinate = op.getCoordinates(s, u);

        for (int j = 0; j < len; j++)
        {
            for (int k = 0; k < j; k++)
            {
                if (direc_coordinate[j][0] == direc_coordinate[k][0] && direc_coordinate[j][1] == direc_coordinate[k][1] && direc_coordinate[j][2] == direc_coordinate[k][2])
                {
                    overlap = 1;
                    break;
                }
            }
        }

        if (overlap == 0)
        {
            break;
        }
    }
    std::vector<int> e = getEnergy(s, u);
    Structure con;
    con.setU(u);
    con.setE(e);

    return u;
}

std::string Structure::opp(std::string d)
{
    std::vector<std::string> direction({ "L", "R", "U", "D", "F", "B" });
    std::vector<std::string> oppDirection({ "R", "L", "D", "U", "B", "F" });
    int i;

    for (i = 0; i < 6; i++)
    {
        if (direction[i] == d)
        {
            break;
        }

    }

    return oppDirection[i];
}
#pragma endregion Misc

#pragma region Getters & Setters
void Structure::setE(std::vector<int> e)
{
    this->e = e;
}

std::vector<int> Structure::getE()
{
    return this->e;
}

void Structure::setU(std::vector<std::string> u)
{
    this->u = u;
}

std::vector<std::string> Structure::getU()
{
    return this->u;
}

void Structure::setEnergyValue(int energyValue)
{
    this->energyValue = energyValue;
}

int Structure::getEnergyValue()
{
    return this->energyValue;
}
#pragma endregion Getters & Setters
