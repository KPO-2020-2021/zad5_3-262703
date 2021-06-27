#ifndef ROTOR_HH
#define ROTOR_HH
   /*!
    * \file Plik zawiera definicje klasy Rotor
    *        
    */
#include <iostream>
#include "BrylaWzorcowa.hh"
   /*!
    * \brief Klasa Rotor
    *        Zawiera wspolrzedne polozenia rotora, kat obrota i wektor translacji
    */
class Rotor: public BrylaGeometryczna
{

public:
   /*!
    * \brief Wektor polozenia rotora 
    *        
    */
    Vector3D Poloz;
   /*!
    * \brief Wektor translacji rotora
    *        
    */
    Vector3D PolozTransl;
   /*!
    * \brief Kat obrota rotora
    *        
    */
    double KatObrotu;
   /*!
    * \brief Transformuje wektor polozenia rotora do ukladu drona
    *        
    */
    void TransfDoUkl(Vector3D const PolozDrona){Poloz[0] = PolozDrona[0] + PolozTransl[0];
                                                Poloz[1] = PolozDrona[1] + PolozTransl[1];
                                                Poloz[2] = PolozDrona[2] + PolozTransl[2] - 2;};

};


#endif