#include "zegar.h"

using namespace std;

Timer::Timer() : running(false) {}

void Timer::startTimer()
{
    start = chrono::steady_clock::now();
    running = true;
    cout << "Rozpoczeto odliczanie..." << std::endl;
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
