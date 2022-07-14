//
//  Operators.cpp
//  CRO_Algorithm
//
//  Created by Domen Osojnik on 10/07/2021.
//

#include "Operators.h"
#include <iterator>
#include <fstream>

double Operators::CRO_PSP(int pop_size, std::string s, double moleCol, double initialKE, double KELossRate)
{
    std::vector<std::vector<std::string> > population = search_space_creation(s, pop_size, target);
    //population = {};
    //   

    //std::ifstream is("space_creation.txt");
    //std::istream_iterator<char> start(is), end;
    //std::vector<char> characters(start, end);
    //std::vector<std::string> bomba;
    //for (int i = 0; i < characters.size(); i)
    //{   
    //    bomba = {};
    //    for (int j = 0; j < 48; j++, i++)
    //    {
    //        std::string str(1, characters[i]);
    //        bomba.push_back(str);
    //    }
    //    population.push_back(bomba);
    //}


    double KE = initialKE;
    double r;
    struc.d = target;
    struc.getEnergy(sequence, target);

    s = sequence;
    int size = pop_size;
    double maxE = 0;
    int startP = (int)(initialKE / 2);
    int lastP = (int)(initialKE / 3);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);
    int alpha = (int)(startP + (dis(gen) * lastP));
    int beta = (int)(startP + (dis(gen) * lastP));

  /*  alpha = 59;
    beta = 71;*/

    std::vector<int> numHit(pop_size * 4, 0);
    std::vector<int> minHit(pop_size * 4, 0);
    std::vector<int> maxScore(pop_size * 4, 0);
    std::vector<std::string> maxStruc(length);
    int maxLen = 0;

    for (int loop = 0; loop < pop_size; loop++)
    {
        population[loop] = struc.repairAndEvaluate(sequence, population[loop]);

        repairCount++;

        struc.getEnergy(sequence, population[loop]);
        int energyValue = struc.getEnergyValue();
        maxScore[loop] = energyValue;
        numHit[loop] = (0);
        minHit[loop] = (0);
    }

    std::vector<std::vector<std::string> > decom = {};
    std::vector<std::string> direcArray = {};
    int loopcount = 1;

    // In java display was used?
    std::cout << "\nInitial Kinetic Energy : " << KE << "\n";
    std::cout << "Alpha = " << alpha << " Beta = " << beta << "\n";
    std::cout << "------------------------------------------------------------------------------\n\n";

    int dec, onWall, syn, inter;

    try
    {
        for (; KE >= 0;)
        {
            if (stoppingConditionMet(energyValue))
            {
                break;
            }

            dec = 0;
            onWall = 0;
            syn = 0;
            inter = 0;

            for (int j = 0; j < pop_size; j++)
            {
                population[j] = struc.evaluate(sequence, population[j]);
                repairCount += struc.repairCount;
            }

            loopcount++;

            for (int i = 0; i < pop_size; i++)
            {
                r = dis(gen);

                if (r > moleCol)
                {
                    if (numHit[i] - minHit[i] > alpha)
                    {
                        dec++;
                        decom = this->struc.decomposition2(sequence, population[i]);

                        this->struc.getEnergy(sequence, population[i]);
                        int energy1 = this->struc.getEnergyValue();

                        decom[0] = this->struc.repairAndEvaluate(sequence, decom[0]);
                        repairCount++;

                        decom[1] = this->struc.repairAndEvaluate(sequence, decom[1]);
                        repairCount++;

                        // std::copy(decom.begin(), decom.end(), back_inserter(vect2)); TODO:
                        std::copy_n(decom[0].begin(), length, population[size].begin());
                        for (int i = 0; i < length; i++)
                        {
                            population[size + i] = decom[i];
                        }

                        this->struc.getEnergy(sequence, population[size]);
                        energyValue = this->struc.getEnergyValue();

                        maxScore[size] = energyValue;

                        if (energy1 < energyValue)
                        {
                            numHit[size] = numHit[i] + 1;
                            minHit[size] = minHit[i] + 1;
                        }
                        else
                        {
                            numHit[size] = 1;
                            minHit[size] = 1;
                        }

                        size++;

                        //system array copy TODO:
                        std::copy_n(decom[1].begin(), length, population[size].begin());

                        this->struc.getEnergy(sequence, population[size]);
                        energyValue = this->struc.getEnergyValue();

                        maxScore[size] = energyValue;

                        if (energy1 < energyValue)
                        {
                            numHit[size] = numHit[i] + 1;
                            minHit[size] = minHit[i] + 1;
                        }
                        else
                        {
                            numHit[size] = 1;
                            minHit[size] = 1;
                        }

                        size++;
                        numHit[i]++;
                    }
                    else
                    {
                        onWall++;
                        direcArray = this->struc.onWallIneffectiveCollision2(sequence, population[i]);
                        this->struc.getEnergy(sequence, population[i]);
                        int energy1 = this->struc.getEnergyValue();
                        
                        direcArray = this->struc.repairAndEvaluate(sequence, direcArray);
                        repairCount++;

                        // array copy TODO:
                        std::copy_n(direcArray.begin(), length, population[size].begin());

                        this->struc.getEnergy(sequence, population[size]);
                        energyValue = this->struc.getEnergyValue();

                        maxScore[size] = energyValue;

                        if (energy1 < energyValue)
                        {
                            numHit[size] = numHit[i] + 1;
                            minHit[size] = minHit[i] + 1;
                        }
                        else
                        {
                            numHit[size] = 1;
                            minHit[size] = 1;
                        }
                        size++;
                        numHit[i]++;
                    }
                }
                else
                {
                    int j;
                    do
                    {
                        j = (int)(dis(gen) * pop_size);
                    } while (i == j);

                    if (KE <= beta)
                    {
                        syn++;
                        std::vector<std::string> temp = this->struc.synthesis2(sequence, population[i], population[j]);

                        this->struc.getEnergy(sequence, population[i]);
                        int energy1 = this->struc.getEnergyValue();
                        this->struc.getEnergy(sequence, population[j]);
                        int energy2 = this->struc.getEnergyValue();

                        temp = this->struc.repairAndEvaluate(sequence, temp);
                        repairCount++;

                        // System.arraycopy(temp, 0 , population[size], 0, length); TODO:
                        std::copy_n(temp.begin(), length, population[size].begin());

                        this->struc.getEnergy(sequence, population[size]);
                        int energyValue = this->struc.getEnergyValue();

                        maxScore[size] = energyValue;

                        if (energy1 < energyValue || energy2 < energyValue)
                        {
                            numHit[size] = numHit[i] + 1;
                            minHit[size] = minHit[i] + 1;
                        }
                        else
                        {
                            numHit[size] = 1;
                            minHit[size] = 1;
                        }

                        size++;
                        numHit[i]++;
                        minHit[j]++;;
                    }
                    else
                    {
                        inter++;
                        std::vector<std::vector<std::string> > temp = this->struc.interMolecularIneffectiveCollision2(sequence, population[i], population[j]);

                        int energy1 = this->struc.getEnergyValue();
                        this->struc.getEnergy(sequence, population[j]);
                        int energy2 = this->struc.getEnergyValue();

                        temp[0] = this->struc.repairAndEvaluate(sequence, temp[0]);
                        repairCount++;

                        temp[1] = this->struc.repairAndEvaluate(sequence, temp[1]);
                        repairCount++;

                        //System.arraycopy(temp[0], 0, population[size], 0, length)
                        std::copy_n(temp[0].begin(), length, population[size].begin());

                        this->struc.getEnergy(sequence, population[size]);
                        int energyValue = this->struc.getEnergyValue();

                        maxScore[size] = energyValue;

                        if (energy1 < energyValue)
                        {
                            numHit[size] = numHit[i] + 1;
                            minHit[size] = minHit[i] + 1;
                        }
                        else
                        {
                            numHit[size] = 1;
                            minHit[size] = 1;
                        }

                        size++;

                        std::copy_n(temp[1].begin(), length, population[size].begin());

                        this->struc.getEnergy(sequence, population[size]);
                        energyValue = this->struc.getEnergyValue();

                        maxScore[size] = energyValue;

                        if (energy2 < energyValue)
                        {
                            numHit[size] = numHit[i] + 1;
                            minHit[size] = minHit[i] + 1;
                        }
                        else
                        {
                            numHit[size] = 1;
                            minHit[size] = 1;
                        }

                        size++;
                        numHit[i]++;
                        numHit[j]++;
                    }
                }
            }

            int e1, e2;

            for (int j = 0; j < size; j++)
            {

                int select = (int)(1 + dis(gen) * 2);
                char ch = 'P';

                if (select == 1)
                {
                    ch = 'H';
                }
                population[j] = this->struc.increasePerformance2(sequence, population[j], ch);
                repairCount += this->struc.repairCount;
            }

            int nHit, mHit, mScore;
            std::vector<std::string> iPop;

            std::vector<std::string> maxS = population[0];
            this->struc.getEnergy(sequence, maxS);

            for (int j = 0; j < size; j++)
            {
                this->struc.getEnergy(s, population[j]);
                e1 = this->struc.getEnergyValue();

                for (int k = j + 1; k < size; k++)
                {
                    this->struc.getEnergy(s, population[k]);
                    e2 = this->struc.getEnergyValue();

                    if (e1 < e2)
                    {
                        iPop = population[k];
                        nHit = numHit[k];
                        mHit = minHit[k];
                        mScore = maxScore[k];

                        population[k] = population[j];
                        numHit[k] = numHit[j];
                        minHit[k] = minHit[j];
                        maxScore[k] = maxScore[j];

                        population[j] = iPop;
                        numHit[j] = nHit;
                        minHit[j] = mHit;
                        maxScore[j] = mScore;
                        e1 = e2;
                    }
                }
            }
            this->struc.getEnergy(sequence, population[0]);
           

            energyValue = this->struc.getEnergyValue();

            if (energyValue > maxLen)
            {
                //System.arraycopy(population[0], 0, maxStruc, 0, length); TODO:

                std::copy_n(population[0].begin(), length, maxStruc.begin());

                maxLen = energyValue;
            }

            std::cout << "\nEnergy Value : " << energyValue << " when Kinetic Energy " << KE << " \n\n";
            std::cout << "Direction array : ";

            for (int j = 1; j < length; j++)
            {
                std::cout << population[0][j] + " ";
            }
            std::cout << "\n\n";
            std::cout << "Decomposition: " << dec << "  On-wall Ineffective Collision: " << onWall << "  Synthesis: " << syn << "  Inter-molecular Ineffective Collision: " << inter << "\n\n";

            size = pop_size;
            KE = KE - KELossRate;
        }

        int count = 0;
        this->struc.getEnergy(s, target);
        int val, targetvalue = this->struc.getEnergyValue();

        int sum = 0;

        for (int l = (size - pop_size); l < size; l++)
        {
            for (int m = l + 1; m < size; m++)
            {
                sum += this->struc.hammingDistance(s, population[l], population[m]);
            }
            this->struc.getEnergy(s, population[l]);
            val = struc.getEnergyValue();
            if (val == targetvalue)
            {
                count++;
            }

        }

        div = sum;
        speed = repairCount;

        std::cout << "Hightest attempted " << count << " times... out of " << pop_size << "   div loops diff = " << sum << "  repair call  " << repairCount << "\n\n";

        this->struc.getEnergy(sequence, maxStruc);

        std::vector<std::vector<int> > coor = getCoordinates(sequence, maxStruc);

        for (int j = 0; j < length; j++)
        {
            std::cout << maxStruc[j] << " ";
        }
        std::cout << "\n";

        for (int j = 0; j < length; j++)
        {
            std::cout << sequence[j] << " ";
        }
        std::cout << "\n last   " << energyValue << "\n";

        maxE = energyValue;

        for (int j = 0; j < length; j++)
        {
            int match = 0;
            for (int k = 0; k < j; k++)
            {
                if (coor[j][0] == coor[k][0] && coor[j][1] == coor[k][1] && coor[j][2] == coor[k][2])
                {
                    std::cout << j << " =   " << coor[j][0] << " " << coor[j][1] << " " << coor[j][2] << "    match with  " << k << "\n";
                    match = 1;
                }
            }
            if (match == 0)
            {
                std::cout << j << " =      " << coor[j][0] << " " << coor[j][1] << " " << coor[j][2] << "\n";
            }
        }

        std::cout << "\n" << loopcount << "\n\n";
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return maxE;
}

