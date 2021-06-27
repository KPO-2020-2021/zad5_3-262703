#include "BrylaWzorcowa.hh"

std::string& BrylaGeometryczna::WezNazwePliku_Bryla(double KatObrotu, Vector3D VectorTransl)
{
    std::ifstream StrmWe(NazwaBrylaWzorc);
    std::ofstream StrmWy(NazwaBrylaFinalna);

    if (!StrmWe.is_open())
    {
        std::cerr << std::endl << "Blad otwarcia pliku" << NazwaBrylaFinalna << std::endl;
    }
    if (!StrmWy.is_open())
    {
        std::cerr << std::endl << "Blad otwarcia pliku" << NazwaBrylaFinalna << std::endl;
    }
    
    assert(StrmWe.good());
    assert(StrmWy.good());
    Vector3D Polozen;
    StrmWe >> Polozen;
    while (!StrmWe.fail())
    {
        for (unsigned int IloscWierz = 0; IloscWierz < 4; ++IloscWierz)
        {
            Skaluj(Polozen, KatObrotu, VectorTransl);
            StrmWy << Polozen << std::endl;
            StrmWe >> Polozen;

            assert(IloscWierz == 3 || !StrmWe.fail());
        }

        StrmWy << std::endl;
    }
    return NazwaBrylaFinalna;
}

Vector3D BrylaGeometryczna::Skaluj(Vector3D& Poloz, double KatObrotu, Vector3D VectorTransl)
{
    KatObrotu *=M_PI/180;
    Vector3D PolozNowe;
    PolozNowe[0] = Poloz[0] * cos(KatObrotu) - Poloz[1] * sin(KatObrotu);
    PolozNowe[1] = Poloz[0] * sin(KatObrotu) + Poloz[1] * cos(KatObrotu);
    PolozNowe[2] = Poloz[2];
    Poloz = PolozNowe * Skala + VectorTransl;
    return Poloz;
}

std::string& BrylaGeometryczna::WezNazwePliku_BrylaObiekt(Vector3D VectorTransl )
{
    std::ifstream StrmWe(NazwaBrylaWzorc);
    std::ofstream StrmWy(NazwaBrylaFinalna);

    if (!StrmWe.is_open())
    {
        std::cerr << std::endl << "Blad otwarcia pliku" << NazwaBrylaFinalna << std::endl;
    }
    if (!StrmWy.is_open())
    {
        std::cerr << std::endl << "Blad otwarcia pliku" << NazwaBrylaFinalna << std::endl;
    }
    
    assert(StrmWe.good());
    assert(StrmWy.good());
    Vector3D Polozen;
    StrmWe >> Polozen;
    while (!StrmWe.fail())
    {
        for (unsigned int IloscWierz = 0; IloscWierz < 4; ++IloscWierz)
        {
            switch (TYP)
            {
                case GoraZOstrymSzczyt:
                    Polozen = TransfGoraZOstrymSzszytem(Polozen);
                    break;
                case GoraZDlugaGran:
                    Polozen = TransfGoraZDlugaGrania(Polozen);
                    break;
                case Plaskow:
                    break;
                case Drn:
                    break;
            }
            
            Skaluj(Polozen, 0, VectorTransl);
            StrmWy << Polozen << std::endl;
            StrmWe >> Polozen;

            assert(IloscWierz == 3 || !StrmWe.fail());
        }

        StrmWy << std::endl;
    }
    return NazwaBrylaFinalna;
}

Vector3D BrylaGeometryczna::TransfGoraZOstrymSzszytem(Vector3D& Wierz)
{
    if (Wierz[2] > 0.5)
    {
        Wierz[0] = 0;
        Wierz[1] = 0;
    }
    else if (Wierz[2] == 0.5)
    {
        Wierz[0] /= 2;
        Wierz[1] /= 2;
    }
    return Wierz;
}

Vector3D BrylaGeometryczna::TransfGoraZDlugaGrania(Vector3D& Wierz)
{
    if(Wierz[2] > 0.5)
    {
        if(Wierz[0] < 0)
        {
            Wierz[0] = fabs(Wierz[0]);
        }
    }
    return Wierz;
}