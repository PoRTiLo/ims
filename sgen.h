/*
 * --------------IMS-----------------
 *
 * Project:  Implementace diskr. simul�toru zalo�en�ho na ��zen� UD�LOSTMI (opak procesn� orientovan�ho p��stupu)
 * File:     sgen.h
 * Author:   Jaroslav Sendler, xsendl00, xsendl00@stud.fit.vutr.cz
 *           Du�an Kova�i�, xkovac21, xkovac21@stud.fit.vutbr.cz
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

