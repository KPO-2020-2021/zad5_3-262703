#include "Dron.hh"

bool Dron::Oblicz_i_zapisz_WspDrona(int const adresDrona)
{
    static double KatObrotuRotora = 0;
    Rotory[0].PolozTransl = {5, 4, 5};
    Rotory[1].PolozTransl = {5, -4, 5};
    Rotory[2].PolozTransl = {-5, 4, 5};
    Rotory[3].PolozTransl = {-5, -4, 5};
    Rotory[0].KatObrotu = -KatObrotuRotora;
    Rotory[1].KatObrotu = KatObrotuRotora;
    Rotory[2].KatObrotu = KatObrotuRotora;
    Rotory[3].KatObrotu = -KatObrotuRotora;
    if (!Oblicz_i_zapisz_WspKorpusa(adresDrona)) return false;
    for (int adres = 0; adres < 4; ++adres)
    {
        if (!Oblicz_i_zapisz_WspRotora(Rotory[adres], adres, adresDrona)) return false;

    }
    KatObrotuRotora += 10;
    return true;
}

bool Dron::Oblicz_i_zapisz_WspKorpusa(int adresDrona)
{
    Korp.Skala = {10, 8, 4};
    Korp.NazwaBrylaWzorc = "../bryly_wzorcowe/szescian.dat";
    Korp.NazwaBrylaFinalna = "../datasets/PlikWlasciwy_Dron" + std::to_string(adresDrona + 1) + "_Korpus.dat";
    Korp.TransfDoUkl(Poloz, KatObrotu);
    Korp.NazwaBrylaFinalna = Korp.WezNazwePliku_Bryla(Korp.KatObrotu, Korp.Poloz);
    return true;
}

bool Dron::Oblicz_i_zapisz_WspRotora(Rotor& Rot, int adres, int adresDrona)
{
    Rot.Skala = {8, 8, 2};
    Rot.NazwaBrylaWzorc = "../bryly_wzorcowe/graniastoslup6.dat";
    Rot.NazwaBrylaFinalna = "../datasets/PlikWlasciwy_Dron" + std::to_string(adresDrona + 1) +"_Rotor" + std::to_string(adres+1) + ".dat";
    Rot.TransfDoUkl(Poloz);
    Rot.NazwaBrylaFinalna = Rot.WezNazwePliku_Bryla(Rot.KatObrotu, Rot.Poloz);
    return true;
}

bool Dron::DodajTrasePrzelotu(double KatObrot, double Dlugosc, PzG::LaczeDoGNUPlota &Lacze)
{
    std::ofstream StrmWyj("../datasets/trasa_przelotu.dat");

    if (!StrmWyj.is_open())
    {
        std::cerr << std::endl << "Nie mozna otworzyc do zapisu pliku: ../datasets/trasa_przelotu.dat" << std::endl << std::endl;
        return false;
    }
    KatObrot *= M_PI/180;
    Vector3D PolozKonc = {Dlugosc * cos(KatObrot) + Poloz[0], Dlugosc * sin(KatObrot) + Poloz[1], Poloz[2]};
    StrmWyj << Poloz << std::endl << Poloz[0] << " " << Poloz[1] << " 80" << std::endl
            << PolozKonc[0] << " " << PolozKonc[1] << " 80" << std::endl << PolozKonc <<std::endl;
    Lacze.DodajNazwePliku("../datasets/trasa_przelotu.dat");
    return !StrmWyj.fail();
}

