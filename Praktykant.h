#pragma once

#include <iostream>
#include "User.h"
#include "zegar.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class Praktykant : public User //dziedziczenie
{
    Timer timer;

    bool oczekiwanie_na_potwierdzenie;
public:
    Praktykant(); //ustawic domyslne

    bool czy_oczekuje_na_potwierdzenie();
    void wyswietl_dane_praktykanta();
    void wniosek_o_dostep();
    void zatwierdz_dostep();
    void rozpocznij_liczenie();
    float zakoncz_liczenie();
    bool czy_liczy();
    void from_json(const json& dane);
    json to_json();
};
