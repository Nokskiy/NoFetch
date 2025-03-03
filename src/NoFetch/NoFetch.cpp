#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include <map>
using namespace std;

HANDLE hConsole;

map<string, int> colors;
string commandList[] = {"help","sys_char","monitor_avail_RAM"};

void setTextColor(int Color);
void command();
void init();
void help();
void getChar();
float totalRAM();
float availableRAM();
void monitorAvailableRAM();

int main()
{
    init();

    setTextColor(colors["Fetch"]);
}

void setTextColor(int Color)
{
    SetConsoleTextAttribute(hConsole, Color);
}

void command()
{
    string commandName;
    setTextColor(colors["Fetch"]);
    cout << "enter the command : ";
    setTextColor(colors["Command"]);
    cin >> commandName;
    int commandIndex = -1;
    for (int i = 0; i < size(commandList); i++)
    {
        if (commandName == commandList[i])
        {
            commandIndex = i;
            break;
        }
    }
    if (commandIndex == -1)
    {

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
    default:
        cout << "error, check the correctness of the command form. To do this, enter 'help'\n";
        command();
        break;
    }
}

void init()
{
    colors["Fetch"] = 3;
    colors["Command"] = 2;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    setTextColor(colors["Fetch"]);
    cout << "You can enter the command 'help' for help.\n";

    command();
}

void help()
{
    setTextColor(colors["Fetch"]);
    cout << "\ncommands list: \n\n";
    for (int i = 0; i < size(commandList); i++)
    {
        cout << commandList[i] << "\n\n";
    }
    command();
}

void getChar()
{
    setTextColor(colors["Fetch"]);
    cout << "\t\Total RAM\t\t\t" << totalRAM() / (1024 * 1024) << "MB" << "\n";
    cout << "\t\Available  RAM\t\t\t" <<  availableRAM()/ (1024 * 1024)<<"MB" <<"\t"<< availableRAM() / totalRAM() *100 << "%" << "\n";
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
void monitorAvailableRAM()
{
    auto startTime = time(NULL);
    auto endTime = startTime + 10;
    setTextColor(colors["Fetch"]);
    while (time(NULL) != endTime)
    {
        cout << "\t\Available  RAM\t\t\t" << availableRAM() / (1024 * 1024) << "MB" << "\t" << availableRAM() / totalRAM() * 100 << "%" << "\n";
    }
    command();
}