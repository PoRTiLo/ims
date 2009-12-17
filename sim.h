/*
 * --------------IMS-----------------
 *
 * Project:  Implementace diskr. simulátoru zalo¾eného na øízení UDÁLOSTMI (opak procesnì orientovaného pøístupu)
 * File:     sim.h
 * Author:   Jaroslav Sendler, xsendl00, xsendl00@stud.fit.vutr.cz
 *           Du¹an Kovaèiè, xkovac21, xkovac21@stud.fit.vutbr.cz
 *
 * Encoding: ISO-8859-2
 *
 * Description:
 */

#include <fstream>
#include <queue>
#include <deque>
#include <string>
#include "sgen.h"

using namespace std;

/************************** event ****************************************/
class sEvent                                                //trieda sEvent
{     
      public:
             sEvent();                                      //konstruktor, meno defaultne, priorita zakladna,cas nulovy
             sEvent(string start);                          //konstruktor, meno start, priorita zakladna, cas nulovy             
             sEvent(string start, double now);              //konstruktor, meno start, priorita zakladna, cas now
             sEvent(string start, double now, int prio);    //konstruktor, meno start, priorita prio, cas now
             ~sEvent();                                     //destruktor
             
             void setName(string id);
             
             string name;                                   //meno
             double time;                                   //cas udalosti
             int priority;                                  //prioriorita
             int type;

};
/************************** queue *****************************************/
class sQueue                                                //trieda sQueue
{
      public:
             sQueue();                                      //konstruktor, meno defaultne
             sQueue(string id);                             //konstruktor, meno id
             ~sQueue();                                     //destruktor
             
             string name;                                   //meno
             
             void push(sEvent event);                       //vloz event do fronty
             void pop();                         //vyber event z fronty
             sEvent front();                                //vrati prvy prvok fronty
             sEvent back();                                 //vrati posledny prvok fronty
             bool isEmpty();                                //zisti ci je fronta prazdna
             void setName(string id);
             int size();                                    //zisti velkost
             int getTotalNum();                             //zisti pocet ludi co presli frontou
             double getTimeUsed();                          //zisti cas po ktory bola fornta pouzivana
             double getTimeStart();
             double getAvarageLength();                        //zisti priemernu dlzku fornty
             
      private:
             double curNum;                                 //pomocna premmenan pre priemernu dlzku
             int counter;                                   //pocitadlo pristupov
             bool first;                                    //rozlisuje prvy pristup pre detekovanie zaciatku pouzivania
             double start;                                  //zaciatocny cas pouzivania
             double timeUsed;                               //cas po ktory bola fronta pouzivana
             deque<sEvent> queueEvents;                     //fronta
};
/******************************************* calendar unit ********************/
class sCalUnit {                                            //trieda sCalUnit - prvok kalendara udalosti
      public:
       
            sCalUnit(sEvent *event=0);                      //konstruktor
            ~sCalUnit(){};                                  //destruktor
 
            sCalUnit* contiguous;                           //pointer na dalsi prvok
            sCalUnit* previous;                             //pointer na predchadzajuci prvok
            sEvent* event;                                  //pointer na event

};

/****************************** calendar *************************************/
/**
 * Trida sCalendar je implementovana pomoci obousmerneho linearniho zretezeneho
 * seznameu s hlavickou.
 */
class sCalendar {                                           //trieda sCalendar

            sCalUnit *head;                                 //hlavicka
            int count;                                      //pocet prvku v seznamu

      private:
            void dbCopy(const sCalendar& t);
            void dbInit();                                  //inicializace kalendare

      public:
            sCalendar() { dbInit(); }                       //konstruktor kalendare
            sCalendar(const sCalendar& t);                  //vytvoreni kalendare
            ~sCalendar();                                   //destruktor kalendare
            void dbDelete(sEvent* event);                   //zruseni udalosti
            void dbDelete();                                //zruseni vsech udalosti
            int dbGetCount() const;                         //pocet udaloi v kalendari
            void dbInsertEvent(sEvent event);               //pridani udalosti do kalendare
            sCalUnit* dbSearch(sEvent* event) const;        //vrati pozice prvku pred ktery se ma vlozit
            sCalUnit* dbGetFirst() const;                   //vrati ukazatel na prvni prvek kalendare
            sEvent dbGetNextEvent();                        //vrati ukazatel na dalsi Udalost kalendare(prvni)
            void dbShow() const;                            //zobrazeni obsahu kalendare
            bool dbIsEmpty() const;                         //kontrola zda je kalendar przadny
};

