#pragma once
#include <vector>
#include <string>
#include "user.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class Manager_plikow
{
public:
    vector<User*> wczytaj_pracownikow(string& nazwa_pliku);

    void zapisz_pracownikow(string& nazwa_pliku, vector<User*>& pracownicy);
};

