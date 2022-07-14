//
//  main.cpp
//  CRO_Algorithm
//
//  Created by Domen Osojnik on 10/07/2021.
//

#include <iostream>
#include "Operators.h"
#include "Structure.h"
#include <chrono>
#include <ctime>  
#include <fstream>

using namespace std::chrono;

int main(int argc, const char* argv[]) {
    long long startTime = duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()
        ).count();

    int pop_size = 500;
    double moleCol = 0.4;
    double initialKE = 100;
    double KELossRate = 1;

    std::vector<std::vector<std::string> > file{ {"HPHHPPHHHHPHHHPPHHPPHPHHHPHPHHPPHHPPPHPPPPPPPPHH","FRUUULDDFDRUULUFDRRDLDLULDBLBRBUFFLFURUFFLBBBRDB"}
    ,{"HHHHPHHPHHHHHPPHPPHHPPHPPPPPPHPPHPPPHPPHHPPHHHPH","FRUBBDLUFDRDBBLFDFUFDRURUUFLLBULDFDDBLURBLDRBUUF"}
    ,{"PHPHHPHHHHHHPPHPHPPHPHHPHPHPPPHPPHHPPHHPPHPHPPHP","FRURFLDRBDFDDLUBULFRFRRDBBLBURFRFLURBLUUFDFDFLBU"}
    ,{"PHPHHPPHPHHHPPHHPHHPPPHHHHHPPHPHHPHPHPPPPHPPHPHP","FRURFUFDRBBBULDDDFRDBUUFLFDDFURBUFLLBLFDRBDBUBUB"}
    ,{"PPHPPPHPHHHHPPHHHHPHHPHHHPPHPHPHPPHPPPPPPHHPHHPH","FRUBULFURDRUUFDDLULDFURDRFUBRDDLFLBLDRBLURRRUBDL"}
    ,{"HHHPPPHHPHPHHPHHPHHPHPPPPPPPHPHPPHPPPHPPHHHHHHPH","FRRULBDLLDFRBBRDLFFLBLBRDRRFURBRULBULFURDFDLFRDL"}
    ,{"PHPPPPHPHHHPHPHHHHPHHPHHPPPHPHPPPHHHPPHHPPHHPPPH","FRULBDRURDRRFDLULFUBRFDRRUBLBLBDDFLLLFRFFRBBDRFU"}
    ,{"PHHPHHHPHHHHPPHHHPPPPPPHPHHPPHHPHPPPHHPHPHPHHPPP","FRRBDLDDFURFFUBLUFFUBRDBRDDFDBLLULUBRRRDBLDFRBDD"}
    ,{"PHPHPPPPHPHPHPPHPHHHHHHPPHHHPHPPHPHHPPHPHHHPPPPH","FRURUUBDDLDBRBDFLFRURDFRULUBBDRDLDFLDFULURUFRDDB"}
    ,{"PHHPPPPPPHHPPPHHHPHPPHPHHPPHPPHPPHHPPHHHHHHHPPHH","FRRDRBBLFULLBURDRRFRULBLUBLFUFDLDRFLURRDBURFFDBD"}
            ,{"PPHHHHHPPPHHPPPPPHHPPPHPPPPPPHPHPPPHPPHPPHPPPPPHPPPPHHPHHPPHPPHP","FRRFRDLDFRUUFDDLUBUFURBUFUBLDDBRUBDDBDFDLUBDRRFUBBUFFFUFDFDBDBUR"}
            ,{"PPHPHPPHPPHHHPHHHHPPHHHPPPPHPHPPPHPHPPPHPHPPPPPHPHPPHPHPPPHPPHPP","FFLUBRBLBDFFDDLUUUUBDDDBDLUFDFDRBURURFFLDLLLUUBRFRFDBLBLBURBUFFF"}
            ,{"HPHHPPHHPHPPPPPHHHPHHHHPPHPPHPHHPPPHPHPPHHHPHHPHPPPPPHHHHHHHHPPP","FRULBUFURDBDDLLFFRRULLULBRBDFLFDDFRULUFRBRDRUUULULUBDDRRDLFLULFD"}
            ,{"HPPHHPPHPPHPHPPHPPPPHPPPPPPHPHPHHHPPHPHPPPHPHPPHHPPHPPHPPHPHHHPH","FFLBUFLBLDRDRFRBDRBLURFUFULBRBDLLDDBULFLUURBRUFDRUBDBRFRDLDLULLF"}
            ,{"HPPPHHPPHPHPPPHPPPHPHHPPPHHPHPHHPHPPHPPPHPPHPHHHPPHPPHPPHHHPHHHH","FFLDBRFDBDBDDRURRULFUUFDLBUUBRDDBLBUFRULLUFDLDRBBLFLDRDFURBDRFUU"}
            ,{"HPPHHPHHHHPPPPPPHHPPHPPPPHHPPPHPPHPHHPHPPPPHHPPPPHPPPPPHPPPPHPHH","FRULBDLFUBBBDFLUFDDFULBUFRUUFDDFRBUBRFDFRBDLLFDLUBLUUBBRUUBDDRFR"}
            ,{"PPPPHPPPHPPPHHHHPHHPPPPPHPPHPHHPHPHPPPPPHPPPPPPPPPPHHHHPPPPHHPPH","FRRURBUFRFLDRBRFUBRUUBLDDBDFRFDFURBRDLBLLDDFDFUFLUUBRBLDBBUFUBUF"}
            ,{"PPPHHHPPHPHPPHPPHHPPPHPPHPPHHPHPPPHPPPPPPPHPHHHPHHHHHPPHHPPPHPPH","FBUUUUULDBRBRFUFDDRUFLULDFDBRDLDRBURBUBLLDFRULLLFRDFLFUBRFULBURD"}
            ,{"HPPHPPHHHPPPPHPHPPPHPHHPHHHHHPPPPHPHPHPPPPHPHPPPHHPHPPPPHPPHHPHP","FFLBUBDBDBDRUFDLDLFULUBDRUFRFFDRUBDLLUFLDBUURUBBDFLBBRRRFUFDDDLD"}
            ,{"PPHPPHPPHHHPPPHPHPPHPPHPPPPPPHPPHHHPPHPPHPPHPHPPPPPPHHHPPPPPHPHP","FRULBRDRUULUBRDLDDRUBRFDRDLFUURFLLFFRBRULFLBLBUFFRRBBDLUBURDDRFR"}
                    ,{"HPHPPHHPHPPHPHHPPHPH","FFLUBDLFDDRURBLDLULU"}
                    ,{"HHPPHPPHPPHPPHPPHPPHPPHH","FFLURUBDBRFRULUFDRDLFDBB"}
                    ,{"PPHPPHHPPPPHHPPPPHHPPPPHH","FFLUBDLLFFRBUFRDDBBRBLLFF"}
                    ,{"PPPHHPPHHPPPPPHHHHHHHPPHHPPPPHHPPHPP","FFFLUFLBDDLUUURUBRFDBBLFDBBDFFRBUFRB"}
                    ,{"PPHPPHHPPHHPPPPPHHHHHHHHHHPPPPPPHHPPHHPPHPPHHHHH","FFLFLBLFUBRRRBBLFDLUBLFDDFFLBUBBRDDRUFDFUFRBBBUL"}
                    ,{"HHPHPHPHPHHHHPHPPPHPPPHPPPPHPPPHPPPHPHHHHPHPHPHPHH","FFLBLBURBDFRRBLURFLULFDLFRRBRFDBRDBLBLFLBLFFRFRRBL"}
                    ,{"PPHHHPHHHHHHHHPPPHHHHHHHHHHPHPPPHHHHHHHHHHHHPPPPHHHHHHPHHPHP","FFLBBULFRFLFRDRDBLBBDFLBLFFFUFRUBLUBBDBRDLFFLFUBRRBDFFDBRFUF"}
                    ,{"HHHHHHHHHHHHPHPHPPHHPPHHPPHPPHHPPHHPPHPPHHPPHHPPHPHPHHHHHHHHHHHH","FFFFLBUFRBBBUFULULDDLBRUURDBDFDBDFLBUFLFRFLFRUFRBRBULFLBDRBDDLFF"}
                            ,{"PPHHHPHHHPPPHPHHPHHPPHPHHHHPHPPHHHHHPHPHHPPHHP","FRUULURRDFRUBDBUBDDDFUFLBUUBDBDFLFUBUFLDDLBRUB"}
                            ,{"PHPHHHPHHHPPHHPHPHHPHHHPHPHPHHPPHHHPPHPHPPPPHPPHPPHHPPHPPH","FRURDDDLULLDRFFRRUBDLUFLBURURRRDLLFFLBURFUBRDRDLFDBBRBLBUF"}
                            ,{"PPHHPPPPPHHPPHHPHPPHPPPPPPPHPPPHHPHHPPPPPPHPPHPHPPHPPPPPHHHPPPPHHPHHPPPPPHHPPPPHHHHPHPPPPPPPPHHHHHPPHPP","FFFLBLUUFRDBRFRULUFDRUBRDDDLBDLFLLUULUFFRDRFDBLBDFRDRBBRUFURFUBLFULLFRRDDBLFFUBBBLULDLFDBDDRRUURDFFRBDB"}
                            ,{"HPPPPPHPPPPHPHHPHHPPPPHPHHHPPPPHPHPHHHHPPPPPPPPPPPHPPHPPPHPHHPPPHHPPHPPHPHPHPPPPPPPPHPPPHHHHHHPPPHHPPHHHPPPHHPHHHHHPPPPPPPPPHPPPPHPHPPPP","FFLLBBRULBRDLDDDRRDLFRUFUURFLDLBLBDRURRRDFUURBBLDDLDBURUULULDBRDFLBDFDLULUURBLDLFUURRURFDDDRUUUFFDBRDLLUUFLDDLBRBDBBDLDFFFFURDRRBUFUFDLL"}
    };
    Operators op;
    std::cout << "Title: Protein Structure Prediction using Chemical Reaction Optimization in HP Cubic Lattice model\n\n";

    std::string input;
    std::vector<std::string> dataSet{ "S1.1","S1.2","S1.3","S1.4","S1.5","S1.6","S1.7","S1.8","S1.9","S1.10","S2.1","S2.2","S2.3","S2.4","S2.5","S2.6","S2.7","S2.8","S2.9","S2.10","S3.1","S3.2","S3.3","S3.4","S3.5","S3.6","S3.7","S3.8","S4.1","S4.2","S4.3","S4.4" };
    std::ofstream myfile;
    std::string fileName = "results";
    for (int in = 0; in < 32; in++)
    {
        fileName = "results" + std::to_string(in) + ".txt";
        Structure struc;

        double div = 0, speed = 0;

        int NSR = 0;
        const int NR = 1;
        std::string target;

        double energy[NR]; // Vector of size NR
        {
            
            myfile.open(fileName, std::ios_base::app);
            NSR = 0;
            input = file[in][0];
            target = file[in][1];

            std::vector<std::string> targetArray(target.length());

            for (int i = 0; i < target.length(); i++)
            {
                targetArray[i] = target.at(i);
            }

            op.target = targetArray;

            struc.getEnergy(input, targetArray);
            int targetValue = struc.getEnergyValue();

            double ie = initialKE;
            double ke = KELossRate;
            int eBest = 0, eMean = 0, eSum = 0;
            long long tempTime, tempTime1 = startTime;

            for (int i = 0; i < NR; i++)
            {
                myfile << "#" << dataSet[in] << " :  " << "( Run = " << (i + 1) << ")\n";
                op = Operators();

                initialKE = ie;
                KELossRate = ke;
                op.target = targetArray;

                energy[i] = op.CRO_PSP(pop_size, input, moleCol, initialKE, KELossRate);
                tempTime = duration_cast<milliseconds>(
                    system_clock::now().time_since_epoch()
                    ).count();
                tempTime1 = tempTime - tempTime1;

                myfile << "Time taken = " << (tempTime1 / 1000) << "\n";

                tempTime1 = tempTime;

                if (energy[i] == targetValue)
                {
                    NSR++;
                }

                if (energy[i] > eBest)
                {
                    eBest = (int)energy[i];
                }

                eSum += energy[i];
                div += op.div;
                speed += op.speed;
                myfile << "------------------------------------------------------------------------\n";
            }
            eMean = eSum / NR;
            eSum = 0;

            double eStd = 0;

            for (int i = 0; i < NR; i++)
            {
                eSum += pow(abs(eMean - energy[i]), 2);
            }

            eStd = sqrt(eStd / NR);

            long long endTime = duration_cast<milliseconds>(
                system_clock::now().time_since_epoch()
                ).count();

            long long executionTime = (endTime - startTime) / 1000;
            div = (2 * div) / (NR * (pop_size - 1) * pop_size);
            double pSpeed = speed / executionTime;
            std::cout << "\nSET COMPLETE, WRITING TO FILE.....\n";

            myfile << "Total execution time: " << executionTime << "\n";
            myfile << "---------------------- " << dataSet[in] << " ------------------------\n";

            myfile << "Ebest = " << eBest << "      Emean = " << eMean << "      Std = " << eStd << "\n";
            myfile << "div = " << div << "    speed = " << pSpeed << "     SR =  " << (NSR / NR) << "\n";

            myfile << "-------------------------------*******************----------------------------------\n";
            myfile << "-------------------------------*******************----------------------------------\n\n\n";

            myfile.close();
        }
    }

    return 0;
}
