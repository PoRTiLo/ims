
#include <fstream>
#include <queue>
#include <string>

using namespace std;


class sEvent
{     
      public:
             sEvent();
             sEvent(string name);
             ~sEvent(); 
             string name;
             double time;
             int priority;

};

class sFascility
{
      public:
             sFascility();
             ~sFascility();
             
             int free;                       //zariadenie je volne defaultne             
             void sieze(sEvent a);      //zabere zariadenie
             void release();
      private:
             queue<sEvent> fascQueue;     //fronta pre udalosti ak je zariadenie obsadene
            

};

class sQueue : public queue<sEvent> 
{
};

class sStorage
{
      public:
             sStorage();
             sStorage(int capacity);
             ~sStorage();            
             
             void take(sEvent a);
             void bringBack();
             bool isEmpty();
             
      private:
             int left;                              //zasoba v sklade         
             int full;                              //maximalny obsah skladu         
             queue<sEvent> storQueue;     //fronta pre udalosti ak je sklad vztazeny
};

class sSimulation
{
      public:
             sSimulation();
             ~sSimulation();
             
             void start(int length);
             void start(int begin,int end);
             
             int startTime;                          //start time       
             int finishTime;                         //finish time       
             int currentTime;                           //current time
      private:
             bool running;
};

class sStats
{
      public:
             sStats();
             sStats(sSimulation a);
             ~sStats();
             
             class sSimulation sim;
             
             void registerObject(sStorage);
             void registerObject(sFascility);
             void registerObject(sQueue);
             void print();
             void setOutputToFile(string name);
             void setOutputDefault();
      private:
             queue<sStorage> sStatsQueuesStorage;
             queue<sFascility> sStatsQueuesFascility;
             queue<sQueue> sStatsQueuesQueue;
             bool registered;
             bool fopened;
             ofstream file;
             streambuf* sbuf;
};

class sCalUnit {
public:
//    sCalUnit(){};
    sCalUnit(sEvent *event=0);
    ~sCalUnit(){};
 
    sCalUnit* contiguous;
    sCalUnit* previous;
    sEvent* event;

};

class sCalendar {
    sCalUnit *head;
    int count; // pocet prvku v seznamu

private:
    void dbCopy(const sCalendar& t);
    void dbInit();

public:

    sCalendar() {
        dbInit();
    }
    sCalendar(const sCalendar& t);                    // vytvoreni seznamu
    ~sCalendar();                          // zruseni seznamu
    void dbDelete(sEvent* event);              // zruseni udalosti
    void dbDelete();                            //zruseni vsech udalosti
    int dbGetCount() const;
    void dbInsertEvent(sEvent* event);
    sCalUnit* dbSearch(sEvent* event) const; // vrati pozice prvku pred ktery se ma vlozit
    //void dbInsertSimByTime(sCalUnit* calUnit);
    //void dbInsertSimByPriority(Simulation* sim);
    //void dbInsertSimF(Simulation* sim);
    //void dbInsertSimL(Simulation* sim);
 
    //Simulation* dbSearchByTime(Simulation* sim) const; // vrati pozice prvku pred ktery se ma vlozit
    //Simulation* dbSearchByPriority(Simulation* sim) const;
    //void dbSortByTime();
    //void dbSortByPriority();
    void dbShow() const;
    bool dbIsEmpty() const;
    //BList& operator=(const sCalendar& t);
};
