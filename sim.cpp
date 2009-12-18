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

/**
 * Konstruktor zarizeni - defaultni nastaveni
 */
sFascility::sFascility()
{
     free = true;                                           //ukazatel stavu zarizeni
     name = "Default fascility";                            //jmeno zarizeni
}

/**
 * Konstruktor zarizeni
 *
 * @param[in] <string> id identifikacni cislo zarizeni
 */
sFascility::sFascility(string id)
{
     free = true;
     name = id;
}

/**
 * Destruktor zarizeni
 */
sFascility::~sFascility()
{
}

/**
 * Funkce pro osazeni zarizeni
 *
 * @param[in] <sEvent> a udalost, jez chce obsadit zarizeni
 */
void sFascility::seize(sEvent a)
{
     if (free == true)                                      //je prazdne
     {
        free = false;                                       //obsazeno
        currentEvent = a;                                   //udalost obsadi zarizeni
     }
     else                                                   //neni prazdne
     {
        if (a.priority > currentEvent.priority)             //pokud ma nova udalost vetsi prioritu
        {
          removedQueue.push(currentEvent);                  //udaost s nizsi prioritou je zarazena do "vyhozene" rady
          currentEvent = a;                                 //a obsadi si zarizeni
        }
     }

}

/**
 * Nastaveni jmena zarizeni
 *
 * @param[in] <string> id jmeno zarizeni
 */
void sFascility::setName(string id)
{
     name = id;
}

/**
 * Uvolneni zarizani
 */
