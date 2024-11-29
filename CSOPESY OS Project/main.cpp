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
#include "FlatMemoryAllocator.h"
#include <fstream>
#include <random>
#include "PagingAllocator.h"



int main()
{
    ConsoleManager::initialize();
	InputManager::initialize();

    shared_ptr<BaseScreen> mainScreen = make_shared<MainScreen>(MAIN_CONSOLE);

    ConsoleManager::getInstance()->registerConsole(mainScreen);
    ConsoleManager::getInstance()->setCurrentConsole(mainScreen);
    
    bool running = true;
    ConsoleManager::getInstance()->drawConsole();
	size_t maxOverallMem = ConsoleManager::getInstance()->getMaxOverallMem();

    FlatMemoryAllocator::initialize(maxOverallMem);
    PagingAllocator::initialize(maxOverallMem);

    while (running){
        InputManager::getInstance()->handleMainConsoleInput();
        running = ConsoleManager::getInstance()->isRunning();
    }
    
	InputManager::getInstance()->destroy();
    ConsoleManager::getInstance()->destroy();

    return 0;
}

