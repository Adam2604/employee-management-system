#include "praktykant.h"

using namespace std;


Praktykant::Praktykant()
    : User("Bartosz", "Kostuj", "10.11.2004", "ul.Polanka 3 Poznan", "PRAKTYKANT"), oczekiwanie_na_potwierdzenie(false) {}

void Praktykant::wyswietl_dane_praktykanta()
{
    wyswietl_imie();
    cout << " ";
    wyswietl_nazwisko();
    cout << " - ";
    wyswietl_dostep();
    cout << endl;
    cout << endl;
}

void Praktykant::wniosek_o_dostep()
{
    cout << "Czy zlozyc wniosek o dostep do magazynu? (tak/nie) ";
    string odp;
    cin >> odp;

    if(odp =="tak")
    {
        oczekiwanie_na_potwierdzenie = true;
        cout << "Prosze czekac. Za chwile podejdzie pracownik ..." << endl;
    }
    else if(odp =="nie")
    {
        oczekiwanie_na_potwierdzenie = false;
        cout << "Anulowano wniosek o dostep" << endl;
    }
    else
    {
        cout << "Nie rozpoznano komendy, anulowano zadanie.";
    }

}

void Praktykant::rozpocznij_liczenie()
{
    timer.startTimer();
}

void Praktykant::zatwierdz_dostep()
{
    if(oczekiwanie_na_potwierdzenie)
    {
        oczekiwanie_na_potwierdzenie = false;
        cout << "Dostep potwierdzony, mozna wejsc na magazyn." << endl;
        rozpocznij_liczenie();
    }
}

bool Praktykant::czy_oczekuje_na_potwierdzenie()
{
    return oczekiwanie_na_potwierdzenie;
}

float Praktykant::zakoncz_liczenie()
{
    return timer.stopTimer();
}

bool Praktykant::czy_liczy()
{
    return timer.isRunning();
}

void Praktykant::from_json(const json& dane)
{
    zmien_imie(dane["imie"].get<string>());
    zmien_nazwisko(dane["nazwisko"].get<string>());
    zmien_date(dane["data_urodzenia"].get<string>());
    zmien_adres(dane["adres"].get<string>());
    zmien_dostep(dane["poziom_dostepu"].get<string>());
}

json Praktykant::to_json()
{
    return json{
                    {"typ", "praktykant"},
                    {"imie", pobierz_imie()},
                    {"nazwisko", pobierz_nazwisko()},
                    {"data_urodzenia", pobierz_date()},
                    {"adres", pobierz_adres()},
                    {"poziom_dostepu", pobierz_dostep()}
    };
}