std::vector<std::vector<std::string> > Operators::search_space_creation(std::string s, int pop_size, std::vector<std::string> target)
{
    std::string seq = "";
    char ch, ch1 = 0;
    int seq_len = 0;

    for (int i = 0; i < s.length(); i++)
    {
        ch = s[i];

        if (48 <= ch && ch <= 57)
        {
            for (int j = 1; j < (ch - 48); j++)
            {
                seq = seq + ch1;
                seq_len++;
            }

        }
        else {
            seq = seq + ch;
            seq_len++;
        }
        ch1 = ch;
    }

    this->length = seq_len;
    this->sequence = seq;

    std::vector<std::vector<std::string> > structures(pop_size * 4, std::vector<std::string>(seq_len, ""));
    std::vector<std::string> direc(seq_len);

    std::vector<std::string> direc_name({ "L", "R", "U", "D", "F", "B" });

    int direction;
    Structure st;

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 5); // Use 5, there are indexes until 5
    for (int i = 0; i < pop_size * 4; i++)
    {
        //std::cout << i << "\n";
        for (int j = 0; j < seq_len; j++)
        {
            direction = dist(mt);
            direc[j] = direc_name[direction];
        }

        std::copy_n(direc.begin(), seq_len, structures[i].begin());

        int match = 0;
        int k;
        for (k = 0; k < i; k++)
        {
            match = 0;
            for (int l = 0; l < seq_len; l++)
            {
                if (structures[k][l] == structures[i][l])
                {
                    match++;
                }
                if (match == seq_len)
                {
                    break;
                }
            }
        }

        if (match == seq_len)
        {
            i--;
        }
        else
        {
            structures[i] = this->struc.repairAndEvaluate(s, structures[i]);
            repairCount++;
        }
    }

    int closest;
    int distance = 0;
    std::vector<std::string> tempSec;

    for (int i = 1; i < pop_size * 4; i++)
    {
        closest = st.hammingDistance(s, structures[i], target);

        for (int j = i; j < pop_size * 4; j++)
        {
            distance = st.hammingDistance(s, structures[j], target);

            if (distance < closest)
            {
                tempSec = structures[j];
                structures[j] = structures[i];
                structures[i] = tempSec;
                closest = distance;
            }
        }
    }
    return structures;
}

