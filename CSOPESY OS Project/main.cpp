/**
*  CSOPESY OS Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
*  CSOPESY - S16 (Group 11)
*  Members:
*          - CAASI, SAMANTHA NICOLE LINTAG
*          - GUTIERREZ, CARLOS KRISTOFFER PABALAN
*          - MARCELLANA, JOHN PATRICK TABERNILLA
*          - SAYO, TRISHA ALISSANDRA
*  
*  Submitted to: Prof. Neil Patrick Del Gallego
**/

using namespace std;

#include <iostream>
#include <cctype>
#include <vector>
#include <ctime>
#include "ConsoleManager.h"
#include "InputManager.h"
#include "BaseScreen.h"
#include "MainScreen.h"

int main()
{
    ConsoleManager::initialize();
	InputManager::initialize();

    // create 10 processes each with 100 commands
    for (int i = 0; i < 10; i++) {
        string processName = "Process" + to_string(i);
        std::shared_ptr<BaseScreen> processScreen = std::make_shared<Screen>(processName, 1, 100, ConsoleManager::getInstance()->getCurrentTimestamp());
        ConsoleManager::getInstance()->registerConsole(processScreen);
    }

    // register main screen
    std::shared_ptr<BaseScreen> mainScreen = std::make_shared<MainScreen>(MAIN_CONSOLE);

    ConsoleManager::getInstance()->registerConsole(mainScreen);
    ConsoleManager::getInstance()->setCurrentConsole(mainScreen);
    
    bool running = true;
    ConsoleManager::getInstance()->drawConsole();

    while (running){
        InputManager::getInstance()->handleMainConsoleInput();
        running = ConsoleManager::getInstance()->isRunning();
    }
    
	InputManager::getInstance()->destroy();
    ConsoleManager::getInstance()->destroy();

    return 0;
}

