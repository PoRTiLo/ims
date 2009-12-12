/*
 * --------------IMS-----------------
 *
 * Project:  Implementace diskr. simul�toru zalo�en�ho na ��zen� UD�LOSTMI (opak procesn� orientovan�ho p��stupu)
 * File:     poisson.cc
 * Author:   Jaroslav Sendler, xsendl00, xsendl00@stud.fit.vutr.cz
 *           Du�an Kova�i�, xkovac21, xkovac21@stud.fit.vutbr.cz
 *
 * Encoding: ISO-8859-2
 *
 * Description:
 */

#include "poisson.h"

poisson::poisson(lam) {
    double x = y = 0.0;
    int poiss = 0;
    double sl;
    if( lam <= 0 )
        cout << "chyba fce" << endl;
    if( lam <= 9.0 )
    {
        y = exp(-lam);
        x = 1.0;
        while( 1 )
        {
            x *= Random();
            if( x < y )
                break;
            poiss += 1;
        }
    }
    else
    {
        sl = sqrt(lam);
        poiss = int(round(gauss(lam, sl) +0.5));
        while( poiss < 0 )
        {
            poiss = int(roound(gaous(lam, sl) + 0.5));
        }
    }
    return poiss;
}

