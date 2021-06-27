#ifndef SCENA_HH
#define SCENA_HH
   /*!
    * \file Plik zawiera definicje klasy Scena
    *        
    */
#include <iostream>
#include "Dron.hh"
#include "GoreZOstrymSzczytem.hh"
#include "GoreZDlugaGrania.hh"
#include "Plaskowyz.hh"
#include "Obiekt.hh"
#include <memory>
   /*!
    * \brief Klasa Scena
    *        Ta klasa pokazuje scene, po ktorej dwa drony moge wedrowac
    *        Ta scena zawiera przeszkody
    */
class Scena{

private:

    PzG::LaczeDoGNUPlota Lacze;
   /*!
    * \brief Vektor obiektow sceny
    *        
    */
    std::vector<std::shared_ptr<ObiektScena>> LObiektow;
   /*!
    * \brief Numer pliku dla przeszkod
    *        
    */
    int NumerObiektu = 0;

public:
   /*!
    * \brief Metoda, ktora wyswietla menu
    *        
    */
    void Menu();
   /*!
    * \brief Glowna metoda calego programu
    *        
    */
    void UzyjAktywnegoDrona();
   /*!
    * \brief Metoda dla wyboru aktywnego drona
    *        
    */
    int WezAktywnegoDrona(int const AktywnyDron);
   /*!
    * \brief Metoda buduje nowa przeskode(Gora z ostrym szczytem)
    *        
    */
    bool TworzGoreZOstrymSzczytem(PzG::LaczeDoGNUPlota &Lacze);
   /*!
    * \brief Metoda buduje nowa przeszkode(Gora z dluga grania)
    *        
    */
    bool TworzGoreZDlugaGrania(PzG::LaczeDoGNUPlota &Lacze);
   /*!
    * \brief Metoda buduje nowa przeszkode(Plaskowyz)
    *        
    */
    bool TworzPlaskowyz(PzG::LaczeDoGNUPlota &Lacze);
   /*!
    * \brief Metoda buduje poczatkowe przeszkody(Gora z ostrym szczytem)
    *        
    */
    bool TworzPaczGoraZOstrymSzczytem(PzG::LaczeDoGNUPlota &Lacze);
   /*!
    * \brief Metoda buduje poczatkowe przeszkody(Gora z dluga grania)
    *        
    */
    bool TworzPaczGoraZDlugaGrania(PzG::LaczeDoGNUPlota &Lacze);
   /*!
    * \brief Metoda buduje poczatkowe przeszkody(Plaskowyz)
    *        
    */
    bool TworzPaczPlaskowyz(PzG::LaczeDoGNUPlota &Lacze, Vector3D &Polozeni, Vector3D &Skal);
};

#endif