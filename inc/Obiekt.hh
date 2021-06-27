#ifndef OBIEKT_HH
#define OBIEKT_HH
   /*!
    * \file Plik zawiera definicje klasy ObiektScena
    *        
    */
#include <iostream>
#include "Vector3D.hh"
#include "BrylaWzorcowa.hh"
#include "lacze_do_gnuplota.hh"
#include <memory>

   /*!
    * \brief Klasa ObiektSceny
    *        Z tej klasy dziedzicza klasy pochodne, ktore potrzebne, aby zidentyfikowac kolizji
    */
class ObiektScena
{


public:
   /*!
    * \brief Metoda wirtualna zwraca wektor polozenia
    *        
    */
    virtual Vector3D& ZwrotPoloz() = 0;
   /*!
    * \brief Metoda wirtualna zwraca nazwe pliku finalnego
    *        
    */
    virtual std::string ZwrotNazwaFinalna() = 0;
   /*!
    * \brief Metoda wirtualna zwraca TYP obiektu
    *        
    */
    virtual enum TypObiektu ZwrotTypu() = 0;
   /*!
    * \brief Metoda wirtualna dla klasy drona. 
    *        Wywoluje metode DodajTrasePrzelotu
    */
    virtual void Trasa(double KatObrotu, double Dlugosc, PzG::LaczeDoGNUPlota &Lacze) = 0;
   /*!
    * \brief Metoda wirtualna dla klasy drona.
    *        Wywoluje metode WykonajLot
    */
    virtual void Lot(double, double, PzG::LaczeDoGNUPlota &, int const, std::vector<std::shared_ptr<ObiektScena>>, Vector3D& PolozPoczatkowe) = 0;

};

#endif