bool Dron::WykonajLot(double Dlug, double KatObr, PzG::LaczeDoGNUPlota &Lacze, int const adresDrona, std::vector<std::shared_ptr<ObiektScena>> LObiektow, Vector3D& PolozPoczatkowe)
{
    std::cout << std::endl << "Wznoszenie ... " << std::endl;
    for(; Poloz[2] <= 80; Poloz[2] += 2)
    {
        if (!Oblicz_i_zapisz_WspDrona(adresDrona)) return false;
        usleep(100000);
        Lacze.Rysuj();
    }

    std::cout << "Lot do przodu ... " << std::endl;
    double x, y, a1, b, Kat;
    Kat = KatObr;
    KatObr *= M_PI / 180;
    x = Dlug * cos(KatObr) + Poloz[0];
    y = Dlug * sin(KatObr) + Poloz[1];
    if (x != Poloz[0]){
        a1 = (x - Poloz[0]) / abs(x - Poloz[0]);
    }
    else {a1 = 0;}
    if (y != Poloz[2]){
        b = (y - Poloz[1]) / abs(x - Poloz[0]);
    }
    else {b = 0;}
    if (a1 > 0)
    {
        for (; Poloz[0] <= x; Poloz[0] += a1, Poloz[1] +=b)
        {
            if(!Oblicz_i_zapisz_WspDrona(adresDrona)) return false;
            usleep(100000);
            Lacze.Rysuj();
        }
    }
    if (a1 < 0)
    {
        for (; Poloz[0] >= x; Poloz[0] += a1, Poloz[1] +=b)
        {
            if(!Oblicz_i_zapisz_WspDrona(adresDrona)) return false;
            usleep(100000);
            Lacze.Rysuj();
        }
    }
    if (a1 == 0) 
    {
        if(y > Poloz[1])
        {
            b = 1;
            for (; Poloz[1] <= y; Poloz[1] +=b)
            {
                if(!Oblicz_i_zapisz_WspDrona(adresDrona)) return false;
                usleep(100000);
                Lacze.Rysuj();
            }
        }
        if(y < Poloz[1])
        {
            b = -1;
            for (; Poloz[1] >= y; Poloz[1] +=b)
            {
                if(!Oblicz_i_zapisz_WspDrona(adresDrona)) return false;
                usleep(100000);
                Lacze.Rysuj();
            }
        }
    }
    Poloz[0] = x; Poloz[1] = y;

    if (!Kolizja(Kat, Lacze, adresDrona, LObiektow, PolozPoczatkowe)) return false;


    for (; Poloz[2] >= 2; Poloz[2] -= 2)
    {
        if (!Oblicz_i_zapisz_WspDrona(adresDrona)) return false;
        usleep(100000);
        Lacze.Rysuj();
    }
    return true;
}

