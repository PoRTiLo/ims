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


#include <cmath>
#include <cstdlib>
#include <climits>

#ifndef _SGEN_H
#define	_SGEN_H



class sGen
{
   public:
      sGen(){};
      ~sGen(){};

      double expGen(double lambda);
      double uniformGen(double a , double b);
      double randomGen();
      int randomGen(int range);
      double normalGen(double mu, double lambda);
      int poissonGen(double lambda);
};



#endif	/* _SGEN_H */

