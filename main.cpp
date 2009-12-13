#include <iostream>
#include "sim.h"
#include <stdio.h>
#include "sgen.h"

using namespace std;

int main(int argc, char *argv[])
{
    sFascility a;
    sStorage b(5);
    sQueue q;
    sEvent e;
    sSimulation sim("ahoj");
    double time = 0;
    sStats stats;
    q.push(e,time);
    cout<<a.free<<endl;
    cout<<b.isEmpty()<<endl;
    
    stats.print();
    getchar();

    return EXIT_SUCCESS;
}
