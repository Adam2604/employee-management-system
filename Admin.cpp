#include "admin.h"
#include <iostream>

using namespace std;

Admin::Admin() : User("Adam", "Michalak", "26.04.2004", "ul. Polanka 3 Poznan", "ADMIN") {}   // Konstruktor przypisujacy domyslne wartosci atrybutow dla admina

void Admin::wyswietl_dane_admina()
{
    wyswietl_imie();
    cout << " ";
    wyswietl_nazwisko();
    cout << " - ";
    wyswietl_dostep();
    cout << endl;
    cout << endl;
}

void Admin::wybierz_zadanie(vector<User*> &pracownicy)
{
    cout << "Co chcesz zrobic?(wybierz numer)" << endl;
    cout << "1. Wyswietlic dane pracownikow" << endl;
    cout << "2. Edytowac dane pracownikow" << endl;
    int wybor;
    cin >> wybor;
    if(wybor == 1)
    {
        wyswietl_dane_pracownikow(pracownicy);
    }
    else if(wybor == 2)
    {
        edytuj_dane_pracownikow(pracownicy);
    }
    else
    {
        cout << "Bledny numer";
    }
}

void Admin::wyswietl_dane_pracownikow(vector<User*> &pracownicy)    // funkcja wyswietlajaca dane pracownikow
{
    cout << "Dane pracownikow: " << endl;
    for(User* &pracownik : pracownicy) // przetestowac "User*" zamiast auto
    {
        cout << *pracownik << endl;
    }
}

void Admin::edytuj_dane_pracownikow(vector<User*> &pracownicy)  // funkcja edytujaca dane pracownikow
{
    cout << "Wybierz pracownika do zmiany danych:" << endl;
    cout << endl;
    int nr = 1;
    int wybor;
    for(User* &pracownik : pracownicy)
    {
        cout << nr << ". ";
        pracownik -> wyswietl_imie();
        cout << " ";
        pracownik -> wyswietl_nazwisko();
        cout << " - ";
        pracownik -> wyswietl_dostep();
        cout << endl;
        nr++;
    }
    cin >> wybor;
    if(wybor > 0 && wybor <= pracownicy.size())
    {
        User* wybrany_pracownik = pracownicy[wybor - 1];
        bool zmiana_danych = true;

        while(zmiana_danych)    // while jest po to jakby uzytkownik chcial zmienic wiecej niz jedne dane ale nie wszystkie
        {
            cout << "Co chcesz zmienic?(wybierz numer)" << endl;
            cout << "1. Imie" << endl;
            cout << "2. Nazwisko" << endl;
            cout << "3. Date" << endl;
            cout << "4. Adres" << endl;
            cout << "5. Poziom dostepu" << endl;
            cout << "6. Wszystkie dane" << endl;
            cout << "7. Anuluj" << endl;

            int opcja;
            cin >> opcja;
            switch(opcja)
            {
            case 1:
                {
                    string nowe_imie;
                    cout << "Podaj nowe imie: ";
                    cin >> nowe_imie;
                    wybrany_pracownik -> zmien_imie(nowe_imie);
                    cout << "Imie zostalo zmienione." << endl;
                    break;
                }
            case 2:
                {
                    string nowe_nazwisko;
                    cout << "Podaj nowe nazwisko: ";
                    cin >> nowe_nazwisko;
                    wybrany_pracownik -> zmien_nazwisko(nowe_nazwisko);
                    cout << "Nazwisko zostalo zmienione." << endl;
                    break;
                }
            case 3:
                {
                    string nowa_data;
                    cout << "Podaj nowa date urodzenia: ";  // mozna sie odmlodzic
                    cin >> nowa_data;
                    wybrany_pracownik -> zmien_date(nowa_data);
                    cout << "Data urodzenia zostala zmieniona." << endl;
                    break;
                }
            case 4:
                {
                    string nowy_adres;
                    cout << "Podaj nowy adres zamieszkania: ";
                    cin >> nowy_adres;
                    wybrany_pracownik -> zmien_adres(nowy_adres);
                    cout << "Adres zamieszkania zostal zmieniony." << endl;
                    break;
                }
            case 5:
                {
                    string nowy_dostep;
                    cout << "Podaj nowy poziom dostepu: ";
                    cin >> nowy_dostep;
                    wybrany_pracownik -> zmien_dostep(nowy_dostep);
                    cout << "Rodzaj dostepu zostal zmieniony. " << endl;
                    break;
                }
            case 6:
                {
                    string nowe_imie, nowe_nazwisko, nowa_data, nowy_adres, nowy_dostep;

                    cout << "Podaj nowe imie: ";
                    cin >> nowe_imie;
                    wybrany_pracownik -> zmien_imie(nowe_imie);

                    cout << "Podaj nowe nazwisko: ";
                    cin >> nowe_nazwisko;
                    wybrany_pracownik -> zmien_nazwisko(nowe_nazwisko);

                    cout << "Podaj nowa date urodzenia: ";
                    cin >> nowa_data;
                    wybrany_pracownik -> zmien_date(nowa_data);

                    cout << "Podaj nowy adres zamieszkania: ";
                    cin >> nowy_adres;
                    wybrany_pracownik -> zmien_adres(nowy_adres);

                    cout << "Podaj nowy poziom dostepu: ";
                    cin >> nowy_dostep;
                    wybrany_pracownik -> zmien_dostep(nowy_dostep);

                    cout << "Wszystkie dane zostaly zmienione." << endl;
                    break;
                }
            case 7:
                {
                    cout << "Anulowano edycje danych." << endl;
                    zmiana_danych = false;
                    break;
                }
            default:
                {
                    cout << "Nieprawidlowy wybor. Edycja zostala anulowana." << endl;
                    zmiana_danych = false;
                }
            }
            if(opcja != 7 && opcja >= 1 && opcja <= 5)
            {
                string odpowiedz;
                cout << "Czy chcesz zmienic cos jeszcze?(tak/nie): ";
                cin >> odpowiedz;
                if(odpowiedz == "nie")
                {
                    zmiana_danych = false;
                    cout << "Zakonczono edycje danych." << endl;
                }
            }
        }
    }
    else
    {
        cout << "Nieprawidlowy numer pracownika." << endl;
    }
}

void Admin::from_json(const json& dane)
{
    zmien_imie(dane["imie"].get<string>());
    zmien_nazwisko(dane["nazwisko"].get<string>());
    zmien_date(dane["data_urodzenia"].get<string>());
    zmien_adres(dane["adres"].get<string>());
    zmien_dostep(dane["poziom_dostepu"].get<string>());
}

json Admin::to_json()
{
    return json{
            {"typ", "admin"},
            {"imie", pobierz_imie()},
            {"nazwisko", pobierz_nazwisko()},
            {"data_urodzenia", pobierz_date()},
            {"adres", pobierz_adres()},
            {"poziom_dostepu", pobierz_dostep()}
    };
}