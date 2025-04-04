#pragma once
#include <iostream>
#include <chrono>
#include <fstream>
#include <ctime>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

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
    bool isLate(const std::string& jsonPath);
};
