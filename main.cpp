#include <iostream>
#include "sim.h"
//#include <stdio.h>

//using namespace std;

int main(int argc, char *argv[])
{
   sCalendar abcd;
   sSimulation sim;
   sEvent event;
   event.time = 100;
   event.priority = 1;

   abcd.dbInsertEvent(new sEvent(event));
   abcd.dbInsertEvent(new sEvent(event));
   event.name = "pes";
   abcd.dbInsertEvent(new sEvent(event));
   event.name= "kocka";
   abcd.dbInsertEvent(new sEvent(event));
   abcd.dbShow();

   sFascility a;
   sStorage b(5);
   sQueue q;
   sEvent e;

   q.push(e);
   cout<<a.free<<endl;
   cout<<b.isEmpty()<<endl;
    
   getchar();

   return 1;//EXIT_SUCCESS;
}
