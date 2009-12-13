#include <iostream>
#include "sim.h"
#include <cmath>
#include <cstdlib>
#include <climits>

#define SEED 7;

static unsigned numRand = SEED;


/**
 * Python
 */
double pytExp(double lambda) {

   double a = rand();
   while( a <= 1e-7 )
      a = rand();

   return -log(a)/lambda;
}

/**
 * Propablib
 */
double libExp(double lambda) {

   return (-log(1.0-(double)rand()/(double)RAND_MAX)/(double)lambda);
}

/**
 * Simlib
 */
double simExp(double lambda) {
   
   return -lambda * log(rand());
}

/**
 * Python
 */
 double pytUniform(double a, double b) {

        return a + (b-a) * rand();
 }

 /**
  * Simlib
  */
 double simUniform(double a, double b) {

   if( a >= b )
   {
       cout<<"spatne parametry"; // prfehodime je /////////////dodelat
   }

   return(a + (b - a) * rand());
 }

 /**
  * Random z prednasky
  */
 double predRandom() {

    numRand = numRand * 69069L + 1;
    return numRand / ((double)ULONG_MAX + 1);
}
 
/**
 * Python - notmalni rozlozeni
 */
double pythNormal(double mu, double sigma) {

   double a, b, z, zz;
   while( 1 )
   {
      a = random();
      b = 1.0 - random();
      z = 4 * exp(-0.5)/sqrt(2.0)*(a-0.5)/b;
      zz = z*z/4.0;
      if( zz <= -log(b) )
         break;
   }

   return mu + z*sigma;
}

/**
 * 
 */
double libNormal(double esp,double var)
{

   double a = (double)random()/(double)RAND_MAX;
   double b = (double)random()/(double)RAND_MAX;
   double z = sqrt(-2.0*log(a))*cos(2*M_PI*b);
   
   return esp + var * z;
}

/**
 * Normalni
 *
 * @param
 * @param
 * @return<>
 */
double simNormal(double mi, double sigma)
{
  int i;
  double SUM = 0.0;
  for (i=0; i<12; i++)  
      SUM += random();
  
  return (SUM-6.0)*sigma + mi;
}
/// poresit random nebo rand....

/**
 *
 */
unsigned long libPoisson(double lambda)
{
   double a = exp(-lambda);
   double b = a;
   double u = (double)random()/(double)RAND_MAX;
   unsigned long k = 0;
   while (u > b)
   {
      a *= (lambda / (double)(++k));
      b += a;
   }

   return k;
}

/**
 * Poisson - simlib
 */
int simPoisson(int lam) {
   double a = 0.0;
   double b = 0.0;
   int poiss = 0;
   double sl;
   if( lam <= 0 )
       cout << "chyba fce" << endl;
   if( lam <= 9.0 )
   {
      b = exp(-lam);
      a = 1.0;
      while( 1 )
      {
         a *= rand();
         if( a < b )
            break;
         poiss += 1;
      }
   }
   else
   {
      sl = sqrt(lam);
      poiss = int(round(libNormal(lam, sl) +0.5));
      while( poiss < 0 )
      {
         poiss = int(round(libNormal(lam, sl) + 0.5));
      }
   }
   return poiss;
}


int main(int argc, char *argv[])
{
    int lam;
    //poisson(lam);
   sCalendar abcd;
   sSimulation sim;
   sEvent event;
   event.time = 500;
   event.priority = 1;

   abcd.dbInsertEvent(new sEvent(event));
   event.time = 100;
   event.name = "velbloud";
   event.priority = 1;
   abcd.dbInsertEvent(new sEvent(event));

   event.time = 1000;
   event.priority = 1;
   event.name = "pes";
   abcd.dbInsertEvent(new sEvent(event));
   event.time = 1;
   event.priority = 1;
   event.name= "kocka";
   abcd.dbInsertEvent(new sEvent(event));
   //abcd.dbShow();

   sFascility a;
   sStorage b(5);
   sQueue q;
   sEvent e;

   q.push(e);
 //  cout<<a.free<<endl;
  // cout<<b.isEmpty()<<endl;

  // cout<< exp(100)<<endl;
srand(time(NULL));
   int cykl = 0;
   while(cykl < 50000)
   {
      cout<< predRandom() << endl;
      cykl++;
   }


   getchar();





   return 1;//EXIT_SUCCESS;
}
