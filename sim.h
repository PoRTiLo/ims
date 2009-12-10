
#include <fstream>
#include <queue>
#include <string>



class sEvent
{     
      public:
             sEvent();
             sEvent(std::string name);
             ~sEvent(); 
             std::string name;
             
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
             std::queue<sEvent> fascQueue;     //fronta pre udalosti ak je zariadenie obsadene
            

};

class sQueue : public std::queue<sEvent> 
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
             std::queue<sEvent> storQueue;     //fronta pre udalosti ak je sklad vztazeny
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
             void setOutputToFile(std::string name);
             void setOutputDefault();
      private:
             std::queue<sStorage> sStatsQueuesStorage;
             std::queue<sFascility> sStatsQueuesFascility;
             std::queue<sQueue> sStatsQueuesQueue;
             bool registered;
             bool fopened;
             std::ofstream file;
             std::streambuf* sbuf;
};
