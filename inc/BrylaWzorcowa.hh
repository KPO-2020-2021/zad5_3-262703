#ifndef BRYLAWZORCOWA_HH
#define BRYLAWZORCOWA_HH
   /*!
    * \file Plik zawiera definicje klasy BrylaGeometryczna
    *        
    */
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include "Vector3D.hh"
   /*!
    * \brief Pokazuje TYP Bryly
    *        
    */
enum TypObiektu {GoraZDlugaGran, GoraZOstrymSzczyt, Plaskow, Drn};

   /*!
    * \brief Klasa BrylaGeometryczna
    *        Z tej klasy dziedzicza klasy pochodne
    *        Wprowadzi pojecie Bryly Geometrycznej
    */
class BrylaGeometryczna
{    

public:
   /*!
    * \brief Typ obiektu
    *        
    */
    TypObiektu TYP;
   /*!
    * \brief Nazwa pliku, do ktorego odbywa sie nagranie wspolrzednych punktow bryl
    *        
    */
    std::string NazwaBrylaFinalna;
   /*!
    * \brief Nazwa pliku, z ktorego pobierane sa wspolrzedne punktow
    *        
    */
    std::string NazwaBrylaWzorc;
   /*!
    * \brief Wektor skaly
    *        
    */
    Vector3D Skala;
   /*!
    * \brief Metoda skaluje punkty z pliku wzorcowego
    *        
    */
    Vector3D Skaluj(Vector3D& Wierz, double KatObrotu, Vector3D VectorTransl);
   /*!
    * \brief Glowna metoda Drona
    *        Bierze punkty z pliku wzorcowego
    *        Modyfikuje je za pomoca metody Skaluj
    *        Zapisuje punkty do pliky finalnego
    */
    std::string& WezNazwePliku_Bryla(double KatObrotu, Vector3D VectorTransl);
   /*!
    * \brief Glowna metoda Przeszkody
    *        Bierze punkty z pliku wzorcowego
    *        Modyfikuje je za pomoca metody Skaluj
    *        Zapisuje punkty do pliky finalnego       
    */
    std::string& WezNazwePliku_BrylaObiekt(Vector3D VectorTransl);
   /*!
    * \brief Deformacja dla gory z ostrym szczytem
    *        
    */
    Vector3D TransfGoraZOstrymSzszytem(Vector3D& Wierz);
   /*!
    * \brief Deformacja dla gory z dluga grania
    *        
    */
    Vector3D TransfGoraZDlugaGrania(Vector3D& Wierz);
};



#endif