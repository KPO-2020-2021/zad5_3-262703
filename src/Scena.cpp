#include "Scena.hh"

void Scena::Menu()
{
    std::cout << "a - wybierz aktywnego drona" << std::endl;
    std::cout << "p - zadaj parametry przelotu" << std::endl;
    std::cout << "u - usun obiekt powiezchni" << std::endl;
    std::cout << "d - dodaj element powierzchni" << std::endl;
    std::cout << "m - wyswietl menu" << std::endl << std::endl;
    std::cout << "k - koniec dzialania programu" << std::endl;
}

void Scena::UzyjAktywnegoDrona()
{
    Lacze.DodajNazwePliku("../bryly_wzorcowe/plaszczyzna.dat");
    
    Lacze.DodajNazwePliku("../datasets/PlikWlasciwy_Dron1_Korpus.dat");//NazwaBrylaFinalna.c_str();
    Lacze.DodajNazwePliku("../datasets/PlikWlasciwy_Dron1_Rotor1.dat");
    Lacze.DodajNazwePliku("../datasets/PlikWlasciwy_Dron1_Rotor2.dat");
    Lacze.DodajNazwePliku("../datasets/PlikWlasciwy_Dron1_Rotor3.dat");
    Lacze.DodajNazwePliku("../datasets/PlikWlasciwy_Dron1_Rotor4.dat");  
    
    Lacze.DodajNazwePliku("../datasets/PlikWlasciwy_Dron2_Korpus.dat");
    Lacze.DodajNazwePliku("../datasets/PlikWlasciwy_Dron2_Rotor1.dat");
    Lacze.DodajNazwePliku("../datasets/PlikWlasciwy_Dron2_Rotor2.dat");
    Lacze.DodajNazwePliku("../datasets/PlikWlasciwy_Dron2_Rotor3.dat");
    Lacze.DodajNazwePliku("../datasets/PlikWlasciwy_Dron2_Rotor4.dat");  

  
    Lacze.ZmienTrybRys(PzG::TR_3D);
    Lacze.Inicjalizuj();  // Tutaj startuje gnuplot.

    Lacze.UstawZakresX(0, 200);
    Lacze.UstawZakresY(0, 200);
    Lacze.UstawZakresZ(0, 120);
  
    double KatDl, Dlug;
    Dron Dron_1, Dron_2;
  
    Dron_1.KatObrotu = 0;
    Dron_1.Poloz = {20, 30, 2};
    Dron_1.Oblicz_i_zapisz_WspDrona(0);
    LObiektow.push_back(std::make_shared<Dron>(Dron_1));
    
    Dron_2.KatObrotu = 0;
    Dron_2.Poloz = {100, 70, 2};
    Dron_2.Oblicz_i_zapisz_WspDrona(1);
    LObiektow.push_back(std::make_shared<Dron>(Dron_2));
    
    
    Vector3D Poloz1 = {20, 130, 0}, Poloz2 = {130, 90, 0};
    Vector3D Skal1 = {30, 20, 70}, Skal2 = {30, 70, 20};
    TworzPaczGoraZOstrymSzczytem(Lacze);
    TworzPaczGoraZDlugaGrania(Lacze);
    TworzPaczPlaskowyz(Lacze, Poloz1, Skal1);
    TworzPaczPlaskowyz(Lacze, Poloz2, Skal2);

    Lacze.Rysuj();
    
    char WyborMenu = ' ';
    int AktywnyDron = 0;
    int inde = 1;
    Vector3D PolozPoczatkowe;
    while (WyborMenu != 'k')
    {
        std::cout << "Polozenie Drona aktywnego (x, y):  " << LObiektow[AktywnyDron]->ZwrotPoloz()[0] << " " << LObiektow[AktywnyDron]->ZwrotPoloz()[1] << std::endl; 
        std::cout << "Twoj wybor <m - menu> ";
        std::cin >> WyborMenu;
        switch (WyborMenu)
        {
            case 'a':
                AktywnyDron = WezAktywnegoDrona(AktywnyDron);
                break;
            case 'p':
                std::cout << "Podaj kierunek lotu (kat w stopniach)> ";
                std::cin >> KatDl;
                std::cout << std::endl;
                std::cout << "                   Podaj dlugosc lotu> ";
                std::cin >> Dlug;
                std::cout << "Nacisnij ENTER, aby pokazac sciezke przelotu drona " << std::flush;
                std::cin.ignore(10000,'\n');
                LObiektow[AktywnyDron]->Trasa(KatDl, Dlug, Lacze);
                Lacze.Rysuj();
                std::cout << "Nacisnij ENTER, aby wykonac animacje lotu drona" << std::flush;
                std::cin.ignore(10000,'\n');
                PolozPoczatkowe = LObiektow[AktywnyDron]->ZwrotPoloz();
                LObiektow[AktywnyDron]->Lot(Dlug, KatDl, Lacze, AktywnyDron, LObiektow, PolozPoczatkowe);
                std::cout << std::endl << "Nacisnij ENTER, aby usunac sciezke ... " << std::flush;
                std::cin.ignore(10000,'\n');
                Lacze.UsunNazwePliku("../datasets/trasa_przelotu.dat");
                Lacze.Rysuj();
                break;
            case 'm':
                Menu();
                break;
            case 'd':
                int NumerElementu;
                std::cout << "Wybierz rodzaj powiezchniowego elementu" << std::endl;
                std::cout << "1 - Gora z ostrym szczytem" << std::endl;
                std::cout << "2 - Gora z dluga grania" << std::endl;
                std::cout << "3 - Plaskowyz" << std::endl;
                std::cout << "Wprowadz numer typu elementu>";
                std::cin >> NumerElementu;
                if (NumerElementu >= 0 && NumerElementu < 4)
                {
                    if (NumerElementu == 1) {TworzGoreZOstrymSzczytem(Lacze);}
                    if (NumerElementu == 2) {TworzGoreZDlugaGrania(Lacze);}
                    if (NumerElementu == 3) {TworzPlaskowyz(Lacze);} 
                }
                else
                {
                    std::cerr << "Nie ma takeigo obiektu!" << std::endl;
                    break;
                }
                Lacze.Rysuj();
                break;
            case 'u':
                std::cout << "Wybierz element powierzchni do usuniecia:" << std::endl;
                for (std::vector<std::shared_ptr<ObiektScena>>::iterator iter = LObiektow.begin(); iter != LObiektow.end(); ++iter)
                {
                    switch((*iter)->ZwrotTypu())
                    {
                        case GoraZOstrymSzczyt:
                            GoraZOstrymSzczytem* Wsk1;
                            Wsk1 = (GoraZOstrymSzczytem*) iter->get();
                            std::cout << inde << " - (" << Wsk1->Poloz[0] << ", " << Wsk1->Poloz[1] << ") Gora z ostrym szcytem" << std::endl;
                            inde++;
                            break;
                        case GoraZDlugaGran:
                            GoraZDlugaGrania* Wsk2;
                            Wsk2 = (GoraZDlugaGrania*) iter->get();
                            std::cout << inde << " - (" << Wsk2->Poloz[0] << ", " << Wsk2->Poloz[1] << ") Gora z dluga grania" << std::endl;
                            inde++;
                            break;
                        case Plaskow:
                            Plaskowyz* Wsk3;
                            Wsk3 = (Plaskowyz*) iter->get();
                            std::cout << inde << " - (" << Wsk3->Poloz[0] << ", " << Wsk3->Poloz[1] << ") Plaskowyz" << std::endl;
                            inde++;
                            break;
                        case Drn:
                            break;
                    }    
                }
                inde = 1;
                std::cout << "Podaj numer elementu>";
                unsigned int ElementDousun;
                std::cin >> ElementDousun;
                if (ElementDousun > 0 && ElementDousun <= LObiektow.size() - 2)
                {
                    ElementDousun++;
                    Lacze.UsunNazwePliku(LObiektow[ElementDousun]->ZwrotNazwaFinalna());
                    LObiektow.erase(LObiektow.begin() + ElementDousun);
                    Lacze.Rysuj();
                }
                else
                {
                    std::cerr << "Blad! Nie ma takiego elementu!" << std::endl;
                }
                break;
            case 'k':
                std::cout << "Koniec dzialania programu" << std::endl;
                break;
            default:
                std::cout << "Nie ma takiej opcji!" << std::endl;
                break;
        }
    }
}