void sFascility::release()
{
     if (free == false)                                     //zarizeni neni prazdne
     {
        if (fascQueue.isEmpty())                            //rada zarizeni je prazdna
        {
           free = true;                                     //zariadenie je volne defaultne
           return;
        }
        else                                                //rada na zarizeni neni prazdna
        {
           if (removedQueue.isEmpty())                      //nejsou zadne vyhozene udalosti od zarizeni
           {
              currentEvent = fascQueue.back();
              fascQueue.pop();
           }
           else                                             //existuje rada s "vyhozentmi" udalostmi
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

/**
 * Konstruktor udalosti
 */
sEvent::sEvent()
{
     name="Default event";
     time = 0;
     priority =0;
}

/**
 * Konstruktor udalosti
 *
 * @param[in] <string> start jmeno udalsoti
 */
sEvent::sEvent(string start)
{
     name=start;
     time = 0;
     priority =0;
}

/**
 * Konstruktor udalosti
 *
 * @param[in] <string> start jmeno udalsoti
 * @param[in] <double> now cas startu udalosti
 */
sEvent::sEvent(string start, double now)
{
     name=start;
     time = now;
     priority = 0;
}

/**
 * Konstruktor udalosti
 *
 * @param[in] <string> start jmeno udalsoti
 * @param[in] <double> now cas startu udalosti
 * @param[in] <int> prio priorita udalosti
 */
sEvent::sEvent(string start, double now, int prio)
{
     name=start;
     time = now;
     priority = prio;
}

/**
 * Nastaveni jmena udalosti
 *
 * @param[in] <string> id
 */
void sEvent::setName(string id)
{
     name = id;
}

/**
 * Destruktor udalosti
 */
sEvent::~sEvent()
{
}


/************************* sStorage ******************************/

/**
 * Konstruktor skladu
 *
 * @param[in] <int> capacity velikost skladu
 * @param[in] <string> id identifikacni oznaceni
 */
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
     for(i=0;i<full;i++)                                    //vyprazdneni
     {
          takenByEvents[i] = 0;
          currentTime[i] = 0;
     }
}

/**
 * Konstruktor skladu
 *
 * @param[in] <int> capacity velikost skladu
 */
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

/**
 * Konstruktor skladu
 */
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

/**
 * Destruktor skladu
 */
sStorage::~sStorage()
{
     delete takenByEvents;
     delete currentTime;
}

/**
 * Nastaveni kapacity skladu
 *
 * @param[in] <int> capacity
 */
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

/**
 * Vyber udalosti ze skladu
 *
 * @param[in] <sEvent> a
 */
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

/**
 *
 *
 * @param[in] <string> id
 */
void sStorage::setName(string id)
{
     name = id;
}

/**
 *
 *
 * @param[in] <double> time
 */
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

/**
 * Zjisti stav skladu, zda je prazdny nebo ne
 *
 * @return <bool> TRUE - prazdny sklad | FALSE - neprazdny sklad
 */
bool sStorage::isEmpty()
{
    if(left == 0)
         return true;
    else
         return false;
}

/**
 *
 *
 * @return <int> full
 */
int sStorage::getStorageSize()
{
    return full;
}

/**
 *
 *
 * @return <int> left
 */
int sStorage::getStoregeLeft()
{
    return left;
}

/**
 *
 *
 * @return <double> timeTotal
 */
double sStorage::getTimeUsed()
{
    return timeTotal;
}

/**
 *
 *
 * @param[in] <int> i
 * @return <double>
 */
double sStorage::getUsagePerUnit(int i)
{
    if (i<full)
          return takenByEvents[i];
    else
          return -1;
}


/********************* sSimulation *****************************/

/**
 * Konstruktor simulace
 */
sSimulation::sSimulation()
{
     name = "Default simulation";
     startTime = 0;
     finishTime = 0;
     currentTime = 0;
     running = false;
}

/**
 * Konstruktor simulace
 *
 * @param[in] <string> id identifikacni jmeno simulace
 */
sSimulation::sSimulation(string id)
{
     name = id;
     startTime = 0;
     finishTime = 0;
     currentTime = 0;
     running = false;
}

/**
 * Destruktor simulace
 */
sSimulation::~sSimulation()
{
}

/**
 * Nastaveni doby behu simulace
 *
 * @param[in] <double> lenght delka behu simulace
 */
void sSimulation::start(double length)
{
     currentTime = 0;
     startTime = 0;
     finishTime = length;
     running = true;
}

/**
 * Nastaveni startu simulace
 *
 * @param[in] <double> begin cas pro zahajeeni simulace
 * @param[in] <double> end cas pro ukonceni simulae
 */
void sSimulation::start(double begin,double end)
{
     startTime = begin;                                     //cas startu
     currentTime = begin;                                   //aktualni cas
     finishTime = end;                                      //cas konce simulace
     running = true;                                        //stav simulace
}

/**
 * Zjisti zda simulace bezi
 *
 * @return <bool> TRUE - bezi | FALSE - nebezi
 */
bool sSimulation::isRunning()
{
     return running;
}

/**
 * Nastaveni jmena simulace
 *
 * @param[in] <string> id identifikacni nazev simulace
 */
void sSimulation::setName(string id)
{
     name = id;
}


/******************** sQueue **********************************/

/**
 * Konstruktor fronty
 */
sQueue::sQueue()
{
      counter = 0;                                          //pocet prvku ve fronte
      timeUsed = 0;                                         //cas vyuziti fronty
      first = true;
      name = "Default queue";                               //jmeno fronty
}

/**
 * Konstruktor fronty
 *
 * @param[in] <string> id identifikacni jmeno fronty
 */
sQueue::sQueue(string id)
{
      counter = 0;
      timeUsed = 0;
      first = true;
      name = id;
}

/**
 * Destruktor fronty
 */
sQueue::~sQueue()
{
}

/**
 * Bastaveni jmena fronty
 *
 * @param[in] <string> id pojmenovani fronty
 */
void sQueue::setName(string id)
{
     name = id;
}

/**
 *
 *
 * @param[in] <sEvent> event
 */
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

/**
 *
 */
void sQueue::pop()
{
     queueEvents.pop_back();
}

/**
 * 
 *
 * @return <sEvent>
 */
sEvent sQueue::front()
{
     return queueEvents.front();
}

/**
 *
 *
 * @return <sEvent>
 */
sEvent sQueue::back()
{
     return queueEvents.back();
}

/**
 * Kontrola zda je fronta prazdna
 *
 * @return <bool> TRUE - prazdne | FALSE - neprazdna
 */
bool sQueue::isEmpty()
{
     return queueEvents.empty();
}

/**
 * Velikost rady
 *
 * @return <int> queueEvents.size() velikost rady
 */
int sQueue::size()
{
     return queueEvents.size();
}

/**
 * Ziska pocet prvku v rade
 *
 * @return <int> counter pocet prvku v rade
 */
int sQueue::getTotalNum()
{
     return counter;
}

/**
 *
 *
 * @return <double>
 */
double sQueue::getTimeUsed()
{
     return timeUsed;
}

/**
 *
 *
 * @return <double>
 */
double sQueue::getAvarageLength()
{
    return curNum/counter;
}

/**
 * Zacatek startu
 *
 * @return <double> start
 */
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
