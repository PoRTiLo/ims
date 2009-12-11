/*
 * --------------IMS-----------------
 *
 * Project:  Implementace diskr. simulátoru zalo¾eného na øízení UDÁLOSTMI (opak procesnì orientovaného pøístupu)
 * File:     stat.cc
 * Author:   Jaroslav Sendler, xsendl00, xsendl00@stud.fit.vutr.cz
 *           Du¹an Kovaèiè, xkovac21, xkovac21@stud.fit.vutbr.cz
 *
 * Encoding: ISO-8859-2
 *
 * Description:
 */

#include <iostream>
#include "stat.h"
#include <cmath>

using namespace std;


/**
 * Konstruktor se jmenem statistyky
 *
 * @param[in] *name
 */
Stat::Stat(const char * name) {

  sName = name;
  sX = 0;
  sXX = 0;
  sMin = 0;
  sMax = 0;
  sCount = 0;
}


/**
 * Konstruktor
 */
Stat::Stat() {
  sInit();
}


/**
 * Destruktor
 */
Stat::~Stat() {}


/**
 * Inicializace a vymazani statistiky
 */
void Stat::sInit() {
  sX = 0;
  sXX = 0;
  sMin = 0;
  sMax = 0;
  sCount = 0;
}


/**
 * Kontrola zda je prazdne
 *
 * @return true - je prazdny, false - neni prazdny
 */
bool Stat::sIsEmpty() const {
  if( sCount > 0 )
      return false;

  return true;
}


/**
 * Prida data do statistky
 *
 * @param data
 */
void Stat::sAddData(double data) {

    sCount++;
    sX += data;
    sXX += sX*sX;

    if( sCount == 1 )
    {
        sMin = data;
        sMax = data;
    }
    else
    {
       if( data < sMin )
           sMin = data;
       if( data > sMax )
           sMax = data;
    }
}


/**
 * Vytiskne obsah statistiky
 */
void Stat::sShow() const {

    cout<< "zorazi data staticstiky...."<< sX <<","<< "atd...dodelat"<<endl;
}


/**
 * Vrati pocet prvku ve statistice
 *
 * @return count
 */
unsigned long Stat::sGetCount() const {

    return sCount;
}


/**
 * Vrati nejmenis prvek statistiky
 *
 * @return <double> sMin
 */
double Stat::sGetMin() const {

    if( sIsEmpty() )
        cout<< "chyba ve fci sGetMin" << endl;
    return sMin;
}


/**
 * Vrati nejvetsi prvek statistiky
 *
 * @return <double> sMax
 */
double Stat::sGetMax() const {

    if( sIsEmpty() )
        cout<< "chyba ve fsi sGetMax" << endl;
    return sMax;
}


/**
 * Vrati soucet prvku ve statistice
 *
 * @return <double> sX
 */
double Stat::sGetSX() const {

    return sX;
}


/**
 * Vrati soucet prvku na druhou ve statistice
 *
 * @return <double> sXX
 */
double Stat::sGetSXX() const {

    return sXX;
}


/**
 * Vypocet prumeru
 *
 * @return <double> mean
 */
double Stat::meanValue() const {

    if( sIsEmpty() )
    {
        cout << "chyba ve fci meanValue" <<endl;
        return 0.0;        
    }

    return sX/sCount;
}


/**
 * Smerodatna odchylka
 *
 * @return <double>
 */
double Stat::standardDev() const {

    if( sCount < 2 )
        cout << "Chyba ve fci standatdDev, malo poctu pro statistiku" << endl;
    
    return sqrt( fabs( (sXX - sX*sX/sCount) / (sCount - 1) ) );
}
