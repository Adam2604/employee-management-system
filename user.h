#pragma once
#include <iostream>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

class User
{
private:
    string imie;
    string nazwisko;
    string data;
    string adres;
    string dostep;
    string typ;

public:
    User();
    User(string i, string n, string d, string a, string dos);
    ~User();

    void zmien_imie(string i);
    void zmien_nazwisko(string n);
    void zmien_date(string d);
    void zmien_adres(string a);
    void zmien_dostep(string dos);

    void wyswietl_imie();
    void wyswietl_nazwisko();
    void wyswietl_date();
    void wyswietl_adres();
    void wyswietl_dostep();

    string pobierz_imie();
    string pobierz_nazwisko();
    string pobierz_date();
    string pobierz_adres();
    string pobierz_dostep();
    string pobierz_typ();

    virtual void from_json(const json& dane)=0;
    virtual json to_json()=0;

    friend ostream& operator <<(ostream &cout,const User &u);
};
