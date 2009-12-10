/* 
 * --------------IMS-----------------
 *
 * Project:  Implementace diskr. simulátoru zalo¾eného na øízení UDÁLOSTMI (opak procesnì orientovaného pøístupu)
 * File:     dblist.cc
 * Author:   Jaroslav Sendler, xsendl00, xsendl00@stud.fit.vutr.cz
 *           Du¹an Kovaèiè, xkovac21, xkovac21@stud.fit.vutbr.cz
 * 
 * Created on December 10, 2009, 8:34 PM
 *
 * Encoding: ISO-8859-2
 *
 * Description:
 */


#include "simulation.h"
#include "dblist.h"

//#define DEBUG // zapne debugovaci makra
/**
 * Inicializace seznamu(kalendare)
 */
void DBList::dbInit() {

   count = 0;                 // pocet prvku nastaven na nulu
   head = new Simulation();   // vytvori hlavicku seznamu
   head->contiguous = head;   // ukazatel na dalsi prvek ukazuje na hlavicku
   head->previous = head;     // ukazatel na predchozi prvek ukazuje na hlavicku
}

/**
 * Destruktor seznam -
 */
DBList::~DBList() {

   dbDelete();
   delete head;
}

/**
 * Smaze prvek ze seznamu
 *
 * @param sim prvek jez bude smazan
 */
void DBList::dbDelete(Simulation* sim) {

   if( sim != head )
   {
      sim->previous->contiguous = sim->contiguous;
      sim->contiguous->previous = sim->previous;
      delete sim;                                              // smaze prvek seznamu
      count--;                                                 // snizi pocet prvku v seznamu
   }
}

 
/**
 * Smaze vsechny prvky seznamu
 */
void DBList::dbDelete() {

   while( head->contiguous != head )
   {
      dbDelete(head->contiguous);
   }
}


/**
 * Zobrazi obsah Simulace(cas, priorita, koncovy cas)
 */
void DBList::dbShow() const
{
     Simulation* pom;
     pom = head->contiguous;
     while( pom != head )
     {
         pom->getSim();
         pom = pom->contiguous;
     }
}


/**
 * Vlozi simulaci na prvni misto v calendari
 *
 * @param sim ukazatel na simulaci jez se ma vlozit
 */
void DBList::dbInsertSimF(Simulation* sim) {//DBList& t) {

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


/**
 * Vlozi simulaci na posledni misto v calendari
 *
 * @param sim ukazatel na simulaci jez se ma vlozit
 */
void DBList::dbInsertSimL(Simulation* sim) {//DBList& t) {

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


/**
 * Najde misto v seznamu pro simulaci, hleda podle priority
 *    -- najde misto pred, ktere se bude vkladat
 *
 * @param *sim ukazetel simulace, jez misto hledame
 * @return pom ukazatel mista, pred ktere se ma vlozit prvek do seznamu
 */
Simulation* DBList:: dbSearchByPriority(Simulation *sim) const { // iterator

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


/**
 * Vlozi simulaci do calendare, vlozi ji na misto podle priority
 *
 * @param sim ukazatel na simulaci jez se ma vlozit
 */
void DBList::dbInsertSimByPriority(Simulation* sim) {//DBList& t) {

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


/**
 * Najde misto v seznamu pro simulaci, hleda podle casu startu
 *    -- najde misto pred, ktere se bude vkladat
 *
 * @param *sim ukazetel simulace, jez misto hledame
 * @return pom ukazatel mista, pred ktere se ma vlozit prvek do seznamu
 */
Simulation* DBList:: dbSearchByTime(Simulation *sim) const { // iterator

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


/**
 * Vlozi simulaci do calendare, vlozi ji na misto podle casu startu
 *
 * @param sim ukazatel na simulaci jez se ma vlozit
 */
void DBList::dbInsertSimByTime(Simulation* sim) {

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


/**
 * Vrati pocet prvku v seznamu
 *
 * @return count pocet prvku v seznamu
 */
int DBList::dbGetCount() const{

    return count;
}


/**
 * Zjisti zda je seznam prazdny(obsahuje jen hlavicku)
 *
 * @return bool true - prazdny seznam, false - seznam neni prazdny
 */
bool DBList::dbIsEmpty() const{

   if( head == head->contiguous )
      return true;
   
   return false;
}


/**
 * Zkopiruje seznam
 *
 * @param t kopirovany seznam
 */
void DBList::dbCopy(const DBList& t ) {

   Simulation* pom;
   pom = t.head->contiguous;
   while( pom != head )
   {
      dbInsertSimL(pom);
      pom = pom->contiguous;
   }
}


/**
 * Vytvori novy stejny seznam
 *
 * @param t
 */
DBList::DBList(const DBList& t) {

   dbInit();
   dbCopy(t);
}


/*
int DBList::dbTime(const DBList& t) {
   return t.head->contiguous->time;
}
*/


/**
 * Bublesort - radi podle casu
 */
void DBList::dbSortByTime() {

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


/**
 * Bublesort - radi podle PRIORITY
 */
void DBList::dbSortByPriority() {

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
