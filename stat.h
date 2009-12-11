/*
 * --------------IMS-----------------
 *
 * Project:  Implementace diskr. simulátoru zalo¾eného na øízení UDÁLOSTMI (opak procesnì orientovaného pøístupu)
 * File:     stat.h
 * Author:   Jaroslav Sendler, xsendl00, xsendl00@stud.fit.vutr.cz
 *           Du¹an Kovaèiè, xkovac21, xkovac21@stud.fit.vutbr.cz
 *
 * Encoding: ISO-8859-2
 *
 * Description:
 */


#ifndef _STAT_H
#define	_STAT_H

class Stat {
    
protected:
    double sX;                            // soucet hodnot
    double sXX;                           // soucet na druhou
    double sMin;                          // minimalni hodnota
    double sMax;                          // maximalni hodnota
    unsigned long sCount;                 // pocet hodnot
    const char* sName;
    
public:
    Stat();
    Stat(const char* name);
    ~Stat();
    virtual void sInit();
    bool sIsEmpty() const;
    void sAddData(double data);
    void sShow() const;
    unsigned long sGetCount() const;
    double sGetMin() const;
    double sGetMax() const;
    double sGetSX() const;
    double sGetSXX() const;
    double meanValue() const;
    double standardDev() const;
};

#endif	/* _STAT_H */