int Scena::WezAktywnegoDrona(int const AktywnyDron)
{
    std::cout << "Wybor aktywnego drona" << std::endl << std::endl;
    for (int i = 1; i <= 2; i++)
    {
        std::cout << i << " - Polozenie (x, y):  " << LObiektow[i-1]->ZwrotPoloz()[0] << " " << LObiektow[i-1]->ZwrotPoloz()[1];
        if  ((i-1) == AktywnyDron) {std::cout << " <-- Dron aktywny"; }
        std::cout << std::endl;
    }
    std::cout << std::endl << "Wprowadz numer aktywnego drona> ";
    int adres;
    std::cin >> adres;
    std::cout << std::endl;
    return adres - 1;

}

bool Scena::TworzGoreZOstrymSzczytem(PzG::LaczeDoGNUPlota &Lacze)
{
    GoraZOstrymSzczytem Gora;
    Vector3D Skala, Polozen;
    std::cout << "Wprowadz polozenie (x i y) dla nowego obiektu sceny" << std::endl;
    std::cin >> Polozen[0] >> Polozen[1];
    std::cout << "Wprowadz skale wedlug OX, OY i OZ" << std::endl;
    std::cin >> Skala;
    Gora = GoraZOstrymSzczytem(Polozen, Skala);
    Gora.NazwaBrylaFinalna = "../datasets/" + std::to_string(NumerObiektu) + ".dat";
    Gora.NazwaBrylaFinalna = Gora.WezNazwePliku_BrylaObiekt(Gora.Poloz);
    LObiektow.push_back(std::make_shared<GoraZOstrymSzczytem>(Gora));
    Lacze.DodajNazwePliku(Gora.NazwaBrylaFinalna.c_str());
    NumerObiektu++;
    return true;
}

