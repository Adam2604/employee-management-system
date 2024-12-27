#include "Manager_plikow.h"
#include "admin.h"
#include "praktykant.h"
#include "magazynier.h"
#include "programowalna.h"
#include <fstream>


vector<User*> Manager_plikow::wczytaj_pracownikow(const string& nazwa_pliku)
{
    vector<User*> pracownicy;
    ifstream plik(nazwa_pliku);

    if (plik.is_open())
    {
        json dane;
        plik >> dane;
        plik.close();

        for (const auto& elem : dane)
        {
            string typ = elem["typ"];
            if (typ == "admin")
            {
                Admin* admin = new Admin();
                admin->from_json(elem);
                pracownicy.push_back(admin);
            }
            else if (typ == "praktykant")
            {
                Praktykant* praktykant = new Praktykant();
                praktykant->from_json(elem);
                pracownicy.push_back(praktykant);
            }
            else if (typ == "magazynier")
            {
                Magazynier* magazynier = new Magazynier();
                magazynier->from_json(elem);
                pracownicy.push_back(magazynier);
            }
            else if (typ == "programowalna")
            {
                Programowalna* programowalna = new Programowalna();
                programowalna->from_json(elem);
                pracownicy.push_back(programowalna);
            }
        }
    }

    return pracownicy;
}


void Manager_plikow::zapisz_pracownikow(const string& nazwa_pliku, const vector<User*>& pracownicy)
{
    json dane;
    for (const auto& pracownik : pracownicy)
    {
        dane.push_back(pracownik->to_json());
    }

    ofstream plik(nazwa_pliku);
    if (plik.is_open())
    {
        plik << dane.dump(4); // zapis z wcięciami dla czytelności
        plik.close();
    }
}
