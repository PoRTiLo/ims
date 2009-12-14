/*
 * --------------IMS-----------------
 *
 * Project:  Implementace diskr. simulátoru zalo¾eného na øízení UDÁLOSTMI (opak procesnì orientovaného pøístupu)
 * File:     sim.cpp
 * Author:   Jaroslav Sendler, xsendl00, xsendl00@stud.fit.vutr.cz
 *           Du¹an Kovaèiè, xkovac21, xkovac21@stud.fit.vutbr.cz
 *
 * Encoding: ISO-8859-2
 *
 * Description:
 */



#include <iostream>
#include "sim.h"

using namespace std;
/********************* sFascility *********************/
sFascility::sFascility()    
{
     free = true;
     timeUsed = 0;
     takenByEvents = 0;
     name = "Default fascility";
}

sFascility::sFascility(string id)
{
     free = true;
     timeUsed = 0;
     takenByEvents = 0;
     name = id;
}

sFascility::~sFascility()   
{
}

void sFascility::sieze(sEvent a, double time)
{
     if (free == true)
     {
        free = false;
        takenByEvents = time;
     }
     else
         fascQueue.push(a);
     
}

void sFascility::release(double time)
{
     if (free == 0)
     {
        if (fascQueue.empty())
        {
           free = 1;         //zariadenie je volne defaultne 
           timeUsed += time - takenByEvents;                 
           return;
        }
        else
        {
           fascQueue.pop();
        }
     }
}
double sFascility::getTimeUsed()
{
      return timeUsed;
}   
/************************** sEvent ******************************/

sEvent::sEvent()
{
     name="Default event";
     time = 0;
     priority =0;
}

sEvent::sEvent(string start)
{
     name=start;
     time = 0;
     priority =0;
}

sEvent::sEvent(string start, double now)
{
     name=start;
     time = now;
     priority = 0;
}

sEvent::sEvent(string start, double now, int prio)
{
     name=start;
     time = now;
     priority = prio;
}


sEvent::~sEvent()
{
}       
/************************* sStorage ******************************/
sStorage::sStorage(int capacity, string id)
{      
     name = id;             
     first = true;    
     full = capacity;                
     left = capacity;
     timeUsed = 0;
     
     currentTime = (double*) operator new (sizeof(double)* full);
     takenByEvents = (double*) operator new (sizeof(double)* full);
     
     int i;
     for(i=0;i<capacity;i++)
     {
          takenByEvents[i] = 0;
          currentTime[i] = 0;
     }
}

sStorage::sStorage(int capacity)
{      
     name = "Default storage";             
     first = true;    
     full = capacity;                
     left = capacity;
     timeUsed = 0;
     timeTotal = 0;
     
     currentTime = (double*) operator new (sizeof(double)* full);
     takenByEvents = (double*) operator new (sizeof(double)* full);
     
     int i;
     for(i=0;i<capacity;i++)
     {
          takenByEvents[i] = 0;
          currentTime[i] = 0;
     }
}

sStorage::sStorage()
{
     name = "Default storage";
     first = true;
     full = 1;                
     left = 1;
     timeTotal = 0;
     
     takenByEvents = new double;
     currentTime = new double;
     
     timeUsed = 0;
     takenByEvents = 0;
     currentTime = 0;
}

sStorage::~sStorage()
{
     delete takenByEvents;
     delete currentTime;
}

void sStorage::take(sEvent a, double time)
{
     if(first == true)
     {
        timeUsed = time;
        first = false;
     }
     if ((time - timeUsed) > timeTotal)
        timeTotal = time - timeUsed;
        
     if (left>0)
        left--;
     else
         storQueue.push(a);
         
         
     currentTime[left] = time;
}

void sStorage::bringBack(double time)
{  
     timeTotal = timeUsed - time;
     takenByEvents[left] += time - currentTime[left]; 
     
     if (left == 0)
         storQueue.pop();
           
     else if (left<full)
         left++;
                         //else chyba ak bude treba
}

bool sStorage::isEmpty()
{
    if(left == 0)
         return true;
    else
         return false;
}
int sStorage::getStorageSize()
{
    return full;
}
 
int sStorage::getStoregeLeft()
{
    return left;
}

double sStorage::getTimeUsed()
{
    return timeTotal;
}

double sStorage::getUsagePerUnit(int i)
{
    if (i<full)
          return takenByEvents[i];
    else
          return -1;
} 
/********************* sSimulation *****************************/
sSimulation::sSimulation()
{
     name = "Default simulation";
     startTime = 0;
     finishTime = 0;
     currentTime = 0;
     running = false;
}
sSimulation::sSimulation(string id)
{
     name = id;
     startTime = 0;
     finishTime = 0;
     currentTime = 0;
     running = false;               
}
sSimulation::~sSimulation()
{
}

void sSimulation::start(double length)
{
     currentTime = 0;
     startTime = 0;
     finishTime = length;
     running = true;
}

