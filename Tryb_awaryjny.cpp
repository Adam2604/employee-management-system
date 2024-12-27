#include "Tryb_awaryjny.h"
#include <iostream>

using namespace std;

Dostep_awaryjny::Dostep_awaryjny(vector<User*>& pracownicy) : pracownicy(pracownicy) {}

bool Dostep_awaryjny::uzyskaj_dostep() {
    cout << "Wprowadz kod dostepu skladajacy sie z twoich inicjalow oraz dnia i miesiaca urodzenia: ";
    string kod_uzytkownika;
    cin >> kod_uzytkownika;

    for (User* pracownik : pracownicy) {
        string kod_pracownika = generuj_kod(pracownik);
        if (kod_pracownika == kod_uzytkownika) {
            cout << "Dostep przyznany! Witaj, " << pracownik->pobierz_imie() << " " << pracownik->pobierz_nazwisko() << endl;
            return true;
        }
    }
    cout << "Niepoprawne dane. Nie przyznano dostepu." << endl;
    return false;
}

void Dostep_awaryjny::sprawdz_awaryjny(string& komunikat)
{
    if (komunikat == "AWARYJNY") {
        cout << "Tryb awaryjny aktywowany!" << endl;
        uzyskaj_dostep();
    }
}

string Dostep_awaryjny::generuj_kod(User* pracownik) {
    string inicjaly = "";
    if (!pracownik->pobierz_imie().empty() && !pracownik->pobierz_nazwisko().empty()) {
        inicjaly += toupper(pracownik->pobierz_imie()[0]);
        inicjaly += toupper(pracownik->pobierz_nazwisko()[0]);
    }
    string data = pracownik->pobierz_date();
    string dzien = data.substr(0, 2);
    string miesiac = data.substr(3, 2);

    return inicjaly + dzien + miesiac;
}
