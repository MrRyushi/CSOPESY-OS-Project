using namespace std;

#include "ConsoleManager.h"
#include <iostream>
#include <unordered_map>

// stores the created instance of console manager
ConsoleManager* ConsoleManager::consoleManager = consoleManager;

// default constructor
ConsoleManager::ConsoleManager()
{
    AConsole* currentConsole = nullptr; 
}

void ConsoleManager::initialize() {
    consoleManager = new ConsoleManager();
}

void ConsoleManager::drawConsole() {
    //this->currentConsole->display();
    this->printHeader();
}

void ConsoleManager::destroy() {
    delete consoleManager;
}

string ConsoleManager::getCurrentTimestamp() {
    // Get current time as time_t object
    std::time_t currentTime = std::time(nullptr);
    // Create tm structure to store local time
    std::tm localTime;
    // Convert time_t to tm structure 
    localtime_s(&localTime, &currentTime);
    // Create a buffer to store the formatted time
    char timeBuffer[100];
    // Format the time (MM/DD/YYYY, HH:MM:SS AM/PM)
    std::strftime(timeBuffer, sizeof(timeBuffer), "%m/%d/%Y, %I:%M:%S %p", &localTime);
    return timeBuffer;
   
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


ConsoleManager* ConsoleManager::getInstance()
{
    return consoleManager;
}

std::unordered_map<std::string, Screen> ConsoleManager::getScreenMap() {
    return this->screenMap;
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