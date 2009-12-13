#include <fstream>
#include <queue>
#include <string>

using namespace std;


class sEvent
{     
      public:
             sEvent();
             sEvent(string name);
             sEvent(string start, double now);
             sEvent(string start, double now, int prio);
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
             
             string name;
             int free;                       //zariadenie je volne defaultne             
             void sieze(sEvent a, double time);      //zabere zariadenie
             void release(double time);
             double getTimeUsed();
      private:
             queue<sEvent> fascQueue;     //fronta pre udalosti ak je zariadenie obsadene
             double timeUsed;
             double takenByEvents;
            

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
             
             string name;
             void take(sEvent a,double time);
             void bringBack(double time);
             int getStorageSize();
             int getStoregeLeft();
             double getTimeUsed();
             double getUsagePerUnit(int i);
             bool isEmpty();
             
      private:
             int left;                      //zasoba v sklade         
             int full;                      //maximalny obsah skladu         
             queue<sEvent> storQueue;       //fronta pre udalosti ak je sklad vztazeny
             double *currentTime;
             double *takenByEvents;
             double timeUsed;
             double timeTotal;
             bool first;
};

class sSimulation
{
      public:
             sSimulation();
             ~sSimulation();
             
             void start(double length);
             void start(double begin,double end);
             
             double startTime;                          //start time       
             double finishTime;                         //finish time       
             double currentTime;                           //current time
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


/**
 *
 */
class sCalendar {

      sCalUnit *head;                                       // hlavicka kalendare
      int count;                                            // pocet prvku v kalendare

   private:
      //void dbCopy(const sCalendar& t);
      void dbInit();                                        // inicializace kalendare

   public:
      sCalendar() {                                         // konstruktor kalendare
         dbInit();                                          // inicializace
      }
      //sCalendar(const sCalendar& t);                      // vytvoreni kalendare
      ~sCalendar();                                         // zruseni kalendare
      void dbDelete(sEvent* event);                         // zruseni konkretni udalosti
      void dbDelete();                                      // zruseni vsech udalosti
      int dbGetCount() const;                               // zjisteni poctu zaznamu v calendari
      void dbInsertEvent(sEvent* event);                    // vkladani novych prvku, zarazeni podle casu
      sCalUnit* dbSearch(sEvent* event) const;              // vrati pozice prvku pred ktery se ma vlozit
      sCalUnit* dbGetFirst() const;                         // vrati ukazatel na prvni prvek kalendare
      void dbShow() const;                                  // zobrazeni obsahu Udalosti
      bool dbIsEmpty() const;                               // test na prazdnost seznamu
      //void dbInsertSimByTime(sCalUnit* calUnit);
      //void dbInsertSimByPriority(Simulation* sim);
      //void dbInsertSimF(Simulation* sim);
      //void dbInsertSimL(Simulation* sim);
 
      //Simulation* dbSearchByTime(Simulation* sim) const; // vrati pozice prvku pred ktery se ma vlozit
      //Simulation* dbSearchByPriority(Simulation* sim) const;
      //void dbSortByTime();
      //void dbSortByPriority();
      //BList& operator=(const sCalendar& t);
};
