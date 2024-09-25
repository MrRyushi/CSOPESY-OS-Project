#include "AConsole.h"
#include "ConsoleManager.h"

#include <stdio.h>
#include <iostream>

using namespace std;

AConsole::AConsole(String name)
{
	AConsole::name = name;
}

void AConsole::display()
{
	String command;
	String screenName;
	String mode;
	
	//temporary
	AConsole* consoleRegister;

	if (ConsoleManager::getInstance()->getCurrentConsole()->name == MAIN_CONSOLE) {
		ConsoleManager::getInstance()->printHeader();

		cout << "Enter a command: ";
		cin >> command;
		cin >> mode;

		if (command == "screen") {
			// fix edge case: if user entered without a parameter, it should display error showing that argument is 
			cin >> screenName;

			cout << "SCREEN NAME: " << screenName << endl;
			//temporary
			//consoleRegister = new AConsole(screenName);

			//ConsoleManager::getInstance()->registerConsole(consoleRegister);
			/*ConsoleManager::getInstance()->switchConsole(consoleRegister);*/

		}
	}
	// change this later on so that it depends on the name of console (through hash table)
	else {
		cout << "This is a screen sample display of process." << endl;

		cout << "Enter a command: ";
		cin >> command; 

		if (command == "exit") {
			//temporary
			//consoleRegister = new AConsole(MAIN_CONSOLE);

			//ConsoleManager::getInstance()->registerConsole(consoleRegister);
			//ConsoleManager::getInstance()->switchConsole(consoleRegister);
		}
	}
}
