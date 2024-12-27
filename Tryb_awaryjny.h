#pragma once
#include <vector>
#include <string>
#include "user.h"

class Dostep_awaryjny {
    vector<User*> pracownicy;
    string generuj_kod(User* pracownik);
public:
    Dostep_awaryjny(vector<User*>& pracownicy);
    bool uzyskaj_dostep();
    void sprawdz_awaryjny(string& komunikat);
};
