/*
 * --------------IMS-----------------
 *
 * Project:  Implementace diskr. simulátoru zalo¾eného na øízení UDÁLOSTMI (opak procesnì orientovaného pøístupu)
 * File:     simulation.h
 * Author:   Jaroslav Sendler, xsendl00, xsendl00@stud.fit.vutr.cz
 *           Du¹an Kovaèiè, xkovac21, xkovac21@stud.fit.vutbr.cz
 *
 * Encoding: ISO-8859-2
 *
 * Description:
 */


#include <iostream>
#ifndef _SIMULATION_H
#define	_SIMULATION_H
 using namespace std;
class Simulation {

public:
    double time;
    double startSim;
    double endSim;
    int prioritySim;
    Simulation* contiguous;
    Simulation* previous;

private:
    void initSim();

public:
    Simulation() {
        initSim();
    }
    Simulation(double start, double end, int priority);
    void setSim(double start, double end, int priority);    // nastavi celou simulaci
    void setSimStart(double start);                         // nastavi pocatecni cas
    void setSimEnd(double end);                             // nastavi koncovy cas
    void setSimPriority(int priority);                      // nastavi prioritu
    void getSim();                                          // vrati vsechny udaje o simulaci
    int getSimPriority();                                   // vrati prioritu
    double getSimStart();                                   // vrati simulacni pocatecni cas
    double getSimEnd();                                     // vrati konec simulace
    double getSimTime();                                    // vrati aktualni cas simulace
};

#endif	/* _SIMULATION_H */

