#include <iostream>
#include "magazynier.h"

Magazynier :: Magazynier() : User("Adam", "Rybacki", "02.03.2005", "ul. Polanka 3 Poznan", "MAGAZYNIER"){}

void Magazynier::wyswietl_dane_magazyniera()
{
    wyswietl_imie();
    cout << " ";
    wyswietl_nazwisko();
    cout << " - ";
    wyswietl_dostep();
    cout << endl;
    cout << endl;
}

void Magazynier::potwierdz_dostep(Praktykant& praktykant)
{
    if(praktykant.czy_oczekuje_na_potwierdzenie())
    {
        praktykant.zatwierdz_dostep();
    }
}

void Magazynier::rozpocznij_liczenie()
{
    cout << "Mozna wejsc na magazyn." << endl;
    timer.startTimer();
}

float Magazynier::zakoncz_liczenie()
{
    return timer.stopTimer();
}

bool Magazynier::czy_liczy()
{
    return timer.isRunning();
}

void Magazynier::from_json(json& dane)
{
    zmien_imie(dane["imie"].get<string>());
    zmien_nazwisko(dane["nazwisko"].get<string>());
    zmien_date(dane["data_urodzenia"].get<string>());
    zmien_adres(dane["adres"].get<string>());
    zmien_dostep(dane["poziom_dostepu"].get<string>());
}

json Magazynier::to_json()
{
    return json{
                {"typ", "magazynier"},
                {"imie", pobierz_imie()},
                {"nazwisko", pobierz_nazwisko()},
                {"data_urodzenia", pobierz_date()},
                {"adres", pobierz_adres()},
                {"poziom_dostepu", pobierz_dostep()}
    };
}