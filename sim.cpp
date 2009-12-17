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
     name = "Default fascility";
}

sFascility::sFascility(string id)
{
     free = true;
     name = id;
}

sFascility::~sFascility()   
{
}

void sFascility::seize(sEvent a)
{
     if (free == true)
     {
        free = false;
        currentEvent = a;
     }
     else
     {
        if (a.priority > currentEvent.priority)
        {
          removedQueue.push(currentEvent);             
          currentEvent = a;
        }                   
     }
     
}
void sFascility::setName(string id)
{
     name = id;
}
void sFascility::release()
{
     if (free == false)
     {
        if (fascQueue.isEmpty())
        {
           free = true;         //zariadenie je volne defaultne                
           return;
        }
        else
        {
           if (removedQueue.isEmpty())
           {
              currentEvent = fascQueue.back(); 
              fascQueue.pop();
           }
           else 
           {
                if (removedQueue.back().priority >= fascQueue.back().priority)
                {
                   currentEvent = removedQueue.back();
                   removedQueue.pop();
                }  
                else
                {
                   currentEvent = fascQueue.back();
                   fascQueue.pop();
                }
           }
        }
     }
     else
     {
         //zariadenie bolo volne a dalsie uvolnenie nema efekt
     }
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

void sEvent::setName(string id)
{
     name = id;
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
     for(i=0;i<full;i++)
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
     for(i=0;i<full;i++)
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

void sStorage::setCapacity(int capacity)
{
     delete currentTime;
     delete takenByEvents;
     
     first = true;    
     full = capacity;                
     left = capacity;
     timeUsed = 0;
     timeTotal = 0;
     
     currentTime = (double*) operator new (sizeof(double)* full);
     takenByEvents = (double*) operator new (sizeof(double)* full);
     
     int i;
     for(i=0;i<full;i++)
     {
          takenByEvents[i] = 0;
          currentTime[i] = 0;
     }
     
}
void sStorage::take(sEvent a)
{
     if(first == true)
     {
        timeUsed = a.time;
        first = false;
     }
     if ((a.time - timeUsed) > timeTotal)
        timeTotal = a.time - timeUsed;
        
     if (left>0)
        left--;
     else
     {
        storQueue.push(a);                  
     }    
     
}

void sStorage::setName(string id)
{
     name = id;
}
void sStorage::bringBack(double time)
{        
     if (left == 0)
     {
         if(!storQueue.isEmpty())    
           storQueue.pop();
         else
           left++;
     }      
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
bool sSimulation::isRunning()
{
     return running;
}  
void sSimulation::setName(string id)
{
     name = id;
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
void sQueue::setName(string id)
{
     name = id;
}

void sQueue::push(sEvent event)
{
     if(queueEvents.empty())
     {
        queueEvents.push_front(event);
     }
     else
     {
        sEvent temp = queueEvents.back();
        if (event.priority > temp.priority)
        {  
           int i = 0;
           deque<sEvent>::iterator it;
            
            for(it = queueEvents.begin(); it < queueEvents.end(); it++)
            {
                if(queueEvents[i].priority < event.priority)
                {
                     i++;
                     continue;
                }
                else 
                     break;
            }
            if (queueEvents.size() == (i+1))
            {
                queueEvents.push_back(event);
            }
            else
            {
                queueEvents.insert(++it,event);
            }
         }
         else
         {
             queueEvents.push_front(event); 
         }
     }
     counter++;
     if ((event.time - start) > timeUsed)
        timeUsed = event.time - start;
     curNum += size();
       
}
void sQueue::pop()
{
     queueEvents.pop_back();
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
double sQueue::getAvarageLength()
{
    return curNum/counter;
}
double sQueue::getTimeStart()
{
    return start;   
}


/******************** calendar **********************************/


/**
 * Konstruktor pro polozku v kalendare
 */
sCalUnit::sCalUnit(sEvent* event):event(event), previous(0), contiguous(0){}


/**
 * Inicializace kalendare
 */
void sCalendar::dbInit() {

   count = 0;                                               //pocet prvku nastaven na nulu
   head = new sCalUnit;                                     //vytvori hlavicku kalendare
   head->contiguous = head;                                 //ukazatel na dalsi prvek ukazuje na hlavicku
   head->previous = head;                                   //ukazatel na predchozi prvek ukazuje na hlavicku
}


/**
 * Destruktor kalendare
 */
sCalendar::~sCalendar() {
   
   dbDelete();                                              //postupne uvolnuje vsechny prvky kalendare
   delete head;                                             //smaze hlavikcu kalendare
}


/**
 * Smaze prvek ze kalendare
 *
 * @param[in] <sEvent> event prvek jez bude smazan
 */
void sCalendar::dbDelete(sEvent* event) {

   sCalUnit* pom = head->contiguous;                        //ukazatel na prvni prvek kalendare
   while( pom != head )                                     //pracuj, dokud jsem se nedosrali zpet na zacatek
   {
      if( event == pom->event )                             //smaze prvek kalendare
      {
         pom->previous->contiguous = pom->contiguous;       //vynechani prvku
         pom->contiguous->previous = pom->previous;
         count--;                                           //pocet prvku v kalendari -1
         delete pom->event;                                 //uvolni udalost
         delete pom;                                        //uvolni prvek kalendare
         break;
      }
      pom = pom->contiguous;                                //nasledujici prvek kalendare
   }
}

 
/**
 * Smaze vsechny prvky kalendare
 */
void sCalendar::dbDelete() {

   while( head->contiguous != head )                        //dokud jsme neprosli cely kalendar
   {
      dbDelete(head->contiguous->event);                    //mazani prvu kalendare
   }
}


/**
 * Zobrazi obsah Udalosti - debugovaci funkce
 */
void sCalendar::dbShow() const {

    sCalUnit* pom;
    pom = head->contiguous;
    while( pom != head )                                    //zobrazi postupne vsechny prvky kalendare
    {
        cout <<"Jmeno: "<< pom->event->name <<", cas:"<< pom->event->time <<", priorita:"<< pom->event->priority << endl;
        pom = pom->contiguous;
    }
}


/**
 * Vlozi udalost do calendare na misto podle casu
 *
 * @param[in] <sEvent> eventIn udalost jez se ma vlozit
 */
void sCalendar::dbInsertEvent(sEvent eventIn) {

   sEvent* event = new sEvent(eventIn);                     //vytvoreni noveho prvku
   sCalUnit* pom = dbSearch(event);                         //vyhledani pozice pred, kterou se vlozi prvek
   sCalUnit* newUnit = new sCalUnit(event);
   if( dbIsEmpty() )   //seznam je prazdny, vkladam prvni prvek
   {
       head->contiguous = newUnit;
       head->previous = newUnit;
       newUnit->contiguous = head;
       newUnit->previous = head;
   }
   else                                                     //kalendar neni prazdny
   {
       newUnit->contiguous = pom;
       newUnit->previous = pom->previous;
       pom->previous->contiguous = newUnit;
       pom->previous = newUnit;
   }
   count++;                                                 //pocet prvku v kalendari +1;
}


/**
 * Najde misto v seznamu pro simulaci, hleda podle casu startu
 *    -- najde misto pred ktere se bude vkladat
 *
 * @param <sEvent> *event ukazetel simulace, jez misto hledame
 * @return <sCalUnit> *pom ukazatel mista, pred ktere se ma vlozit prvek do seznamu
*/
sCalUnit* sCalendar::dbSearch(sEvent *event) const {

   if( dbIsEmpty() )                                        //prazdny seznam nebo jen jeden prvek
      return head;                                          //vracime ukazatel na hlavicku, vkalda se 1.prvek

   sCalUnit* pom;
   sCalUnit* newUnit = new sCalUnit(event);                 //vytvoreni noveho prvku kalendare
   pom = head->contiguous;
   
   bool found = false;
//prohledavam kalendar, dokud nenajdu prvek s vetsim casem nebo jsme ho neprosel cely
   while( pom != head && !found )   
   {
      if( pom->event->time > newUnit->event->time )
      {
         found = true;                                      //nasli jsme udalost s vetsim casem
         break;                                             //ukoncime hledani
      }
      else if( pom->event->time == newUnit->event->time )
      {
          while( pom->event->time == newUnit->event->time && pom != head )//prohledavani podle priority
          {
             if( pom->event->priority <= newUnit->event->priority )
             {
                 found = true;                              //nasli jsme udalost s mensi prioritou
                 break;
             }
             else
             {
                 found = true;
                 pom = pom->contiguous;
                 break;
             }
             pom = pom->contiguous;
          }
      }
      else
      {
      pom = pom->contiguous;                                //nasledujici prvek calendare
      }
   }
   if( !found )                                             //vkladany prvek ma nejvetsi cas, vlozit nakonec calendare
      pom = head;
   delete newUnit;                                          //uvolneni pomocne promenne

   return pom;                                              //ukazatel na miste, pred ktere se budu vkaldat
}


/**
 * Vyber prvniho zaznamu s nejmensim aktovacnim casem
 *
 * @return <sCalUnit> head->contiguous ukazatel na prvni prvek kalendare
 */
sCalUnit* sCalendar::dbGetFirst() const {

   return head->contiguous;                                 //ukazatel na prvni prvek kalendares
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
   event.type = head->contiguous->event->type;
   dbDelete(head->contiguous->event);                       //uvolni prvni udalost z kalendare

   return event;                                            //prvni udalost
}


/**
 * Vrati pocet prvku v seznamu
 *
 * @return <int> count pocet prvku v seznamu
*/
int sCalendar::dbGetCount() const {

    return count;                                           //pocet prvku v kalendari
}


/**
 * Zjisti zda je seznam prazdny(obsahuje jen hlavicku)
 *
 * @return <bool> true - prazdny seznam, false - seznam neni prazdny
*/
bool sCalendar::dbIsEmpty() const {

   if( head == head->contiguous )                           //pokud hlavicka ukazeju sama na sebe
      return true;                                          //je prazdny

   return false;                                            //neni prazdny
}
