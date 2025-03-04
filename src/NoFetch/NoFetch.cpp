#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include <map>
#include <fstream>
#include <string>

using namespace std;

HANDLE hConsole;

map<string, int> colors;
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
        setTextColor(colors["Error"]);
        cout << "error, check the correctness of the command form. To do this, enter 'help'\n";
        command();
        break;
    }
}

void init()
{
    colors["Fetch"] = 3;
    colors["Command"] = 2;
    colors["Error"] = 5;
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
    cout << "\t\OS\t\t\t\t" << os() << "\n";
    cout << "\t\Total RAM\t\t\t" << totalRAM() / (1024 * 1024) << " MB" << "\n";
    cout << "\t\Available RAM\t\t\t" << availableRAM() / (1024 * 1024) << " MB" << "\t" << availableRAM() / totalRAM() * 100 << "%" << "\n";
    cout << "\t\Used RAM\t\t\t" << usedRAM() / (1024 * 1024) << " MB\n";
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
    setTextColor(colors["Fetch"]);
    while (time(NULL) != endTime)
    {
        cout << "\t\Available  RAM\t\t\t" << availableRAM() / (1024 * 1024) << "MB" << "\t" << availableRAM() / totalRAM() * 100 << "%" << "\n";
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
    setTextColor(colors["Fetch"]);
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
        cout << i << "=====> " << str << "\n";
    }
    buffer.close();
    command();
}

void extendBuffer()
{
    setTextColor(colors["Fetch"]);
    ofstream bufMake;
    bufMake.open("buffer.txt", ofstream::app);
    string text;
    cout << "text: ";
    cin.ignore();
    getline(cin, text);
    bufMake << text + "\n";
    bufMake.close();
    command();
}