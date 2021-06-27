#ifndef PLASKOWYZ_HH
#define PLASKOWYZ_HH
   /*!
    * \file Plik zawiera definicje klasy Plaskowyz
    *        
    */
#include <iostream>
#include "BrylaWzorcowa.hh"
#include "Obiekt.hh"
   /*!
    * \brief Klasa Plaskowyz
    *        Zawiera wspolrzedne polozenia danej przeszkody
    */
class Plaskowyz: public BrylaGeometryczna, public ObiektScena
{

public:
   /*!
    * \brief Wektor polozenia Plaskowyza 
    *        
    */
    Vector3D Poloz;
   /*!
    * \brief Konstruktor bezparametryczny 
    *        
    */
    Plaskowyz(){Poloz = {0, 0, 0}; Skala = {0, 0, 0}; TYP = Plaskow; NazwaBrylaWzorc = "../bryly_wzorcowe/szescian_na_powierzchni.dat";};
   /*!
    * \brief Konstruktor parametryczny
    *        
    */
    Plaskowyz(Vector3D const Polozenie, Vector3D const Skal) {Poloz = Polozenie; Skala = Skal; TYP = Plaskow; NazwaBrylaWzorc = "../bryly_wzorcowe/szescian_na_powierzchni.dat";};
   /*!
    * \brief Metoda zwraca wektor polozenia
    *        
    */
    Vector3D& ZwrotPoloz() {return Poloz;};
   /*!
    * \brief Metoda zwraca nazwe pliku finalnego
    *        
    */
    std::string ZwrotNazwaFinalna() {return NazwaBrylaFinalna;};
   /*!
    * \brief Metoda zwraca typ obiektu
    *        
    */
    TypObiektu ZwrotTypu() {return TYP;};
   /*!
    * \brief Dana metoda nie jest potrzebna dla danego klasa
    *        
    */
    void Trasa(double, double, PzG::LaczeDoGNUPlota &) {};
   /*!
    * \brief Dana metoda nie jest potrzebna dla danego klasa
    *        
    */
    void Lot(double, double, PzG::LaczeDoGNUPlota &, int const, std::vector<std::shared_ptr<ObiektScena>>, Vector3D& ) {};
};


#endif