class sFascility                                            //trieda sFascility
{
      public:
             sFascility();                                  //konstruktor, meno defaultne
             sFascility(string id);                         //konstruktor, meno id
             ~sFascility();                                 //destruktor
             
             string name;                                   //meno
             bool free;                                     //zariadenie je volne defaultne
             sEvent currentEvent;
             
             void setName(string id);             
             void seize(sEvent a);                          //zabere zariadenie
             void release();                     //opusti zariadenie
      private:
             sQueue fascQueue;                              //fronta pre udalosti ak je zariadenie obsadene
             sQueue removedQueue;                           //fronta vyhodenych eventov    
};

class sStorage                                              //trieda sStorage
{
      public:
             sStorage();                                    //konstruktor, meno default, kapacita 1
             sStorage(int capacity);                        //konstruktor, meno default, kapacita capacity
             sStorage(int capacity, string id);             //konstruktor, meno id, kapacita capacity
             ~sStorage();                                   //destruktor
             
             string name;                                   //meno
             
             void setCapacity(int capacity);
             void setName(string id);
             void take(sEvent event);                       //zobere polozku zo skladu - change
             void bringBack(double time);                   //vrati polozku do skladu
             int getStorageSize();                          //zisti velkost skladu
             int getStoregeLeft();                          //zisti pocet poloziek v sklade
             double getTimeUsed();                          //zisti dobu pouzivania skladu
             double getUsagePerUnit(int i);                 //zisti dobu pouzivania ked bolo v sklade prave i poloziek
             bool isEmpty();                                //zisti ci je sklad prazdny
             
             
      private:
             int left;                                      //zasoba v sklade         
             int full;                                      //maximalny obsah skladu         
             sQueue storQueue;                              //fronta pre udalosti ak je sklad prazdny
             double *currentTime;                           //pointer na pole s casmi pre vypocet getUsagePerUnit()
             double *takenByEvents;                         //pointer na pole s casmi pre vypocet getUsagePerUnit()
             double timeUsed;                               //zaciatok pouzivania skladu
             double timeTotal;                              //cas pouzivania skladu
             bool first;                                    //detekuje prvy zasah do skladu
};

class sSimulation                                           //trieda sSimulation
{
      public:
             sSimulation();                                 //konstruktor, meno defaultne
             sSimulation(string id);                        //konstruktor, meno id
             ~sSimulation();                                //destruktor
             
             string name;                                   //meno
             sGen gen;                                      //generator pseudonahodnych cisel
             sCalendar calendar;                            //kalendar udalosti       
             
             void setName(string id);
             void start(double length);                     //start simulacie, zaciatok v case 0, koniec v case length
             void start(double begin,double end);           //start simulacie, zaciatok v case begin, koniec v case end
             bool isRunning();                              //zisti ci simulacia bezi       
             
             double startTime;                              //start time       
             double finishTime;                             //finish time       
             double currentTime;                            //current time
      protected:
             bool running;                                  //zisti ci simulacia bezi
};

class sStats                                                //trieda sStats
{
      public:
             sStats();                                      //konstruktor, simulacia nedefinovana, musi sa definovat! 
             sStats(sSimulation* a);                        //konstruktor, simulacia a
             ~sStats();                                     //destruktor
             
             void registerSimulation(sSimulation*);         //zaregistruje simulaciu
             void registerObject(sStorage*);                //zaregistruje sklad pre vypis jeho statistik
             void registerObject(sFascility*);              //zaregistruje zariadenie pre vypis jeho statisti
             void registerObject(sQueue*);                  //zaregistruje frontu pre vypis jeho statisti
             void print();                                  //vytlaci statistiku
             void setOutputToFile(string name);             //presmeruje standartny vystup do suboru, na konci programu je nutne zavolat SerOutputDefault pre spravne uzavretie suboru
             void setOutputDefault();                       //presmeruje vystup na zakladny
      private:
             queue<sStorage*> sStatsQueuesStorage;          //fronta registrovanych skladov
             queue<sFascility*> sStatsQueuesFascility;      //fronta registrovanych zariadeni
             queue<sQueue*> sStatsQueuesQueue;              //fronta registrovanych front
             bool registered;                               //ci je zadana simulacia
             bool fopened;                                  //ci je otvoreny subor
             ofstream file;                                 //subor do ktroreho sa vypisuje
             streambuf* sbuf;                               //pomocna premenna pre vypis do suboru
             sSimulation* sim;                              //simulacia
};
