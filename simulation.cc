/*
 * --------------IMS-----------------
 *
 * Project:  Implementace diskr. simulátoru zalo¾eného na øízení UDÁLOSTMI (opak procesnì orientovaného pøístupu)
 * File:     simulation.cc
 * Author:   Jaroslav Sendler, xsendl00, xsendl00@stud.fit.vutr.cz
 *           Du¹an Kovaèiè, xkovac21, xkovac21@stud.fit.vutbr.cz
 *
 * Encoding: ISO-8859-2
 *
 * Description:
 */

#include "simulation.h"


/**
 * Inicializace simulace
 */
void Simulation::initSim() {
   startSim = 0;
   endSim = 0;
   prioritySim = 0;
   time = 0;
}


/**
 * Construktor simulace
 *
 * @param start
 * @param end
 * @param priority
 */
Simulation::Simulation(double start, double end, int priority) {
  startSim = start;
  endSim = end;
  prioritySim = priority;
  time = start;
}


/**
 * Nastaveni simulace
 *
 * @param start
 * @param end
 * @param priority
 */
void Simulation::setSim(double start, double end, int priority) {
  startSim = start;
  endSim = end;
  prioritySim = priority;
  time = start;

}


/**
 * Nastaveni casu kdy zacne simulace
 *
 * @param start
 */
void Simulation::setSimStart(double start) {
  startSim = start;
  time = start;
}


/**
 * Nastaveni casu konce simulace
 *
 * @param end
 */
void Simulation::setSimEnd(double end) {
  endSim = end;
}


/**
 * Nastaveni priority simulace
 *
 * @priority
 */
void Simulation::setSimPriority(int priority) {
  prioritySim = priority;
}


/**
 * Vytiskne obsah promennych simulace
 */
void Simulation::getSim() {
    cout<< "startSim:" << startSim<< " endSim:"<< endSim<<" time:"<<time<<" prioritySim:"<<prioritySim <<endl;
}


/**
 * Vrati prioritu simulace
 *
 * @return prioritySim
 */
int Simulation::getSimPriority() {
  return prioritySim;
}


/**
 * Vrati cas, kdy zacne simulace
 *
 * @return startSim
 */
double Simulation::getSimStart() {
  return startSim;
}


/**
 * Vrati cas konce simulace
 *
 * @return endSim
 */
double Simulation::getSimEnd() {
  return endSim;
}


/**
 * Vrati aktualni cas vsech simulaci
 *
 * @return time
 */
double Simulation::getSimTime() {
  return time;
}
