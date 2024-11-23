#pragma once
#include <iostream>
#include <chrono>

using namespace std;

class Timer {
private:
    chrono::time_point<chrono::steady_clock> start, end;
    chrono::duration<float> duration;
    bool running;

public:
    Timer();
    void startTimer();
    float stopTimer();
    bool isRunning();
};
