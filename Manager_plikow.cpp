#include "Manager_plikow.h"
#include "admin.h"
#include "praktykant.h"
#include "magazynier.h"
#include <fstream>

using namespace std;

vector<User*> Manager_plikow::wczytaj_pracownikow(const std::string& nazwa_pliku)
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
            std::string typ = elem["typ"];
            if (typ == "admin")
            {
                auto* admin = new Admin();
                admin->from_json(elem);
                pracownicy.push_back(admin);
            }
            else if (typ == "praktykant")
            {
                auto* praktykant = new Praktykant();
                praktykant->from_json(elem);
                pracownicy.push_back(praktykant);
            }
            else if (typ == "magazynier")
            {
                auto* magazynier = new Magazynier();
                magazynier->from_json(elem);
                pracownicy.push_back(magazynier);
            }
        }
    }

    return pracownicy;
}

void PlikManager::zapisz_pracownikow(const std::string& nazwa_pliku, const std::vector<User*>& pracownicy)
{
    json dane;
    for (const auto& pracownik : pracownicy)
    {
        dane.push_back(pracownik->to_json());
    }

    std::ofstream plik(nazwa_pliku);
    if (plik.is_open())
    {
        plik << dane.dump(4); // zapis z wcięciami dla czytelności
        plik.close();
    }
}
