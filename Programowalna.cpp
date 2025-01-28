#include "programowalna.h"

Programowalna :: Programowalna(): User() {}

Magazynier magazynier2;
Praktykant praktykant2;
Admin admin2;
void Programowalna::wyswietl_dane_karty_powitanie()
{
    wyswietl_imie();
    cout << " ";
    wyswietl_nazwisko();
    cout << " - ";
    wyswietl_dostep();
    cout << endl;
    cout << endl;
}


void Programowalna :: ustaw_dane_programowalnej(vector<User*>& pracownicy)
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
    do {
        cout << "Podaj dostep(magazynier lub praktykant): ";
        cin >> dostep;
    }while (dostep != "magazynier" && dostep != "praktykant");
    zmien_dostep(dostep);

    Manager_plikow::zapisz_pracownikow("pracownicy.json", pracownicy);
    cout << "Karta zostala przypisana" << endl;
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


void Programowalna :: powitanie(vector<User*>& pracownicy)
{
    if (!przypisana)
    {
        string odp;
        cout << "Karta nie przypisana, czy chcesz przypisac karte do pracownika? (tak/nie) ";
        cin >> odp;
        if (odp == "tak")
        {
            Programowalna* karta = new Programowalna(*this);
            pracownicy.push_back(karta);
            cout << "Karta zostala przypisana." << endl;
            przypisana = true;

            Manager_plikow::zapisz_pracownikow("pracownicy.json", pracownicy);
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
    if (typ_dostepu == "magazynier")
    {
        if (oczekiwanie_na_potwierdzenie_praktykanta)
        {
            magazynier2.potwierdz_dostep(praktykant);
            oczekiwanie_na_potwierdzenie_praktykanta = false;
        }
        else
        {
            if (!magazynier2.czy_liczy())
            {
                this -> wyswietl_dane_karty_powitanie();
                magazynier2.rozpocznij_liczenie();
            }
            else
            {
                this -> wyswietl_dane_karty_powitanie();
                magazynier2.zakoncz_liczenie();
            }
        }
    }
    else if (typ_dostepu == "praktykant")
    {
        if (!praktykant.czy_liczy())
        {
            this -> wyswietl_dane_karty_powitanie();
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
            this -> wyswietl_dane_karty_powitanie();
            praktykant.zakoncz_liczenie();
        }
    }
    else
    {
        cout << "Nieznany typ dostępu: " << typ_dostepu << endl;
    }
}

void Programowalna::ustaw_przypisanie(bool stan)
{
    przypisana = stan;
}


void Programowalna::from_json(const json& dane)
{
    zmien_imie(dane["imie"].get<string>());
    zmien_nazwisko(dane["nazwisko"].get<string>());
    zmien_date(dane["data_urodzenia"].get<string>());
    zmien_adres(dane["adres"].get<string>());
    zmien_dostep(dane["poziom_dostepu"].get<string>());
    przypisana = dane.value("przypisana", false);
}


json Programowalna::to_json()
{
    return json{
                {"typ", "programowalna"},
                {"imie", pobierz_imie()},
                {"nazwisko", pobierz_nazwisko()},
                {"data_urodzenia", pobierz_date()},
                {"adres", pobierz_adres()},
                {"poziom_dostepu", pobierz_dostep()},
                {"przypisana", przypisana}
    };
}