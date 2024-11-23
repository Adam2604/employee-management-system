#include "user.h"
#include <iostream>
using namespace std;

User::User() : imie("brak_danych"), nazwisko("brak_danych"), data("brak_danych"), adres("brak_danych"), dostep("brak_danych") {} // Konstr domyœlny

User :: User(string i, string n, string d, string a, string dos): imie(i), nazwisko(n), data(d), adres(a), dostep(dos) {} // Konstr inicjalizuj¹cy

User :: ~User() {} // Destruktor

void User :: zmien_imie(string i)  // Funkcja zmien imie (zrobi³em takie do kazdego atrybutu i wtedy w programie by by³o pytanie do admina "co chcesz zmienic?" i po odpowiedzi wywo³ywana dana funkcja dopóki nie napisze "nic"
{
    imie = i;
}

void User :: zmien_nazwisko(string n)
{
    nazwisko = n;
}

void User :: zmien_date(string d)
{
    data = d;
}

void User :: zmien_adres(string a)
{
    adres = a;
}

void User :: zmien_dostep(string dos)
{
    dostep = dos;
}

// dodalem funkcje wyswietlania pojedynczych danych w razie jakby sie mialo wyswietlic tylko je a nie calosc przez przeciazenie operatora
// najwyzej sie to usunie jak nie bedzie potrzebne
void User :: wyswietl_imie()
{
    cout << imie;
}
void User :: wyswietl_nazwisko()
{
    cout << nazwisko;
}
void User :: wyswietl_date()
{
    cout << data;
}
void User :: wyswietl_adres()
{
    cout << adres;
}
void User :: wyswietl_dostep()
{
    cout << dostep;
}

string User :: pobierz_imie()
{
    return imie;
}

string User :: pobierz_nazwisko()
{
    return nazwisko;
}

string User :: pobierz_date()
{
    return data;
}

string User :: pobierz_adres()
{
    return adres;
}

string User :: pobierz_dostep()
{
    return dostep;
}

ostream& operator <<(ostream &cout, const User &u) // Przeci¹¿enie operatora <<
{
    cout << u.imie << " " << u.nazwisko << " - " << u.dostep << endl << "Data urodzenia: " << u.data << endl << "Adres zamieszkania: " << u.adres << endl;
    return cout;
}
