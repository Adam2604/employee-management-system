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
            cout << "Karta zostala przypisana." << endl;
            przypisana = true;
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


void Programowalna::obsluz_dostep(bool& oczekiwanie_na_potwierdzenie_praktykanta, Praktykant& praktykant, Magazynier& magazynier, Admin& admin, vector<User*>& pracownicy)
{
    string typ_dostepu = pobierz_dostep();
    if (typ_dostepu == "admin")
    {
        admin.wyswietl_dane_admina();
        admin.wybierz_zadanie(pracownicy);
    }
    else if (typ_dostepu == "magazynier")
    {
        if (oczekiwanie_na_potwierdzenie_praktykanta)
        {
            magazynier.potwierdz_dostep(praktykant);
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
    else if (typ_dostepu == "praktykant")
    {
        if (!praktykant.czy_liczy())
        {
            praktykant.wyswietl_dane_praktykanta();
            praktykant.wniosek_o_dostep();
            if (!praktykant.czy_oczekuje_na_potwierdzenie())
            {
                praktykant.rozpocznij_liczenie();
            }
            else
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
    else
    {
        cout << "Nieznany typ dostępu: " << typ_dostepu << endl;
    }
}
