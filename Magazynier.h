#pragma once

#include <iostream>
#include "admin.h"
#include "user.h"
#include "praktykant.h"
#include "zegar.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

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
    void from_json(json& dane);
    json to_json();
};

