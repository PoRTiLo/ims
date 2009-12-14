/*
 * --------------IMS-----------------
 *
 * Project:  Implementace diskr. simulátoru zalo¾eného na øízení UDÁLOSTMI (opak procesnì orientovaného pøístupu)
 * File:     sgen.cpp
 * Author:   Jaroslav Sendler, xsendl00, xsendl00@stud.fit.vutr.cz
 *           Du¹an Kovaèiè, xkovac21, xkovac21@stud.fit.vutbr.cz
 *
 * Encoding: ISO-8859-2
 *
 * Description:
 */


#include "sgen.h"
#include <iostream>

using namespace std;

#define SEED 7;

static unsigned numRand = SEED;


/**
 * EXP - generator
 *
 * @param[in] <double> lambda
 * @return <double> nahodne cislo generovane exponencialni distribucni f-ci s parametrem lambda.
 */
double sGen::expGen(double lambda) {
    
   return (-log(1.0-(double)rand()/(double)RAND_MAX)/(double)lambda);
}


/**
 * Rovnomerny generator pseudonahodnych cisel
 *
 * @param[in] <double> b
 * @param[in] <double> a
 * @return <double>
 */
double sGen::uniformGen(double a, double b) {

   return a + (b-a) * rand();
}


/**
 * Generato pseudonahodnych cisel - z prednasky
 *
 * @return <double> pseudonahodne cislo
 */
double sGen::randomGen() {

   numRand = numRand * 69069L + 1;
   return numRand / ((double)ULONG_MAX + 1);
}


/**
 * Generator normalniho rozlozeni - Box-Muller transformace
 *
 * @param[in] <double> mean
 * @param[in] <double> sigma
 * @retun <double> result
 */
double sGen::normalGen(double mean, double sigma) {

   static double number2 = 0.0;
   static int number2_cached = 0;
   if( !number2_cached )                     // fce byla volana v
   {
      double x, y, r;                        // nahodne vygen. souradnice
      do {
         x = 2.0*rand()/RAND_MAX - 1;        // generovani nahodneho cisla v intervalu <-1;1>
         y = 2.0*rand()/RAND_MAX - 1;        // generovani nahodneho cisla v intervalu <-1;1>
         r = x*x + y*y;
      }while (r == 0.0 || r > 1.0);          // generujeme cisla dokud nepadnou jejich body do kruhu o polomeru 1

      {
         // vypocet dvou hodnot pomoci Box Muller transformace
         double d = sqrt(-2.0*log(r)/r);     // prevod vnitrnich kruznic na vnejsi kruznice, zvetseni, zmenseni kruznice
         double number1 = x*d;
         number2 = y*d;
         double result = number1*sigma + mean;
         number2_cached = 1;                 // druha vypoctena hodnota se uklada pro dalsi generovani
         return result;
      }
   }
   else                                      // hodnota vypoctena z minuleho volani
   {
      number2_cached = 0;
      double result = number2*sigma + mean;
      return result;
   }
}


/**
 * Genrator cisel poisosnovym rozlozenim
 *
 * @param[in] <double lambda
 * @return <int> poiss
 */
int sGen::poissonGen(double lambda) {

   double a = 0.0;
   double b = 0.0;
   int poiss = 0;
   double sl;
   if( lambda <= 0 )
       cout << "chyba fce" << endl;
   if( lambda <= 9.0 )
   {
      b = exp(-lambda);
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
      sl = sqrt(lambda);
      poiss = int(round(normalGen(lambda, sl) +0.5));
      while( poiss < 0 )
      {
         poiss = int(round(normalGen(lambda, sl) + 0.5));
      }
   }
   return poiss;
}
