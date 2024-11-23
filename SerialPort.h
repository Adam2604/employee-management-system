#pragma once
#include <windows.h>
#include <string>

class SerialPort {
public:
    SerialPort(const std::string& portName);
    ~SerialPort();
    bool open();
    void close();
    bool readData(std::string& data);

private:
    HANDLE hSerial;
    std::string portName;
    DCB dcbSerialParams;
    COMMTIMEOUTS timeouts;
};
