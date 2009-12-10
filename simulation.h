/* 
 * File:   simulation.h
 * Author: portilo
 *
 * Created on December 10, 2009, 12:11 AM
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
    void setSim(double start, double end, int priority);
    void setSimStart(double start);
    void setSimEnd(double end);
    void setSimPriority(int priority);
    void getSim();
    int getSimPriority();
    double getSimStart();
    double getSimEnd();
    double getSimTime();
};

#endif	/* _SIMULATION_H */

