using namespace std;

#include "ConsoleManager.h"
#include <iostream>
#include <unordered_map>
#include "Screen.h"

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
    system("cls");
    string consoleName = this->getCurrentConsole()->getConsoleName();

    if (this->getCurrentConsole()->getConsoleName() == MAIN_CONSOLE) {
        this->printHeader();
    }
    else {
        if (this->screenMap.contains(consoleName)) {
            cout << "Screen Name: " << this->screenMap[consoleName]->getConsoleName() << endl;
            cout << "Current line of instruction / Total line of instruaction: ";
            cout << this->screenMap[consoleName]->getCurrentLine();
            cout << "/" << this->screenMap[consoleName]->getTotalLine() << endl;
            cout << "Timestamp: " << this->screenMap[consoleName]->getTimestamp() << endl;
        }
    }
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

void ConsoleManager::registerConsole(std::shared_ptr<BaseScreen> screenRef) {
    //TODO: add console to console table
    this->screenMap[screenRef->getConsoleName()] = screenRef; //it should accept MainScreen and ProcessScreen

    // -> hash table where key is the name and value is the AConsole pointer
    system("cls");
    //this->currentConsole = screenRef; // this is just temporary. current console should be set in switch console function
}

// TODO: implement switch console
// change param to screen name to access hash table later on
void ConsoleManager::switchConsole(string consoleName)
{
    //add hash table here
    if (this->screenMap.contains(consoleName)) {
        // Clear the screen
        /*system("cls");*/
        //TODO: make this work
        /*this->previousConsole = this->currentConsole;*/
        this->currentConsole = this->screenMap[consoleName];

        if (consoleName == MAIN_CONSOLE){
            this->drawConsole();
        }

        /*this->currentConsole->onEnabled();*/
    }
    else {
    cout << "Console name" << consoleName << " not found. Was it initialized?" << endl;
    }
}

std::shared_ptr<BaseScreen> ConsoleManager::getCurrentConsole()
{
    return this->currentConsole;
}

void ConsoleManager::setCurrentConsole(std::shared_ptr<BaseScreen> screenRef)
{
    this->currentConsole = screenRef;
}


ConsoleManager* ConsoleManager::getInstance()
{
    return consoleManager;
}

void ConsoleManager::exitApplication() {
    this->running = false;
}

bool ConsoleManager::isRunning() {
    return this->running;
}

std::unordered_map<std::string, std::shared_ptr<BaseScreen>> ConsoleManager::getScreenMap() {
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
    
    /*cout << "MEOW MEOW MOEW" << endl;*/
}