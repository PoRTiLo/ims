/*
 * --------------IMS-----------------
 *
 * Project:  Implementace diskr. simulátoru zalo¾eného na øízení UDÁLOSTMI (opak procesnì orientovaného pøístupu)
 * File:     sgen.h
 * Author:   Jaroslav Sendler, xsendl00, xsendl00@stud.fit.vutr.cz
 *           Du¹an Kovaèiè, xkovac21, xkovac21@stud.fit.vutbr.cz
 *
 * Encoding: ISO-8859-2
 *
 * Description:
 */


#include <cmath>                                            //rand(),sqrt()
#include <cstdlib>
#include <climits>                                          //ULONG_MAX, RAND_MAX
#include <time.h>

#ifndef _SGEN_H
#define	_SGEN_H


/**
 * Trida generatoru nahodnych pseudonahodnych cisel
 */
class sGen
{
   public:
      sGen(){ srand(time(NULL)); };                         //konstruktor - nastaveni aby random zacal vdzy jinak
      ~sGen(){};                                            //destruktor

      double expGen(double lambda);                         //generator exponencialniho rozlozeni
      double uniformGen(double a , double b);               //generator uniformiho rozlozeni
      double randomGen();                                   //rovnomerny generator nahodnych cisel
      int randomGen(int range);                             //rovnomerny generator v rozsahi 0-range
      int randomGen(int rangeMin, int rangeMax);            //rovnomerny generator v rozsahi rangeMin-rangeMax
      double normalGen(double mu, double lambda);           //generator rovnomerneho rozlozeni
      int poissonGen(double lambda);                        //generator poissonova rozlozeni
};



#endif	/* _SGEN_H */