bool Dron::Kolizja(double KatObr, PzG::LaczeDoGNUPlota &Lacze, int const adresDrona, std::vector<std::shared_ptr<ObiektScena>> LObiektow, Vector3D& PolozPoczatkowe)
{
    double Odleglosc;
    int Kolizja = 0;
    Vector3D Polozxy, PunktObiektu;
    for (unsigned int i = 0; i < LObiektow.size(); ++i)
    {
        if (Korp.NazwaBrylaFinalna != LObiektow[i]->ZwrotNazwaFinalna())
        {
            if(LObiektow[i]->ZwrotTypu() == Drn)
            {
                Odleglosc = sqrt(pow(Korp.Poloz[0] - LObiektow[i]->ZwrotPoloz()[0],2) + pow(Korp.Poloz[1] - LObiektow[i]->ZwrotPoloz()[1], 2));
                if (Odleglosc < 2 * PROMIEN)
                {
                    Kolizja = 1;
                }           
            }
            else
            {
                if (Korp.Poloz[0] >= LObiektow[i]->ZwrotPoloz()[0] && Korp.Poloz[1] >= LObiektow[i]->ZwrotPoloz()[1]) // pierwsza czwiartka
                {
                    std::ifstream StrWe(LObiektow[i]->ZwrotNazwaFinalna());
                    if (!StrWe.is_open())
                    {
                    std::cerr << std::endl << "Blad otwarcia pliku" << LObiektow[i]->ZwrotNazwaFinalna() << std::endl;
                    return false;
                    }
                    assert(StrWe.good());
                    StrWe >> Polozxy;
                    while (!StrWe.fail())
                    {
                        if (Polozxy[0] >= LObiektow[i]->ZwrotPoloz()[0] && Polozxy[1] >= LObiektow[i]->ZwrotPoloz()[1] && Polozxy[2] == 0)
                        {
                            PunktObiektu = Polozxy;
                        }
                        StrWe >> Polozxy;
                    }
                    PunktObiektu[0] += PROMIEN;
                    PunktObiektu[1] += PROMIEN;
                    if (PunktObiektu[0] >= Korp.Poloz[0] && PunktObiektu[1] >= Korp.Poloz[1])
                    {
                        Kolizja = 1;
                    }
                }
                if (Korp.Poloz[0] > LObiektow[i]->ZwrotPoloz()[0] && Korp.Poloz[1] < LObiektow[i]->ZwrotPoloz()[1]) // czwarta czwiartka
                {
                    std::ifstream StrWe(LObiektow[i]->ZwrotNazwaFinalna());
                    if (!StrWe.is_open())
                    {
                    std::cerr << std::endl << "Blad otwarcia pliku" << LObiektow[i]->ZwrotNazwaFinalna() << std::endl;
                    return false;
                    }
                    assert(StrWe.good());
                    StrWe >> Polozxy;
                    while (!StrWe.fail())
                    {
                        if (Polozxy[0] > LObiektow[i]->ZwrotPoloz()[0] && Polozxy[1] < LObiektow[i]->ZwrotPoloz()[1] && Polozxy[2] == 0)
                        {
                            PunktObiektu = Polozxy;
                        }
                        StrWe >> Polozxy;
                    }
                    PunktObiektu[0] += PROMIEN;
                    PunktObiektu[1] -= PROMIEN;
                    if (PunktObiektu[0] >= Korp.Poloz[0] && PunktObiektu[1] <= Korp.Poloz[1])
                    {
                        Kolizja = 1;
                    }
                }
                if (Korp.Poloz[0] < LObiektow[i]->ZwrotPoloz()[0] && Korp.Poloz[1] > LObiektow[i]->ZwrotPoloz()[1]) // druga czwiartka
                {
                    std::ifstream StrWe(LObiektow[i]->ZwrotNazwaFinalna());
                    if (!StrWe.is_open())
                    {
                    std::cerr << std::endl << "Blad otwarcia pliku" << LObiektow[i]->ZwrotNazwaFinalna() << std::endl;
                    return false;
                    }
                    assert(StrWe.good());
                    StrWe >> Polozxy;
                    while (!StrWe.fail())
                    {
                        if (Polozxy[0] < LObiektow[i]->ZwrotPoloz()[0] && Polozxy[1] > LObiektow[i]->ZwrotPoloz()[1] && Polozxy[2] == 0)
                        {
                            PunktObiektu = Polozxy;
                        }
                        StrWe >> Polozxy;
                    }
                    PunktObiektu[0] -= PROMIEN;
                    PunktObiektu[1] += PROMIEN;
                    if (PunktObiektu[0] <= Korp.Poloz[0] && PunktObiektu[1] >= Korp.Poloz[1])
                    {
                        Kolizja = 1;
                    }
                }
                if (Korp.Poloz[0] <= LObiektow[i]->ZwrotPoloz()[0] && Korp.Poloz[1] <= LObiektow[i]->ZwrotPoloz()[1]) // trzecia czwiartka
                {
                    std::ifstream StrWe(LObiektow[i]->ZwrotNazwaFinalna());
                    if (!StrWe.is_open())
                    {
                    std::cerr << std::endl << "Blad otwarcia pliku" << LObiektow[i]->ZwrotNazwaFinalna() << std::endl;
                    return false;
                    }
                    assert(StrWe.good());
                    StrWe >> Polozxy;
                    while (!StrWe.fail())
                    {
                        if (Polozxy[0] <= LObiektow[i]->ZwrotPoloz()[0] && Polozxy[1] <= LObiektow[i]->ZwrotPoloz()[1] && Polozxy[2] == 0)
                        {
                            PunktObiektu = Polozxy;
                        }
                        StrWe >> Polozxy;
                    }
                    PunktObiektu[0] -= PROMIEN;
                    PunktObiektu[1] -= PROMIEN;
                    if (PunktObiektu[0] <= Korp.Poloz[0] && PunktObiektu[1] <= Korp.Poloz[1])
                    {
                        Kolizja = 1;
                    } 
                }
            }
        }
    } 
    if (Kolizja == 1)
    {
        ModyfikujTrasePrzelotu(PolozPoczatkowe, KatObr, PROMIEN ,Lacze);
        WykonajLot(PROMIEN, KatObr, Lacze, adresDrona, LObiektow, PolozPoczatkowe);
    }
    return true;
}

bool Dron::ModyfikujTrasePrzelotu(Vector3D& PolozPoczatkowe, double KatObrot, double Dlugosc, PzG::LaczeDoGNUPlota &Lacze)
{
    std::ofstream StrmWyj("../datasets/trasa_przelotu.dat");
    Lacze.UsunNazwePliku("../datasets/trasa_przelotu.dat");
    if (!StrmWyj.is_open())
    {
        std::cerr << std::endl << "Nie mozna otworzyc do zapisu pliku: ../datasets/trasa_przelotu.dat" << std::endl << std::endl;
        return false;
    }
    KatObrot *= M_PI/180;
    Vector3D PolozKonc = {Dlugosc * cos(KatObrot) + Poloz[0], Dlugosc * sin(KatObrot) + Poloz[1], 0};
    StrmWyj << PolozPoczatkowe << std::endl << PolozPoczatkowe[0] << " " << PolozPoczatkowe[1] << " 80" << std::endl
            << PolozKonc[0] << " " << PolozKonc[1] << " 80" << std::endl << PolozKonc <<std::endl;
    Lacze.DodajNazwePliku("../datasets/trasa_przelotu.dat");
    return !StrmWyj.fail();
}