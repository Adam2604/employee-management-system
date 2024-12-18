#pragma once

#include <vector>
#include <string>
#include "user.h"
#include "json.hpp"

using json = nlohmann::json;

class Manager_plikow
{
public:
    // Funkcja do wczytania danych z pliku JSON
    static vector<User*> wczytaj_pracownikow(const string& nazwa_pliku);

    // Funkcja do zapisania danych do pliku JSON
    static void zapisz_pracownikow(const string& nazwa_pliku, const vector<User*>& pracownicy);

    bool czy_typ_programowalna(const vector<User*>& pracownicy);
};

