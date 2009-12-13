#include "simulation.h"



   void Simulation::initSim() {
      startSim = 0;
      endSim = 0;
      prioritySim = 0;
      time = 0;
   }


   Simulation::Simulation(double start, double end, int priority) {
     startSim = start;
     endSim = end;
     prioritySim = priority;
     time = start;
   }

   void Simulation::setSim(double start, double end, int priority) {
     startSim = start;
     endSim = end;
     prioritySim = priority;
     time = start;

   }
   void Simulation::setSimStart(double start) {
     startSim = start;
     time = start;
   }

   void Simulation::setSimEnd(double end) {
     endSim = end;
   }

   void Simulation::setSimPriority(int priority) {
     prioritySim = priority;
   }

   void Simulation::getSim() {
       cout<< "startSim:" << startSim<< " endSim:"<< endSim<<" time:"<<time<<" prioritySim:"<<prioritySim <<endl;
   }
   int Simulation::getSimPriority() {
     return prioritySim;
   }

   double Simulation::getSimStart() {
     return startSim;
   }

   double Simulation::getSimEnd() {
     return endSim;
   }

   double Simulation::getSimTime() {
     return time;
   }
