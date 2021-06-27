#ifndef DRON_HH
#define DRON_HH

   /*!
    * \file Plik zawiera definicje klasy Dron
    *
    */

#define PROMIEN 15

#include <iostream>
#include "BrylaWzorcowa.hh"
#include "Korpus.hh"
#include "Rotor.hh"
#include <unistd.h>
#include "Vector3D.hh"
#include "Obiekt.hh"
#include <memory>
#include "lacze_do_gnuplota.hh"

   /*!
    * \brief Klasa Dron
    *        Tworzy drona z klasy Rotor i Korpus. Zawiera wspolrzedne polozenia drona i kata obrotu
    */

class Dron: public ObiektScena 
{
   /*!
    * \brief Rotory drona
    *        
    */
    Rotor Rotory[4];

public:
   /*!
    * \brief Korpus drona
    *        
    */
    Korpus Korp;
   /*!
    * \brief Polozenie drona
    *        
    */
    Vector3D Poloz;
   /*!
    * \brief Kat obrotu drona
    *        
    */
    double KatObrotu;
   /*!
    * \brief Metoda, ktora buduje drona
    *        
    */
    bool Oblicz_i_zapisz_WspDrona(int adresDrona);
   /*!
    * \brief Metoda, ktora buduje korpus
    *        
    */
    bool Oblicz_i_zapisz_WspKorpusa(int adresDrona);
   /*!
    * \brief Metoda, ktora buduje rotory
    *        
    */
    bool Oblicz_i_zapisz_WspRotora(Rotor& Rot, int adres, int const adresDrona);
   /*!
    * \brief Metoda dodawania trasy przelotu
    *        
    */
    bool DodajTrasePrzelotu(double KatObrot, double Dlugosc, PzG::LaczeDoGNUPlota &Lacze);
   /*!
    * \brief Metoda modyfikuje trase przelotu
    *        Ta metoda zmienia polozenie koncowe trasy przeliota przy kolizji
    */
    bool ModyfikujTrasePrzelotu(Vector3D& PolozPoczatkowe, double KatObrot, double Dlugosc, PzG::LaczeDoGNUPlota &Lacze);
   /*!
    * \brief Metoda wykonuje animacje lotu drona
    *        
    */
    bool WykonajLot(double Dlug, double KatObr, PzG::LaczeDoGNUPlota &Lacze, int const adresDrona, std::vector<std::shared_ptr<ObiektScena>> LObiektow, Vector3D& PolozPocztkowe);
    /*!
    * \brief Metoda sprawdza, czy dron zejdzie na przeszkode
    *        
    */
    bool Kolizja(double KatObr, PzG::LaczeDoGNUPlota &Lacze, int const adresDrona, std::vector<std::shared_ptr<ObiektScena>> LObiektow, Vector3D& PolozPoczatkowe);
   /*!
    * \brief Metoda zwraca polozenie drona
    *        
    */
    Vector3D& ZwrotPoloz() {return Poloz;};
   /*!
    * \brief Metoda zwraca nazwe finalna korpusu drona
    *        
    */
    std::string ZwrotNazwaFinalna() {return Korp.NazwaBrylaFinalna;};
   /*!
    * \brief Metoda zwraca TYP obiektu
    *        
    */
    TypObiektu ZwrotTypu() {return Korp.TYP;};
   /*!
    * \brief Metoda potrzebna, aby dodac trase przelotu
    *        
    */
    void Trasa(double KatObrotu, double Dlugosc, PzG::LaczeDoGNUPlota &Lacze) {DodajTrasePrzelotu(KatObrotu, Dlugosc, Lacze);};
   /*!
    * \brief Metoda potrzebna, aby wykonac lot drona
    *        
    */
    void Lot(double Dlug, double KatObr, PzG::LaczeDoGNUPlota &Lacze, int const adresDrona, std::vector<std::shared_ptr<ObiektScena>> LObiektow, Vector3D& PolozPoczatkowe){WykonajLot(Dlug, KatObr, Lacze, adresDrona, LObiektow, PolozPoczatkowe);};
};

#endif