#pragma once
#include <iostream>
#include <vector>
#include "user.h"

using namespace std;
class Admin : public User
{
public:
    Admin(); // konstruktor który ustawi domyslne wartosci dla admina

    void wyswietl_dane_admina();
    void wybierz_zadanie(vector<User*> &pracownicy);    // w mainie wytlumaczylem czym jest ten vector
    void wyswietl_dane_pracownikow(vector<User*> &pracownicy);
    void edytuj_dane_pracownikow(vector<User*> &pracownicy);
};