bool Scena::TworzGoreZDlugaGrania(PzG::LaczeDoGNUPlota &Lacze)
{
    GoraZDlugaGrania Gora;
    Vector3D Skala, Polozen;
    std::cout << "Wprowadz polozenie (x i y) dla nowego obiektu sceny" << std::endl;
    std::cin >> Polozen[0] >> Polozen[1];
    std::cout << "Wprowadz skale wedlug OX, OY i OZ" << std::endl;
    std::cin >> Skala;
    Gora = GoraZDlugaGrania(Polozen, Skala);
    Gora.NazwaBrylaFinalna = "../datasets/" + std::to_string(NumerObiektu) + ".dat";
    Gora.NazwaBrylaFinalna = Gora.WezNazwePliku_BrylaObiekt(Gora.Poloz);
    LObiektow.push_back(std::make_shared<GoraZDlugaGrania>(Gora));
    Lacze.DodajNazwePliku(Gora.NazwaBrylaFinalna.c_str());
    NumerObiektu++;
    return true;
}

bool Scena::TworzPlaskowyz(PzG::LaczeDoGNUPlota &Lacze)
{
    Plaskowyz Gora;
    Vector3D Skala, Polozen;
    std::cout << "Wprowadz polozenie (x i y) dla nowego obiektu sceny" << std::endl;
    std::cin >> Polozen[0] >> Polozen[1];
    std::cout << "Wprowadz skale wedlug OX, OY i OZ" << std::endl;
    std::cin >> Skala;
    Gora = Plaskowyz(Polozen,Skala);
    Gora.NazwaBrylaFinalna = "../datasets/" + std::to_string(NumerObiektu) + ".dat";
    Gora.NazwaBrylaFinalna = Gora.WezNazwePliku_BrylaObiekt(Gora.Poloz);
    LObiektow.push_back(std::make_shared<Plaskowyz>(Gora));
    Lacze.DodajNazwePliku(Gora.NazwaBrylaFinalna.c_str());
    NumerObiektu++;
    return true;
}

bool Scena::TworzPaczGoraZOstrymSzczytem(PzG::LaczeDoGNUPlota &Lacze)
{
    GoraZOstrymSzczytem Gora;
    Gora.Poloz = {150, 30, 0};
    Gora.Skala = {20, 20, 60};
    Gora = GoraZOstrymSzczytem(Gora.Poloz, Gora.Skala);
    Gora.NazwaBrylaFinalna = "../datasets/" + std::to_string(NumerObiektu) + ".dat";
    Gora.NazwaBrylaFinalna = Gora.WezNazwePliku_BrylaObiekt(Gora.Poloz);
    LObiektow.push_back(std::make_shared<GoraZOstrymSzczytem>(Gora));
    Lacze.DodajNazwePliku(Gora.NazwaBrylaFinalna.c_str());
    NumerObiektu++;
    return true;
}

bool Scena::TworzPaczGoraZDlugaGrania(PzG::LaczeDoGNUPlota &Lacze)
{
    GoraZDlugaGrania Gora;
    Gora.Poloz = {70, 40, 0};
    Gora.Skala = {40, 20, 50};
    Gora = GoraZDlugaGrania(Gora.Poloz, Gora.Skala);
    Gora.NazwaBrylaFinalna = "../datasets/" + std::to_string(NumerObiektu) + ".dat";
    Gora.NazwaBrylaFinalna = Gora.WezNazwePliku_BrylaObiekt(Gora.Poloz);
    LObiektow.push_back(std::make_shared<GoraZDlugaGrania>(Gora));
    Lacze.DodajNazwePliku(Gora.NazwaBrylaFinalna.c_str());
    NumerObiektu++;
    return true;
}

bool Scena::TworzPaczPlaskowyz(PzG::LaczeDoGNUPlota &Lacze, Vector3D &Polozeni, Vector3D &Skal)
{
    Plaskowyz Gora;
    Gora.Poloz = Polozeni;
    Gora.Skala = Skal;
    Gora = Plaskowyz(Gora.Poloz, Gora.Skala);
    Gora.NazwaBrylaFinalna = "../datasets/" + std::to_string(NumerObiektu) + ".dat";
    Gora.NazwaBrylaFinalna = Gora.WezNazwePliku_BrylaObiekt(Gora.Poloz);
    LObiektow.push_back(std::make_shared<Plaskowyz>(Gora));
    Lacze.DodajNazwePliku(Gora.NazwaBrylaFinalna.c_str());
    NumerObiektu++;
    return true;
}