#include <iostream>
#include "sim.h"

//#define DEBUG // zapne debugovaci makra
//using namespace std;
/********************* sFascility *********************/
sFascility::sFascility()    
{
     free = 1;
}

sFascility::~sFascility()   
{
}

void sFascility::sieze(sEvent a)
{
     if (free == 1)
     {
        free = 0;
     }
     else
         fascQueue.push(a);
}

void sFascility::release()
{
     if (free == 0)
     {
        if (fascQueue.empty())
        {
           free = 1;         //zariadenie je volne defaultne                  
           return;
        }
        else
        {
           fascQueue.pop();
        }
     }
}   
/************************** sEvent ******************************/

sEvent::sEvent()
{
     name="default";
     time = 0;
     priority =0;
}

sEvent::sEvent(string start)
{
     name=start;
     time = 0;
     priority =0;
}

sEvent::~sEvent()
{
}       
/************************* sStorage ******************************/
sStorage::sStorage(int capacity)
{
     full = capacity;                
     left = capacity;
}

sStorage::sStorage()
{
     full = 1;                
     left = 1;
}

sStorage::~sStorage()
{
}

void sStorage::take(sEvent a)
{
     if (left>0)
        left--;
     else
         storQueue.push(a);
}

void sStorage::bringBack()
{  
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
/********************* sSimulation *****************************/
sSimulation::sSimulation()
{
     startTime = 0;
     finishTime = 0;
     currentTime = 0;
     running = false;
}

sSimulation::~sSimulation()
{
}

void sSimulation::start(int length)
{
     currentTime = 0;
     startTime = 0;
     finishTime = length;
     running = true;
}

void sSimulation::start(int begin,int end)
{
     startTime = begin;
     currentTime = begin;
     finishTime = end;
     running = true;
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
     if (!sStatsQueuesStorage.empty())
     {
           cout<<"***************** Storages statistics *****************"<<endl;
     }
     sStorage a;
     while (!sStatsQueuesStorage.empty() && registered == true)
     {
           a = sStatsQueuesStorage.front();
           sStatsQueuesStorage.pop();
     }
     
     if (!sStatsQueuesFascility.empty())
     {
           cout<<"***************** Fascilities statistics *****************"<<endl;
     }
     sFascility b;
     while (!sStatsQueuesFascility.empty() && registered == true)
     {
           b = sStatsQueuesFascility.front();
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
           sStatsQueuesQueue.pop();
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

/******************************* calendar ******************/

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
 * Destruktor seznam -
 */
sCalendar::~sCalendar() {
   
   dbDelete();
   delete head;
}


/**
 * Smaze prvek ze seznamu
 *
 * @param <sEvent> event prvek jez bude smazan
 */
void sCalendar::dbDelete(sEvent* event) {

sCalUnit* pom = head->contiguous;
   while( pom != head )
   {
      if( event == pom->event )// smaze prvek seznamu
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
 * Smaze vsechny prvky seznamu
 */
void sCalendar::dbDelete() {

   while( head->contiguous != head )
   {
      dbDelete(head->contiguous->event);
   }
}


/**
 * Zobrazi obsah Simulace(cas, priorita, koncovy cas)
 */
void sCalendar::dbShow() const {

    sCalUnit* pom;
    pom = head->contiguous;
    while( pom != head )
    {
        cout << pom->event->name << endl;
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
sCalUnit* sCalendar:: dbSearch(sEvent *event) const {

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
      }
      pom = pom->contiguous; // nasledujici prvek calendare
   }
   if( !found )   // vkladany prvek ma nejvetsi cas, vlozit nakonec calendare
      pom = head;
   delete newUnit;   // uvolni pomocnou promennou

   return pom; // vlozit pred
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






/************************************ NEPOUZITE ZBYTECNE **************************/
//------------------- dodelat jen prot aby calendar plnil fci obousmerneho spojiteho seznamu s halvickou
/*
 * Zkopiruje seznam
 *
 * @param t kopirovany seznam

void sCalendar::dbCopy(const sCalendar& t ) {

   Simulation* pom;
   pom = t.head->contiguous;
   while( pom != head )
   {
      dbInsertSimL(pom);
      pom = pom->contiguous;
   }
}



 * Vytvori novy stejny seznam
 *
 * @param t

sCalendar::sCalendar(const sCalendar& t) {

   dbInit();
   dbCopy(t);
}



int sCalendar::dbTime(const sCalendar& t) {
   return t.head->contiguous->time;
}




 * Bublesort - radi podle casu

void sCalendar::dbSortByTime() {

    int i=0;
    Simulation* pom = head->contiguous;
    Simulation* pomNext;
    // seznam neni prazdny ani neobsahuje jen jeden prvek
    if( !dbIsEmpty() && head->contiguous != head->previous )
    {
        for( int k = 0; k < count; k++ )
        {
           for( pom = head->contiguous; pom->contiguous != head; )
           {
               if( pom->startSim > pom->contiguous->startSim )
               {
                   if( pom->previous == head )//prohazuje se prvni prvek s druhym
                   {
                      pomNext = pom->contiguous;
                      head->contiguous = pomNext;
                      pomNext->contiguous->previous = pom;
                      pomNext->previous = head;
                      pom->contiguous = pomNext->contiguous;
                      pomNext->contiguous = pom;
                      pom->previous = pomNext;
                      pomNext->contiguous = pom;
                   }
                   else
                   {
                      //prohazuji se nejake prvky v poli
                      pomNext = pom->contiguous;

                      pom->previous->contiguous = pomNext;
                      pomNext->contiguous->previous = pom;
                      pomNext->previous = pom->previous;
                      pom->contiguous = pomNext->contiguous;
                      pomNext->contiguous = pom;
                      pom->previous = pomNext;
                      pomNext->contiguous = pom;
                   }
#ifdef DEBUG
    pom->previous->previous->getSim();
    pom->previous->getSim();
    pom->getSim();
    pom->contiguous->getSim();
    pom->contiguous->contiguous->getSim();
    cout<<"-------------------"<<endl;
#endif
               }
               else
               {
                   pom = pom->contiguous;
               }
           }
        }
    }
}



 * Bublesort - radi podle PRIORITY

void sCalendar::dbSortByPriority() {

    int i=0;
    Simulation* pom = head->contiguous;
    Simulation* pomNext;
    // seznam neni prazdny ani neobsahuje jen jeden prvek
    if( !dbIsEmpty() && head->contiguous != head->previous )
    {
        for( int k = 0; k < count; k++ )
        {
           for( pom = head->contiguous; pom->contiguous != head; )
           {
               if( pom->prioritySim > pom->contiguous->prioritySim )
               {
                   if( pom->previous == head )//prohazuje se prvni prvek s druhym
                   {
                      pomNext = pom->contiguous;
                      head->contiguous = pomNext;
                      pomNext->contiguous->previous = pom;
                      pomNext->previous = head;
                      pom->contiguous = pomNext->contiguous;
                      pomNext->contiguous = pom;
                      pom->previous = pomNext;
                      pomNext->contiguous = pom;
                   }
                   else
                   {
                      //prohazuji se nejake prvky v poli
                      pomNext = pom->contiguous;

                      pom->previous->contiguous = pomNext;
                      pomNext->contiguous->previous = pom;
                      pomNext->previous = pom->previous;
                      pom->contiguous = pomNext->contiguous;
                      pomNext->contiguous = pom;
                      pom->previous = pomNext;
                      pomNext->contiguous = pom;
                   }
#ifdef DEBUG
    pom->previous->previous->getSim();
    pom->previous->getSim();
    pom->getSim();
    pom->contiguous->getSim();
    pom->contiguous->contiguous->getSim();
    cout<<"-------------------"<<endl;
#endif
               }
               else
               {
                   pom = pom->contiguous;
               }
           }
        }
    }
}


**
 * Vlozi simulaci do calendare, vlozi ji na misto podle priority
 *
 * @param sim ukazatel na simulaci jez se ma vlozit

void sCalendar::dbInsertSimByPriority(Simulation* sim) {//sCalendar& t) {

    Simulation* pom = dbSearchByPriority(sim);

    if(dbIsEmpty())   //seznam je prazdny, vkladam prvni prvek
    {
         head->contiguous = sim;
         head->previous = sim;
         sim ->contiguous = head;
         sim ->previous = head;
    }
    else
    {
        sim->contiguous = pom;
        sim->previous = pom->previous;
        pom->previous->contiguous = sim;
        pom->previous = sim;
    }
    count++;
}



 * Najde misto v seznamu pro simulaci, hleda podle casu startu
 *    -- najde misto pred, ktere se bude vkladat
 *
 * @param *sim ukazetel simulace, jez misto hledame
 * @return pom ukazatel mista, pred ktere se ma vlozit prvek do seznamu

Simulation* sCalendar:: dbSearchByTime(Simulation *sim) const { // iterator

      if( dbIsEmpty() )// prazdny seznam nebo jen jeden prvek
          return head;

      Simulation* pom;
      pom = head->contiguous;
      bool found = false;
      while( pom != head && !found )
      {
          if( pom->startSim > sim->startSim )
          {
              found = true;
          }
          pom = pom->contiguous;
      }
      if( !found )
         pom = head;

      return pom; // vlozit pred
}



 * Vlozi simulaci do calendare, vlozi ji na misto podle casu startu
 *
 * @param sim ukazatel na simulaci jez se ma vlozit

void sCalendar::dbInsertSimByTime(Simulation* sim) {

    Simulation* pom = dbSearchByTime(sim);

    if(dbIsEmpty())   //seznam je prazdny, vkladam prvni prvek
    {
         head->contiguous = sim;
         head->previous = sim;
         sim ->contiguous = head;
         sim ->previous = head;
    }
    else
    {
        sim->contiguous = pom;
        sim->previous = pom->previous;
        pom->previous->contiguous = sim;
        pom->previous = sim;
    }
    count++;
}


 * Vlozi simulaci na prvni misto v calendari
 *
 * @param sim ukazatel na simulaci jez se ma vlozit
 
void sCalendar::dbInsertSimF(Simulation* sim) {//sCalendar& t) {

    if( dbIsEmpty() ) //seznam je prazdny, vkladam prvni prvek
    {
         head->contiguous = sim;
         head->previous = sim;
         sim ->contiguous = head;
         sim ->previous = head;
    }
    else
    {
        head->contiguous->previous = sim;
        sim->contiguous = head->contiguous;
        sim->previous = head;
        head->contiguous = sim;
    }
    count++;
}



 * Vlozi simulaci na posledni misto v calendari
 *
 * @param sim ukazatel na simulaci jez se ma vlozit

void sCalendar::dbInsertSimL(Simulation* sim) {//sCalendar& t) {

    if( dbIsEmpty() ) //seznam je prazdny, vkladam prvni prvek
    {
         head->contiguous = sim;
         head->previous = sim;
         sim ->contiguous = head;
         sim ->previous = head;
    }
    else
    {
        head->previous->contiguous = sim;
        sim->contiguous = head;
        sim->previous = head->previous;
        head->previous = sim;
    }
    count++;
}



 * Najde misto v seznamu pro simulaci, hleda podle priority
 *    -- najde misto pred, ktere se bude vkladat
 *
 * @param *sim ukazetel simulace, jez misto hledame
 * @return pom ukazatel mista, pred ktere se ma vlozit prvek do seznamu
 
Simulation* sCalendar:: dbSearchByPriority(Simulation *sim) const { // iterator

      if( dbIsEmpty() )//|| head->contiguous == head->previous )  // prazdny seznam nebo jen jeden prvek
          return head;

      Simulation* pom;
      pom = head->contiguous;
      bool found = false;
      while( pom != head && !found )
      {
          if( pom->prioritySim > sim->prioritySim )
          {
              found = true;
          }
          pom = pom->contiguous;
      }
      if( !found )
         pom = head;

      return pom; // vlozit pred
}
*/
