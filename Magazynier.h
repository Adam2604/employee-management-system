#pragma once

#include <iostream>
#include "user.h"
#include "praktykant.h"
#include "zegar.h"

class Magazynier : public User
{
    Timer timer;
public:
    Magazynier();

    void wyswietl_dane_magazyniera();
    void potwierdz_dostep(Praktykant& praktykant);
    void rozpocznij_liczenie();
    float zakoncz_liczenie();
    bool czy_liczy();
};

