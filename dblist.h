/**
 *
 * Dvousmerny cyklicky zretezeny seznam s hlavickou
 *
 * Hlavickovty soubor pro dblist.cc
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
