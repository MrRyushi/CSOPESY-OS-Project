using namespace std;

#include "ConsoleManager.h"
#include <iostream>

// stores the created instance of console manager
ConsoleManager* ConsoleManager::consoleManager = consoleManager;

// default constructor
ConsoleManager::ConsoleManager()
{
    AConsole* currentConsole = nullptr; 
}

void ConsoleManager::drawConsole() {
    this->currentConsole->display();
}

void ConsoleManager::registerConsole(AConsole* screenRef) {
    //TODO: add console to console table
    // -> hash table where key is the name and value is the AConsole pointer
    system("cls");
    this->currentConsole = screenRef; // this is just temporary. current console should be set in switch console function
}

// TODO: implement switch console
// change param to screen name to access hash table later on
void ConsoleManager::switchConsole(AConsole* screenRef)
{
    //add hash table here
    system("cls");
    this->currentConsole = screenRef;
}

AConsole* ConsoleManager::getCurrentConsole()
{
    return this->currentConsole;
}

void ConsoleManager::initialize() {
    consoleManager = new ConsoleManager();
}

ConsoleManager* ConsoleManager::getInstance()
{
    return consoleManager;
}

void ConsoleManager::printHeader() {
    cout << "             ________________________________________________\n";
    cout << "            /                                                \\\n";
    cout << "           |    _________________________________________     |\n";
    cout << "           |   |                                         |    |\n";
    cout << "           |   |                                         |    |\n";
    cout << "           |   |                                         |    |\n";
    cout << "           |   |                    _______ _______      |    |\n";
    cout << "           |   |      .-----.--.--.|       |     __|     |    |\n";
    cout << "           |   |      |  _  |  |  ||   -   |__     |     |    |\n";
    cout << "           |   |      |___  |_____||_______|_______|     |    |\n";
    cout << "           |   |      |_____|                            |    |\n";
    cout << "           |   |                                         |    |\n";
    cout << "           |   |                                         |    |\n";
    cout << "           |   |                                         |    |\n";
    cout << "           |   |_________________________________________|    |\n";
    cout << "           |                                                  |\n";
    cout << "            \\_________________________________________________/\n";
    cout << "   		  \\___________________________________/\n";
    cout << "                ___________________________________________\n";
    cout << "             _-'    .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.  --- -_\n";
    cout << "          _-'.-.-. .---.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.  .-.-.-_\n";
    cout << "       _-'.-.-.-. .---.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-__. .-.-.-.-_\n";
    cout << "    _-'.-.-.-.-. .-----.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-----. .-.-.-.-.-_\n";
    cout << " _-'.-.-.-.-.-. .---.-. .-------------------------. .-.---. .---.-.-.-.-_\n";
    cout << ":-------------------------------------------------------------------------:\n";
    cout << "---._.-------------------------------------------------------------._.---'\n";
    cout << "\n________________________________________________________________________________\n";
	cout << "\n";
}