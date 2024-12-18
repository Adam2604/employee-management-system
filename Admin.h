#pragma once
#include <iostream>
#include <vector>
#include "user.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;
class Admin : public User
{
public:
    Admin(); // konstruktor który ustawi domyslne wartosci dla admina

    void wyswietl_dane_admina();
    void wybierz_zadanie(vector<User*> &pracownicy);    // w mainie wytlumaczylem czym jest ten vector
    void wyswietl_dane_pracownikow(vector<User*> &pracownicy);
    void edytuj_dane_pracownikow(vector<User*> &pracownicy);
    void from_json(const json& dane);
    json to_json();
};
