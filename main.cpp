#include <iostream>
#include "sim.h"
#include <stdio.h>

using namespace std;

int main(int argc, char *argv[])
{
    sFascility a;
    sStorage b(5);
    sQueue q;
    sEvent e;
    
    q.push(e);
    cout<<a.free<<endl;
    cout<<b.isEmpty()<<endl;
    
    getchar();

    return EXIT_SUCCESS;
}
