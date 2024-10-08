#pragma once
using namespace std;

#include "ConsoleManager.h"
#include <iostream>
#include <unordered_map>
#include "Screen.h"


// stores the created instance of console manager
ConsoleManager* ConsoleManager::consoleManager = nullptr;

ConsoleManager::ConsoleManager() : scheduler(4) {}

void ConsoleManager::initialize() {
    consoleManager = new ConsoleManager();
    consoleManager->scheduler.start(); // Start the scheduler
}

void ConsoleManager::drawConsole() {
    if (this->switchSuccessful) {
        system("cls");
        string consoleName = this->getCurrentConsole()->getConsoleName();

        if (this->getCurrentConsole()->getConsoleName() == MAIN_CONSOLE) {
            this->printHeader();
        }
        else {
            if (this->screenMap.contains(consoleName)) {
                cout << "Screen Name: " << this->screenMap[consoleName]->getConsoleName() << endl;
                cout << "Current line of instruction / Total line of instruction: ";
                cout << this->screenMap[consoleName]->getCurrentLine();
                cout << "/" << this->screenMap[consoleName]->getTotalLine() << endl;
                cout << "Timestamp: " << this->screenMap[consoleName]->getTimestamp() << endl;
            }
        }
    }
}

void ConsoleManager::destroy() {
    consoleManager->scheduler.stop(); // Stop the scheduler
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
    this->screenMap[screenRef->getConsoleName()] = screenRef; //it should accept MainScreen and ProcessScreen
    system("cls");
}

void ConsoleManager::switchConsole(string consoleName)
{
    if (this->screenMap.contains(consoleName)) {
        this->currentConsole = this->screenMap[consoleName];

        if (consoleName == MAIN_CONSOLE) {
            this->drawConsole();
        }
        this->switchSuccessful = true;
    }
    else {
        cout << "Console name " << consoleName << " not found. Was it initialized?" << endl;
        this->switchSuccessful = false;
    }
}

void ConsoleManager::displayProcessList() {
    std::cout << "Running processes:" << std::endl;
    for (const auto& pair : screenMap) {
        std::shared_ptr<Screen> screenPtr = std::dynamic_pointer_cast<Screen>(pair.second);

        if (screenPtr && !screenPtr->isFinished()) {
            std::cout << screenPtr->getProcessName() << " "
                << screenPtr->getTimestamp() << " "
                << "core:" << screenPtr->getCPUCoreID() << " "
                << screenPtr->getCurrentLine() << "/"
                << screenPtr->getTotalLine() << std::endl;
        }
    }

    std::cout << "\nFinished processes:" << std::endl;
    for (const auto& pair : screenMap) {
        std::shared_ptr<Screen> screenPtr = std::dynamic_pointer_cast<Screen>(pair.second);

        if (screenPtr && screenPtr->isFinished()) {
            std::cout << screenPtr->getProcessName() << " "
                << screenPtr->getTimestamp() << " "
                << "core:" << screenPtr->getCPUCoreID() << " "
                << screenPtr->getCurrentLine() << "/"
                << screenPtr->getTotalLine() << std::endl;
        }
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
    cout << "              \\___________________________________/\n";
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