void Operators::print(std::vector<std::string> direc)
{
    std::vector<std::vector<int> > coor = getCoordinates(sequence, direc);

    for (int j = 0; j < length; j++)
    {
        int match = 0;
        for (int k = 0; k < j; k++)
        {
            if (coor[j][0] == coor[k][0] && coor[j][1] == coor[k][1] && coor[j][2] == coor[k][2])
            {
                std::cout << j << " =      " << direc[j] << "      " << coor[j][0] << " " << coor[j][1] << " " << coor[j][2] << "     match with  " << k;
                match = 1;
            }
        }
        if (match == 0)
        {
            std::cout << j << " =        " << direc[j] << "       " << coor[j][0] << " " << coor[j][1] << " " << coor[j][2] << " ";
        }
    }
}

bool Operators::stoppingConditionMet(int max)
{
    Structure st;
    std::vector<int> energy = st.getEnergy(sequence, target);
    int e = st.getEnergyValue();
    if (max == e)
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::vector<std::vector<int> >  Operators::getCoordinates(std::string s, std::vector<std::string> u)
{
    int len = s.length();
    std::vector<std::vector<int> > direc_coordinate(len, std::vector<int>(3));
    int x = 135, y = 135, z = 135;
    std::string d;

    int i = 0;

    for (i = 1; i < len; i++)
    {
        d = u[i];

        if (d == "L") {
            x = x - 1;
        }
        if (d == "R") {
            x = x + 1;
        }
        if (d == "U") {
            y = y + 1;
        }
        if (d == "D") {
            y = y - 1;
        }
        if (d == "F") {
            z = z + 1;
        }
        if (d == "B") {
            z = z - 1;
        }

        direc_coordinate[i][0] = x;
        direc_coordinate[i][1] = y;
        direc_coordinate[i][2] = z;
    }

    direc_coordinate[0][0] = 135;
    direc_coordinate[0][1] = 135;
    direc_coordinate[0][2] = 135;

    return direc_coordinate;
}

std::vector<std::vector<int> > Operators::getCoordinates(std::string s, std::vector<std::string> u, int len)
{
    std::vector<std::vector<int> > direc_coordinate(len, std::vector<int>(3));;
    int x = 135, y = 135, z = 135;
    char* d;

    int i = 0;
    if (len != 1)
    {
        for (i = 1; i < len; i++)
        {
            d = &u[i][0]; // simple and effective way to get character
            switch (d[0])
            {
            case 'L':
                x = x - 1;
                break;
            case 'R':
                x = x + 1;
                break;

            case 'U':
                y = y + 1;
                break;
            case 'D':
                y = y - 1;
                break;
            case 'F':
                z = z + 1;
                break;
            case 'B':
                z = z - 1;
                break;
            }
            direc_coordinate[i][0] = x;
            direc_coordinate[i][1] = y;
            direc_coordinate[i][2] = z;
        }
    }

    direc_coordinate[0][0] = 135;
    direc_coordinate[0][1] = 135;
    direc_coordinate[0][2] = 135;

    return direc_coordinate;
}
