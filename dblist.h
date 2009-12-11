/*
 * --------------IMS-----------------
 *
 * Project:  Implementace diskr. simulátoru zalo¾eného na øízení UDÁLOSTMI (opak procesnì orientovaného pøístupu)
 * File:     dblist.h
 * Author:   Jaroslav Sendler, xsendl00, xsendl00@stud.fit.vutr.cz
 *           Du¹an Kovaèiè, xkovac21, xkovac21@stud.fit.vutbr.cz
 *
 * Encoding: ISO-8859-2
 *
 * Description:
 */


#include <iostream>
#include "simulation.h"
using namespace std;


// obousmerny cyklicky zretezeny seznam s hlavickou

class DBList {
    Simulation *head;
    int count; // pocet prvku v seznamu

private:
    void dbCopy(const DBList& t);
    void dbInit();

public:

    DBList() {
        dbInit();
    }
    DBList(const DBList& t);                    // vytvoreni seznamu
    virtual ~DBList();                          // zruseni seznamu
    void dbDelete(Simulation* sim);              // zruseni udalosti
    void dbDelete();                            //zruseni vsech udalosti
    int dbGetCount() const;
    void dbInsertSimByTime(Simulation* sim);
    void dbInsertSimByPriority(Simulation* sim);
    void dbInsertSimF(Simulation* sim);
    void dbInsertSimL(Simulation* sim);
    Simulation* dbSearchByTime(Simulation* sim) const; // vrati pozice prvku pred ktery se ma vlozit
    Simulation* dbSearchByPriority(Simulation* sim) const;
    void dbSortByTime();
    void dbSortByPriority();
    void dbShow() const;
    bool dbIsEmpty() const;
    //BList& operator=(const DBList& t);
};