void sSimulation::start(double begin,double end)
{
     startTime = begin;
     currentTime = begin;
     finishTime = end;
     running = true;
}
/******************** sQueue **********************************/
sQueue::sQueue()
{
      counter = 0;
      timeUsed = 0;
      first = true;
      name = "Default queue";
}
sQueue::sQueue(string id)
{
      counter = 0;
      timeUsed = 0;
      first = true;
      name = id;
}
sQueue::~sQueue()
{
}
void sQueue::push(sEvent event,double time)
{
     if(first)
     {
        start = time;
        first =  false;
     }
     queueEvents.push(event);
     counter++;
     if ((time - start) > timeUsed)
        timeUsed = time - start;
     curNum += size();
       
}
void sQueue::pop(double time)
{
     queueEvents.pop();
     timeUsed = time - start;
}
sEvent sQueue::front()
{
     return queueEvents.front();  
}
sEvent sQueue::back()
{
     return queueEvents.back(); 
}
bool sQueue::isEmpty()
{
     return queueEvents.empty();
}
int sQueue::size()
{
     return queueEvents.size();
}
int sQueue::getTotalNum()
{
     return counter;
}
double sQueue::getTimeUsed()
{
     return timeUsed;  
}
int sQueue::getAvarageLength()
{
    return int(curNum/counter);
}
/******************** sStats **********************************/
sStats::sStats()
{
     registered = false;
     fopened = false;
}
sStats::sStats(sSimulation a)
{
     sim = a;                   
     registered = true;
     fopened = false;
}
sStats::~sStats()
{
}

void sStats::registerObject(sStorage a)
{
     sStatsQueuesStorage.push(a);
}

void sStats::registerObject(sFascility a)
{
     sStatsQueuesFascility.push(a);
}

void sStats::registerObject(sQueue a)
{
     sStatsQueuesQueue.push(a);
}

void sStats::print()
{
     int i;
     float totalTime = sim.finishTime - sim.currentTime;
     if (!sStatsQueuesStorage.empty())
     {
           cout<<"***************** Storages statistics *****************"<<endl;
     }
     sStorage a;
     while (!sStatsQueuesStorage.empty() && registered == true)
     {
           a = sStatsQueuesStorage.front();
           double timeUsd = a.getTimeUsed();
           int size = a.getStorageSize();
           
           cout<<"Name: "<<a.name<<endl;
           cout<<"Content of storage with:"<<endl;
           for(i=0;i<size;i++)
           {
           cout<<(size-i)<<" units, was active "<<(a.getUsagePerUnit(i)/timeUsd)<<"% of time used, and "<<a.getUsagePerUnit(i)/totalTime<<"% of total time" <<endl;
           }
           sStatsQueuesStorage.pop();
           cout<<"Total time used: "<<a.getTimeUsed()<<" and it is "<<a.getTimeUsed()/totalTime<<"% of total time"<<endl;
           cout<<endl;
     }
     
     if (!sStatsQueuesFascility.empty())
     {
           cout<<"***************** Fascilities statistics *****************"<<endl;
     }
     sFascility b;
     while (!sStatsQueuesFascility.empty() && registered == true)
     {
           b = sStatsQueuesFascility.front();
           cout<<endl;
           cout<<"Name: "<<b.name<<"was taken "<<b.getTimeUsed()<<" time units and it is "<<(b.getTimeUsed()/totalTime)<<"% of total time"<<endl;
           sStatsQueuesFascility.pop();
     }
     
     if (!sStatsQueuesQueue.empty())
     {
           cout<<"***************** Queues statistics *****************"<<endl;
     }
     sQueue c;
     while (!sStatsQueuesQueue.empty() && registered == true)
     {
           c = sStatsQueuesQueue.front();
           cout<<endl;
           cout<<"Name: "<<c.name<<"was used "<<c.getTimeUsed()<<" time units and it is"<<(c.getTimeUsed()/totalTime)<<"% of total time"<<endl;
           cout<<"Average wait time in queue: "<<c.getTimeUsed()/c.getTotalNum()<<"time units"<<endl;
           cout<<"Avarage length of queue: "<<c.getAvarageLength()<<endl;
           sStatsQueuesQueue.pop();
     }
     if(registered)
     {
          cout<<"Total time of simulation: "<<totalTime<<endl;
          cout<<endl;
     }
}
void sStats::setOutputToFile(string a)
{
     file.open (a.c_str());
     sbuf = cout.rdbuf();
     cout.rdbuf(file.rdbuf());
                                             //zistit ci treba aj uzvret file aby neabol mem leak
}
void sStats::setOutputDefault()
{    
     if(fopened)
     {
           cout.rdbuf(sbuf);
           file.close();
     }
}


/******************** calendar **********************************/


/**
 * Konstruktor pro polozku v seznamu
 */
sCalUnit::sCalUnit(sEvent* event):event(event), previous(0), contiguous(0){}


