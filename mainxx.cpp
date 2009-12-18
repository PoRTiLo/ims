#include <iostream>
#include "sim.h"
#include <stdio.h>
#include <math.h>
#include <sstream>

using namespace std;

enum codes
{
     PRISIEL_ZAKAZNIK,
     PROHLIZENI_KNIZEK,
     ODBAVOVANI_PULT,
     PRISEL_DODAVATEL,
     ODESEL_DODAVATEL
};
     


class mySim : public sSimulation
{
      public:
      mySim();
      
      sStorage pult;
        
      //vytvori event prohlizeni knizek
      sEvent prohlizeni_knizek;
      
      //vytvori event odbavovani u pultu s prioritou 1
      sEvent odbavovani_pult_1;
      
      //vytvori event odbavovani u pultu s prioritou 2
      sEvent odbavovani_pult_2;
      
      //vytvori event dodavatel
      sEvent dodavatel;

      void behaviour(sEvent event);
      void PrisielZakaznik();
      void ProhlizeniKnizek();
      void OdbavovaniPult();
      void PriselDodavatel();
      void OdeselDodavatel();
     
};



mySim::mySim()
{   
    prohlizeni_knizek.setName("Prohlizeni knizek");
    prohlizeni_knizek.type = PROHLIZENI_KNIZEK;
    
    odbavovani_pult_1.setName("Odbavovani u prazdneho pultu ");
    odbavovani_pult_1.priority = 1;
    odbavovani_pult_1.type = ODBAVOVANI_PULT;
    
    odbavovani_pult_2.setName("Odbavovani u pultu s frontou");    
    odbavovani_pult_2.priority = 2;
    odbavovani_pult_2.type = ODBAVOVANI_PULT;

    dodavatel.setName("Dodavatel");    
    dodavatel.priority = 3;
    dodavatel.type = PRISEL_DODAVATEL;
    
    pult.setName("pult");          
    pult.setCapacity(2);           
}

void mySim::PrisielZakaznik()
{
     odbavovani_pult_1.time = currentTime + gen.expGen(5);
     prohlizeni_knizek.time = currentTime + gen.expGen(15);
     int a = gen.randomGen(10);
          if (a >= 6)                 //vraceni knizky
          {
               if (!pult.isEmpty())   //ak je aspon jeden pult volny
               {
                                      
                    pult.take(odbavovani_pult_1);
                    calendar.dbInsertEvent(odbavovani_pult_1);
                   // cout<<"pult take"<<endl;
               }
               else
               {
                    int c = gen.randomGen(10);
                    if (c >= 2)        //zakaznik sa postavi do fronty       
                    {
                          pult.take(odbavovani_pult_2);
                          calendar.dbInsertEvent(odbavovani_pult_2);
                   // cout<<"fronta pult"<<endl;
                    }
                    else
                    {
                       // cout<<"opustam"<<endl;
                                      //zakaznik opusta kniznicu
                    }                              
               }
          }
          else                        //pujceni knizky 
          {
              // cout<<"insertCalendar,prohlizeni"<<endl;                       
               calendar.dbInsertEvent(prohlizeni_knizek);       
          } 
}

void mySim::ProhlizeniKnizek()
{
          odbavovani_pult_2.time = currentTime + gen.expGen(5);                   
          int b = gen.randomGen(10);
          if (b >= 3)
          {    
               //cout<<"prohlizeni pult take"<<endl;
               pult.take(odbavovani_pult_2);
               calendar.dbInsertEvent(odbavovani_pult_2);
          }
          else
          {                           
               //cout<<"out"<<endl; // pozadavka opousti system
          }
}
 
void mySim::OdbavovaniPult()
{
     pult.bringBack(currentTime);
}

void mySim::PriselDodavatel()
{
     dodavatel.time = currentTime + gen.expGen(5);
     pult.take(dodavatel);
     calendar.dbInsertEvent(dodavatel);
}

void mySim::OdeselDodavatel()
{
     pult.bringBack(currentTime);
}

void mySim::behaviour(sEvent event)
{   

    switch(event.type)
    {
    case PRISIEL_ZAKAZNIK: PrisielZakaznik();      //prisel zakaznik          
    break;
    case PROHLIZENI_KNIZEK: ProhlizeniKnizek();   //prohlizeni knizek cakanie uplynulo
    break;
    case ODBAVOVANI_PULT: OdbavovaniPult();       //pult sa uvolni  //pozadavka opousti system  
    break;
    case PRISEL_DODAVATEL: PriselDodavatel();     //prisel dodavatel
    break;
    case ODESEL_DODAVATEL: OdeselDodavatel();     //odesel dodavatel    
    break;
    default:
    break;
    }
}


int main(int argc, char *argv[])
{     
    int i = 0;
    sEvent zakaznik;
    mySim sim;
    sim.setName("kniznica"); 
    sEvent ex; 
    sim.start(200);                                      //spustime simulaciu
    double time = sim.startTime;
    while((time+= sim.gen.expGen(15)) <= sim.finishTime)                        //vygenerujem udalosti - PRISIEL_ZAKAZNIK
    {

       zakaznik.type = PRISIEL_ZAKAZNIK;
       stringstream ss;
       ss << i;
       zakaznik.name = "zakaznik " + ss.str();
       zakaznik.time = time;
       zakaznik.type = 0;
       sim.calendar.dbInsertEvent(zakaznik);
       i++;                            
    }
    cout<<i<<endl;
    time = 0;
    while((time+= sim.gen.expGen(100)) <= sim.finishTime)
    {
                  
    }
    i = 0;
    getchar();
    sEvent currentEvent;
    while (!sim.calendar.dbIsEmpty())
    {
          currentEvent = sim.calendar.dbGetNextEvent();
          sim.behaviour(currentEvent);
          sim.currentTime = currentEvent.time;
          i++;
          
          
    }
    cout<<i<<endl;
    getchar();
    return EXIT_SUCCESS;
}
