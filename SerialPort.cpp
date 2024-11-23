#include "Serialport.h"
#include <iostream>

using namespace std;

SerialPort::SerialPort(const string& portName)
    : portName(portName), hSerial(INVALID_HANDLE_VALUE) {}

SerialPort::~SerialPort() {
    close();
}

bool SerialPort::open() {
    hSerial = CreateFile(portName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hSerial == INVALID_HANDLE_VALUE) {
        cerr << "Nie wykryto czytnika kart" << endl;
        return false;
    }

    dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    GetCommState(hSerial, &dcbSerialParams);
    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    SetCommState(hSerial, &dcbSerialParams);

    timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    SetCommTimeouts(hSerial, &timeouts);

    return true;
}

void SerialPort::close() {
    if (hSerial != INVALID_HANDLE_VALUE) {
        CloseHandle(hSerial);
        hSerial = INVALID_HANDLE_VALUE;
    }
}

bool SerialPort::readData(string& data) {
    char szBuff[1024];
    DWORD dwBytesRead = 0;
    if (ReadFile(hSerial, szBuff, sizeof(szBuff) - 1, &dwBytesRead, NULL) && dwBytesRead > 0) {
        szBuff[dwBytesRead] = '\0'; // Zakończ ciąg
        data = szBuff;
        data.erase(data.find_last_not_of(" \n\r") + 1);  // Usuń końcowe białe znaki
        return true;
    }
    return false;
}
