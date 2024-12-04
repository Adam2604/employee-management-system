cmake_minimum_required(VERSION 3.30)
project(Projekt_na_inf)

set(CMAKE_CXX_STANDARD 20)

add_executable(Projekt_na_inf main.cpp
        SerialPort.cpp
        SerialPort.h
        user.cpp
        user.h
        Admin.cpp
        Admin.h
        Magazynier.cpp
        Magazynier.h
        Praktykant.cpp
        Praktykant.h
        Tryb_awaryjny.cpp
        Tryb_awaryjny.h
        Zegar.cpp
        Zegar.h
        Programowalna.cpp
        Programowalna.h
        Manager_plikow.cpp
        Manager_plikow.h)
