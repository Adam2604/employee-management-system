#pragma once
#include <iostream>
#include "user.h"
using namespace std;

class Programowalna : public User
{
public:
    Programowalna();
    void wyswietl_dane_programowalnej();
    void ustaw_dane_programowalnej();
    void powitanie();

};




