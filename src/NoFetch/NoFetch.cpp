#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include <map>
using namespace std;

HANDLE hConsole;

map<string, int> colors;
string commandList[] = {"help"};

void SetTextColor(int Color);
void command();
void init();
void help();

int main()
{
    init();

    SetTextColor(colors["Fetch"]);
}

void SetTextColor(int Color)
{
    SetConsoleTextAttribute(hConsole, Color);
}

void command()
{
    string command;
    SetTextColor(colors["Fetch"]);
    cout << "enter the command : ";
    SetTextColor(colors["Command"]);
    cin >> command;
    int commandIndex = -1;
    for (int i = 0; i < size(commandList); i++)
    {
        if (command == commandList[i])
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
    default:
        cout << "error, check the correctness of the command form. To do this, enter 'help'";
        break;
    }
}

void init()
{
    colors["Fetch"] = 3;
    colors["Command"] = 2;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetTextColor(colors["Fetch"]);
    cout << "You can enter the command 'help' for help.\n";

    command();
}
void help()
{
    SetTextColor(colors["Fetch"]);
    cout << "\ncommands list: \n\n";
    for (int i = 0; i < size(commandList); i++)
    {
        cout << commandList[i] << "\n\n";
    }
}