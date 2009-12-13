/*
 * --------------IMS-----------------
 *
 * Project:  Implementace diskr. simulátoru zalo¾eného na øízení UDÁLOSTMI (opak procesnì orientovaného pøístupu)
 * File:     main.cpp
 * Author:   Jaroslav Sendler, xsendl00, xsendl00@stud.fit.vutr.cz
 *           Du¹an Kovaèiè, xkovac21, xkovac21@stud.fit.vutbr.cz
 *
 * Encoding: ISO-8859-2
 *
 * Description:
 */



#include <iostream>
#include "sim.h"
#include <stdio.h>
#include "sgen.h"

using namespace std;

int main(int argc, char *argv[])
{
    sFascility a;
    sStorage b(5);
    sQueue q;
    sEvent e;
    sSimulation sim("ahoj");
    double time = 0;
    sStats stats;
    q.push(e,time);
    cout<<a.free<<endl;
    cout<<b.isEmpty()<<endl;
    
    stats.print();
    getchar();

    return EXIT_SUCCESS;
}