/**
 * Inicializace seznamu(kalendare)
 */
void sCalendar::dbInit() {

   count = 0;                 // pocet prvku nastaven na nulu
   head = new sCalUnit;     // vytvori hlavicku seznamu
   head->contiguous = head;   // ukazatel na dalsi prvek ukazuje na hlavicku
   head->previous = head;     // ukazatel na predchozi prvek ukazuje na hlavicku
}


/**
 * Destruktor kalendare
 */
sCalendar::~sCalendar() {
   
   dbDelete();
   delete head;
}


/**
 * Smaze prvek ze kalendare
 *
 * @param <sEvent> event prvek jez bude smazan
 */
void sCalendar::dbDelete(sEvent* event) {
    
    sCalUnit* pom;
          pom = head->contiguous;
   while( pom != head )
   {
      if( event == pom->event )// smaze prvek kalendare
      {
         pom->previous->contiguous = pom->contiguous;
         pom->contiguous->previous = pom->previous;
         count--;
         delete pom->event;
         delete pom;
         break;
      }
      pom = pom->contiguous;
   }
}

 
/**
 * Smaze vsechny prvky kalendare
 */
void sCalendar::dbDelete() {

   while( head->contiguous != head )
   {
      dbDelete(head->contiguous->event);
   }
}


/**
 * Zobrazi obsah Udalosti
 */
void sCalendar::dbShow() const {

    sCalUnit* pom;
    pom = head->contiguous;
    while( pom != head )
    {
        cout <<"Jmeno: "<< pom->event->name <<", cas:"<< pom->event->time <<", priorita:"<< pom->event->priority << endl;
        pom = pom->contiguous;
    }
}


/**
 * Vlozi udalost do calendare, vlozi ji na misto podle casu
 *
 * @param <sEvent> event ukazatel na udalost jez se ma vlozit
 */
void sCalendar::dbInsertEvent(sEvent* event) {

   sCalUnit* pom = dbSearch(event);
   sCalUnit* newUnit = new sCalUnit(event);
   if( dbIsEmpty() )   //seznam je prazdny, vkladam prvni prvek
   {
       head->contiguous = newUnit;
       head->previous = newUnit;
       newUnit->contiguous = head;
       newUnit->previous = head;
   }
   else    // seznam neni prazdny
   {
       newUnit->contiguous = pom;
       newUnit->previous = pom->previous;
       pom->previous->contiguous = newUnit;
       pom->previous = newUnit;
   }
   count++;   // pocet prvku v seznamu +1;
}


/**
 * Najde misto v seznamu pro simulaci, hleda podle casu startu
 *    -- najde misto pred ktere se bude vkladat
 *
 * @param <sEvent> *event ukazetel simulace, jez misto hledame
 * @return <sCalUnit> *pom ukazatel mista, pred ktere se ma vlozit prvek do seznamu
*/
sCalUnit* sCalendar::dbSearch(sEvent *event) const {

   if( dbIsEmpty() )// prazdny seznam nebo jen jeden prvek
      return head;

   sCalUnit* pom;
   sCalUnit* newUnit = new sCalUnit(event);
   pom = head->contiguous;
   
   bool found = false;
// prohledavam kalendar, dokud nenajdu prvek s vetsim casem nebo jsme ho neprosel cely
   while( pom != head && !found )   
   {
      if( pom->event->time > newUnit->event->time )
      {
         found = true;   // nasli jsme udalost s vetsim casem
         break;
      }
      pom = pom->contiguous; // nasledujici prvek calendare
   }
   if( !found )   // vkladany prvek ma nejvetsi cas, vlozit nakonec calendare
      pom = head;
   delete newUnit;   // uvolni pomocnou promennou

   return pom; // vlozit pred
}


/**
 * Vyber prvniho zaznamu s nejmensim aktovacnim casem
 *
 * @return <sCalUnit> head->contiguous ukazatel na prvni prvek kalendare
 */
sCalUnit* sCalendar::dbGetFirst() const {

   return head->contiguous;
}


/**
 * Vybere prvni udalost kalendare
 *
 * @return <sEvent> event dalsi udalost
 */
sEvent sCalendar::dbGetNextEvent() {

   sEvent event;
   event.time = head->contiguous->event->time;
   event.priority = head->contiguous->event->priority;
   event.name = head->contiguous->event->name;
   dbDelete(head->contiguous->event);
   
   return event;
}


/**
 * Vrati pocet prvku v seznamu
 *
 * @return <int> count pocet prvku v seznamu
*/
int sCalendar::dbGetCount() const{

    return count;
}


/**
 * Zjisti zda je seznam prazdny(obsahuje jen hlavicku)
 *
 * @return <bool> true - prazdny seznam, false - seznam neni prazdny
*/
bool sCalendar::dbIsEmpty() const{

   if( head == head->contiguous ) // pokud hlavicka ukazeju sama na sebe
      return true;   // je prazdny

   return false;  // neni prazdny
}
