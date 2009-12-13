/*
 * --------------IMS-----------------
 *
 * Project:  Implementace diskr. simul�toru zalo�en�ho na ��zen� UD�LOSTMI (opak procesn� orientovan�ho p��stupu)
 * File:     sgen.cpp
 * Author:   Jaroslav Sendler, xsendl00, xsendl00@stud.fit.vutr.cz
 *           Du�an Kova�i�, xkovac21, xkovac21@stud.fit.vutbr.cz
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
    
   double a = rand();
   while( a <= 1e-7 )
      a = random();

   return -log(a)/lambda;
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
 * Generator normalniho rozlozeni - podel vzorce
 *
 * @param[in] <double> mu
 * @param[in] <double> sigma
 * @retun <double>
 */
double sGen::normalGen(double mu, double sigma) {

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
         a *= random();
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
