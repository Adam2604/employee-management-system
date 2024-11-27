#pragma once
#include <iostream>
#include "user.h"
using namespace std;

class Programowalna : public User
{
    bool przypisana;
public:
    Programowalna();
    void wyswietl_dane_programowalnej();
    void ustaw_dane_programowalnej();
    void powitanie();
    bool czy_przypisana();

};




