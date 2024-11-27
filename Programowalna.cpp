#include "programowalna.h"

Programowalna :: Programowalna(): User(), przypisana(false) {}

void Programowalna :: ustaw_dane_programowalnej()
{
    string imie;
    cout << "Podaj imie: ";
    cin >> imie;
    zmien_imie(imie);

    string nazwisko;
    cout << "Podaj nazwisko: ";
    cin >> nazwisko;
    zmien_nazwisko(nazwisko);

    string data;
    cout << "Podaj date: ";
    cin >> data;
    zmien_date(data);

    string adres;
    cin.ignore();
    cout << "Podaj adres: ";
    getline(cin, adres);
    zmien_adres(adres);

    string dostep;
    cout << "Podaj dostep: ";
    cin >> dostep;
    zmien_dostep(dostep);
}

void Programowalna :: wyswietl_dane_programowalnej()
{
    wyswietl_imie();
    cout << " ";
    wyswietl_nazwisko();
    cout << " ";
    wyswietl_date();
    cout << " ";
    wyswietl_adres();
    cout << " - ";
    wyswietl_dostep();
    cout << endl;
}


void Programowalna :: powitanie()
{
    if (!przypisana)
    {
        string odp;
        cout << "Karta nie przypisana, czy chcesz przypisac karte do pracownika? (tak/nie) ";
        cin >> odp;
        if (odp == "tak")
        {
            ustaw_dane_programowalnej();
        }
        else if (odp == "nie")
        {
            cout << "Anulowano przypisanie karty." << endl;
        }
        else
        {
            cout << "Nie rozpoznano komendy. Anulowano zadanie." << endl;
        }
    }
}

bool Programowalna::czy_przypisana()
{
    return przypisana;
}
