#include <iostream>
#include <fstream>
#include "Serialport.h"
#include "user.h"
#include "admin.h"
#include "praktykant.h"
#include "magazynier.h"
#include "Tryb_awaryjny.h"
#include "programowalna.h"
#include "json.hpp"
#include "Manager_plikow.h"

using namespace std;
using json = nlohmann::json;

int main()
{
    SerialPort serial("COM5");

    if (!serial.open())
    {
        return 1;
    }
    vector<User*> pracownicy = Manager_plikow::wczytaj_pracownikow("pracownicy.json");

    Admin admin;
    Praktykant praktykant;
    Magazynier magazynier;
    Programowalna karta;

    bool admin_exists = false;
    bool praktykant_exists = false;
    bool magazynier_exists = false;

    for (auto& pracownik : pracownicy)
    {
        if (pracownik->pobierz_dostep() == admin.pobierz_dostep())
            admin_exists = true;
        if (pracownik->pobierz_dostep() == praktykant.pobierz_dostep())
            praktykant_exists = true;
        if (pracownik->pobierz_dostep() == magazynier.pobierz_dostep())
            magazynier_exists = true;
        if (pracownik->pobierz_typ() == karta.pobierz_typ())
        {
            Programowalna* karta_programowalna = dynamic_cast<Programowalna*>(pracownik);
            if (karta_programowalna)
            {
                karta = *karta_programowalna;
            }
        }
    }

    if (!admin_exists)
        pracownicy.push_back(&admin);
    if (!praktykant_exists)
        pracownicy.push_back(&praktykant);
    if (!magazynier_exists)
        pracownicy.push_back(&magazynier);

    string id_karty;
    cout << "Czekam na przylozenie karty..." << endl;

    bool oczekiwanie_na_potwierdzenie_praktykanta = false;
    bool oczekiwanie_na_przypisanie = false;
    Programowalna* karta_do_przypisania = nullptr;
    while (true)
    {
        if (serial.readData(id_karty))
        {
            if (id_karty == "AWARYJNY") // NACIŚNIĘCIE PRZYCISKU
            {
                Dostep_awaryjny tryb_awaryjny(pracownicy);
                tryb_awaryjny.uzyskaj_dostep();
            }
            else if (id_karty == "E0 D2 4A 0E")  // ADMIN
            {
                if (oczekiwanie_na_przypisanie && karta_do_przypisania) {
                    cout << "Operacja zatwierdzona, mozna kontynuowac." << endl;
                    karta_do_przypisania->ustaw_przypisanie(true);
                    karta_do_przypisania->ustaw_dane_programowalnej(pracownicy);
                    pracownicy.push_back(karta_do_przypisania);
                    Manager_plikow::zapisz_pracownikow("pracownicy.json", pracownicy);
                    karta_do_przypisania = nullptr;
                    oczekiwanie_na_przypisanie = false;
                }
                else {
                    admin.wyswietl_dane_admina();
                    admin.wybierz_zadanie(pracownicy);
                    Manager_plikow::zapisz_pracownikow("pracownicy.json", pracownicy);
                }
            }
            else if (id_karty == "61 0E E3 0C")  // MAGAZYNIER
            {
                if (oczekiwanie_na_potwierdzenie_praktykanta)
                {
                    magazynier.potwierdz_dostep(praktykant);
                    praktykant.sprawdzCzasPrzybycia("pracownicy.json");
                    oczekiwanie_na_potwierdzenie_praktykanta = false;
                }
                else
                {
                    if (!magazynier.czy_liczy())
                    {
                        magazynier.wyswietl_dane_magazyniera();
                        magazynier.rozpocznij_liczenie();
                    }
                    else
                    {
                        magazynier.wyswietl_dane_magazyniera();
                        magazynier.zakoncz_liczenie();
                    }
                }
            }
            else if (id_karty == "A4 AD BA F3")  // PRAKTYKANT
            {
                if (!praktykant.czy_liczy())
                {
                    praktykant.wyswietl_dane_praktykanta();
                    praktykant.wniosek_o_dostep();
                    if (praktykant.czy_oczekuje_na_potwierdzenie())
                    {
                        oczekiwanie_na_potwierdzenie_praktykanta = true;
                    }
                }
                else
                {
                    praktykant.wyswietl_dane_praktykanta();
                    praktykant.zakoncz_liczenie();
                }
            }
            else if (id_karty == "04 0E 7B F4")  // KARTA PROGRAMOWALNA
            {
                if (!karta.czy_przypisana())
                {
                    if (oczekiwanie_na_przypisanie) {
                        cout << "Konieczne zatwierdzenie przez administratora." << endl;
                    }
                    else {
                        cout << "Karta nie przypisana. Aby to zrobic konieczne jest zatwierdzenie przez administratora." << endl;
                        karta_do_przypisania = &karta;
                        oczekiwanie_na_przypisanie = true;
                    }
                }
                else
                {
                    karta.obsluz_dostep(oczekiwanie_na_potwierdzenie_praktykanta, praktykant, magazynier, admin, pracownicy);
                }
            }
            else
            {
                cout << "Nieznana karta, zamykam dostep." << endl;
                return 0;
            }
        }
    }

    serial.close();
    return 0;
}
