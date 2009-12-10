#include <iostream>
#include "sim.h"

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
}

sEvent::sEvent(std::string start)
{
     name=start;
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
           std::cout<<"***************** Storages statistics *****************"<<std::endl;
     }
     sStorage a;
     while (!sStatsQueuesStorage.empty() && registered == true)
     {
           a = sStatsQueuesStorage.front();
           sStatsQueuesStorage.pop();
     }
     
     if (!sStatsQueuesFascility.empty())
     {
           std::cout<<"***************** Fascilities statistics *****************"<<std::endl;
     }
     sFascility b;
     while (!sStatsQueuesFascility.empty() && registered == true)
     {
           b = sStatsQueuesFascility.front();
           sStatsQueuesFascility.pop();
     }
     
     if (!sStatsQueuesQueue.empty())
     {
           std::cout<<"***************** Queues statistics *****************"<<std::endl;
     }
     sQueue c;
     while (!sStatsQueuesQueue.empty() && registered == true)
     {
           c = sStatsQueuesQueue.front();
           sStatsQueuesQueue.pop();
     }
}
void sStats::setOutputToFile(std::string a)
{
     file.open (a.c_str());
     sbuf = std::cout.rdbuf();
     std::cout.rdbuf(file.rdbuf());
                                             //zistit ci treba aj uzvret file aby neabol mem leak
}
void sStats::setOutputDefault()
{    
     if(fopened)
     {
           std::cout.rdbuf(sbuf);
           file.close();
     }
}
