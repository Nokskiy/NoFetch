#pragma once
namespace cppich
{
    #include <iostream>
    #include <string>

    #ifdef _WIN32
    #include <windows.h>
    #endif
    enum consoleColor
    {
        Black,
        Blue,
        Green,
        Cyan,
        Red,
        Magenta,
        Yellow,
        White
    };

    #ifdef _WIN32
    void setColor(consoleColor col) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, col);
    }
    #else
    void setColor(consoleColor col)
    {
        switch (col) {
        case Black:   std::cout << "\033[30m"; break;
        case Blue:    std::cout << "\033[34m"; break;
        case Green:   std::cout << "\033[32m"; break;
        case Cyan:    std::cout << "\033[36m"; break;
        case Red:     std::cout << "\033[31m"; break;
        case Magenta: std::cout << "\033[35m"; break;
        case Yellow:  std::cout << "\033[33m"; break;
        case White:   std::cout << "\033[37m"; break;
        }
    }
    #endif
    template <typename T>
    void print(T text, consoleColor col = White) {
        setColor(col);
        std::cout << text;
    #ifdef _WIN32
        setColor(White);
    #else
        std::cout << "\033[0m";
    #endif
    }
    std::string cin(consoleColor col = White) 
    {
        setColor(col);
        std::string text;
        std::getline(std::cin, text);
    #ifdef _WIN32
        setColor(White);
    #else
        std::cout << "\033[0m";
    #endif
        return text;
    }
}