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
