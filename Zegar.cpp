#include "zegar.h"

using namespace std;

Timer::Timer() : running(false) {}

void Timer::startTimer()
{
    start = chrono::steady_clock::now();
    running = true;
}

float Timer::stopTimer()
{
    end = chrono::steady_clock::now();
    duration = end - start;
    running = false;
    cout << "Czas na magazynie: " << duration.count() << " sekund." << endl;
    return duration.count();
}

bool Timer::isRunning()
{
    return running;
}

//spoznienie z JSONa
bool Timer::isLate(const std::string& jsonPath)
{

    std::ifstream file(jsonPath);

    // Wczytywanie
    json data;
    file >> data;

    // Iteruj po danych w pliku JSON przez referencje, data (obiekt json) to kolekcja ktora iteruje
    for (const auto& user : data)
    {
        if (user["typ"] == "praktykant")
        {
            string czas = user["godzina_przybycia"];
            //size t to typ zmiennej przechowującej wyniki find, calkowity typ
            size_t break_ = czas.find(':');  // znajdź pozycję (indeks) separatora ":"

            //pobieramy godzine i minuty (ze stringa do int)
            int godzina = stoi(czas.substr(0, break_));  // Godzina (element z indeksem 0 do indeksu ':')
            int minuta = stoi(czas.substr(break_ + 1));  // Minuta

            // Pobierz aktualny czas
            auto teraz = chrono::system_clock::now();
            auto czasAktualny = chrono::system_clock::to_time_t(teraz);
            tm* lokalnyCzas = localtime(&czasAktualny);

            // Porównaj aktualny czas z czasem przybycia
            if (lokalnyCzas->tm_hour > godzina ||
                (lokalnyCzas->tm_hour == godzina && lokalnyCzas->tm_min > minuta))
            {
                return true;  // spoznil sie
            }
            else
            {
                return false;  // na czas
            }
        }
    }
}