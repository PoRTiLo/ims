//#define NDEBUG
#include <assert.h>

#include "dblist.h"

using namespace std;

int main() {

   int pom  = 10;
   
   //assert(pom < 4);



   DBList dblist;
   //dblist.dbDelete();
   Simulation* sim = new Simulation(1.1, 2.1, 3);
   dblist.dbInsertSimF(sim);

   Simulation* sim1 = new Simulation();
   sim1->setSim(1.2,2.2,4);
   dblist.dbInsertSimF(sim1);

   Simulation* sim2 = new Simulation();
   sim2->setSim(1.3,2.3,5);
   dblist.dbInsertSimF(sim2);
   //dblist.dbShow();
   cout<<"-------------------"<<endl;

   Simulation* sim3 = new Simulation(9.2,5.3,23);
   dblist.dbInsertSimByTime(sim3);
   dblist.dbShow();
   cout<<dblist.dbGetCount()<<endl;

   dblist.dbSortByTime();
   dblist.dbDelete();
   cout<<"////////////"<<endl;
   dblist.dbShow();
   //cin.get();
   return 0;
}
