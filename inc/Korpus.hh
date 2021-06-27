#ifndef KORPUS_HH
#define KORPUS_HH
   /*!
    * \file Plik zawiera definicje klasy Korpus
    *        
    */
#include <iostream>
#include "BrylaWzorcowa.hh"
   /*!
    * \brief Klasa Korpus
    *        Zawiera wspolrzedne polozenia korpusa, kat obrota i wektor translacji      
    */
class Korpus: public BrylaGeometryczna
{

public:
   /*!
    * \brief Wektor polozenia korpusa
    *        
    */
    Vector3D Poloz;
   /*!
    * \brief Kat obrotu korpusa
    *        
    */
    double KatObrotu;
   /*!
    * \brief Konstruktor bezparametryczny dla klasy korpusa
    *        
    */
    Korpus(){Poloz = {0, 0, 0}; KatObrotu = 0; TYP = Drn;};
   /*!
    * \brief Metoda transformuje wspolrzedne wektora korpusa do ukladu drona
    *        
    */
    void TransfDoUkl(Vector3D const PolozDrona, double const KatObrotaDrona){Poloz = PolozDrona; KatObrotu = KatObrotaDrona;};
   /*!
    * \brief Metoda zwraca wektor polozenia korpusa
    *        
    */
    Vector3D ZwrotPoloz() {return Poloz;};
};


#endif