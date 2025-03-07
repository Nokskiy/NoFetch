#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include <map>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include <filesystem>

#include "Cppich.h"

using namespace std;

HANDLE hConsole;

string commandList[] = {"help","sys_char","monitor_avail_RAM","clear","o_buf","e_buf" };



void setTextColor(int Color);
void command();
void init();
void help();
void getChar();
float totalRAM();
float availableRAM();
float usedRAM();
void monitorAvailableRAM();
string os();
void clear();
void openBuffer();
void extendBuffer();

int main()
{
    init();
}

void command()
{
    string commandName;
    cppich::print("enter the command : ",cppich::Cyan);
    commandName = cppich::cin(cppich::Green);
    int commandIndex = -1;
    for (int i = 0; i < size(commandList); i++)
    {
        if (commandName == commandList[i])
        {
            commandIndex = i;
            break;
        }
    }
    switch (commandIndex)
    {
    case(0): // help
        help();
        break;
    case(1)://char
        getChar();
        break;
    case(2)://monitor ram
        monitorAvailableRAM();
        break;
    case(3)://clear
        clear();
        break;
    case(4)://open buffer
        openBuffer();
        break;
    case(5)://extend buffer
        extendBuffer();
        break;
    default:
        cout << "error, check the correctness of the command form. To do this, enter 'help'\n";
        command();
        break;
    }
}

void init()
{
    cppich::print("You can enter the command 'help' for help.\n",cppich::Cyan);
    command();
}

void help()
{
    cppich::print("\ncommands list: \n\n", cppich::Cyan);
    for (int i = 0; i < size(commandList); i++)
    {
        cppich::print(commandList[i] + "\n\n",cppich::Cyan);
    }
    command();
}

void getChar()
{
    cppich::print("\t\OS\t\t\t\t" + os() + "\n",cppich::Cyan);
    cppich::print("\t\Total RAM\t\t\t" + to_string(totalRAM() / (1024 * 1024)) + " MB\n",cppich::Cyan);
    cppich::print("\t\Available RAM\t\t\t" + to_string(availableRAM() / (1024 * 1024)) + " MB" + "\t" + to_string(availableRAM() / totalRAM() * 100) + "%\n", cppich::Cyan);
    cppich::print("\t\Used RAM\t\t\t" + to_string(usedRAM() / (1024 * 1024)) + " MB\n", cppich::Cyan);
    command();
}

float totalRAM()
{
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);
    return memInfo.ullTotalPhys;
}

float availableRAM()
{
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);
    return memInfo.ullAvailPhys;
}

float usedRAM()
{
    return totalRAM() - availableRAM();
}

void monitorAvailableRAM()
{
    auto startTime = time(NULL);
    auto endTime = startTime + 10;
    while (time(NULL) != endTime)
    {
        cppich::print("\t\Available  RAM\t\t\t" + to_string(availableRAM() / (1024 * 1024)) + "MB\t" + to_string(availableRAM() / totalRAM() * 100) + "%\n",cppich::Cyan);
    }
    command();
}

string os()
{
    #ifdef _WIN32
        return "Windows";
    #elif __linux__
        return "Linux";
    #elif __APPLE__
        return "Mac os";
    #elif __unix__
        return "Unix like";
    #else
        return "Unknown";
    #endif
}

void clear()
{
    system("cls");
    command();
}

void openBuffer()
{
    ofstream bufMake;
    bufMake.open("buffer.txt", ios::in | ios::out);
    bufMake.close();
    ifstream buffer;
    buffer.open("buffer.txt");
    string str;
    int i = 0;
    while (!buffer.eof())
    {
        i++;
        str = "";
        getline(buffer, str);
        if (str == "")
        {
            break;
        }
        cppich::print(to_string(i) + "=====> " + str + "\n", cppich::Cyan);
    }
    buffer.close();
    command();
}

void extendBuffer()
{
    ofstream bufMake;
    bufMake.open("buffer.txt", ofstream::app);
    string text;
    cppich::print("enter your text\n", cppich::Cyan);
    text = cppich::cin(cppich::Green);
    bufMake << text + "\n";
    bufMake.close();
    command();
}