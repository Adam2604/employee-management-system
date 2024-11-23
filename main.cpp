#include <iostream>
#include "Serialport.h"
#include "user.h"
#include "admin.h"
#include "praktykant.h"
#include "magazynier.h"
#include "Tryb_awaryjny.h"
#include "programowalna.h"

using namespace std;

int main() {
    SerialPort serial("COM5");

    if (!serial.open())
    {
        return 1;
    }
    vector<User*> pracownicy;   //jest to tablica dynamiczna, najlatwiejszy sposob na zapisanie naszych danych jednoczesnie bez zbednego rezerwowania duzej ilosci pamieci
    Admin admin;
    Praktykant praktykant;
    Magazynier magazynier;
    Programowalna karta;

    pracownicy.push_back(&admin);
    pracownicy.push_back(&praktykant);
    pracownicy.push_back(&magazynier);

    string id_karty;
    cout << "Czekam na przylozenie karty..." << endl;
    bool oczekiwanie_na_potwierdzenie_praktykanta = false;
    while (true) {
        if (serial.readData(id_karty))
        {
            if (id_karty == "E0 D2 4A 0E")  // ADMIN
            {
                admin.wyswietl_dane_admina();
                admin.wybierz_zadanie(pracownicy);
            }
            else if(id_karty == "61 0E E3 0C")  // MAGAZYNIER
            {
                if(oczekiwanie_na_potwierdzenie_praktykanta)    // jezeli praktykant poprosi o dostep to sie to stanie
                {
                    magazynier.potwierdz_dostep(praktykant);
                    oczekiwanie_na_potwierdzenie_praktykanta = false;
                }
                else
                {
                    if(!magazynier.czy_liczy()) // Jezeli nie rozpoczelo sie mierzenie czasu to wlasnie zacznie
                    {
                        magazynier.wyswietl_dane_magazyniera();
                        magazynier.rozpocznij_liczenie();
                    }
                    else                        // A jezeli czas juz byl mierzony to zakonczy sie i zostanie to potraktowane jako wyjscie z magazynu
                    {
                        magazynier.wyswietl_dane_magazyniera();
                        magazynier.zakoncz_liczenie();
                    }
                }
            }
            else if(id_karty == "A4 AD BA F3")  // PRAKTYKANT
            {
                if(!praktykant.czy_liczy())
                {
                    praktykant.wyswietl_dane_praktykanta();
                    praktykant.wniosek_o_dostep();
                    if(praktykant.czy_oczekuje_na_potwierdzenie())  // Uruchamiamy liczenie tylko, jeœli oczekuje na potwierdzenie
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
            else if(id_karty == "04 0E 7B F4")  // KARTA PROGRAMOWALNA
            {
                karta.powitanie();
            }
            else
            {
                cout << "Nieznana karta, zamykam dostep.";
                return 1;
            }
        }
    }

    serial.close();
    return 0;
}
