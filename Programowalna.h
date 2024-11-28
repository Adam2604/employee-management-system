#pragma once
#include <iostream>
#include "user.h"
#include "admin.h"
#include "praktykant.h"
#include "magazynier.h"

using namespace std;

class Programowalna : public User
{
    bool przypisana;
public:
    Programowalna();
    void wyswietl_dane_karty();
    void obsluz_dostep(bool& oczekiwanie_na_potwierdzenie_praktykanta, Praktykant& praktykant, Magazynier& magazynier, Admin& admin, vector<User*>& pracownicy);
    void wyswietl_dane_programowalnej();
    void ustaw_dane_programowalnej();
    void powitanie(vector<User*>& pracownicy);
    bool czy_przypisana();

};




