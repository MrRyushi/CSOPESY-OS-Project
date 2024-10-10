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
#include "Scheduler.h"
#include <fstream>



int main()
{
    ConsoleManager::initialize();
	InputManager::initialize();

    Scheduler::initialize(4);

    std::ofstream files[10];

    // create 10 processes each with 100 commands
    for (int i = 0; i < 10; i++) {
        string processName = "Process" + to_string(i);
        shared_ptr<BaseScreen> processScreen = make_shared<Screen>(processName, 0, 100, ConsoleManager::getInstance()->getCurrentTimestamp());
        ConsoleManager::getInstance()->registerConsole(processScreen);
        // Cast processScreen to shared_ptr<Screen>
        shared_ptr<Screen> screenPtr = static_pointer_cast<Screen>(processScreen);
        Scheduler::getInstance()->addProcessToQueue(screenPtr);
    }

    std::thread schedulerThread([&] {
        Scheduler::getInstance()->start();
        });
    schedulerThread.detach();
    
    // register main screen
    shared_ptr<BaseScreen> mainScreen = make_shared<MainScreen>(MAIN_CONSOLE);

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

