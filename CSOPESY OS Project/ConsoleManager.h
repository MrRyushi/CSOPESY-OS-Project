#pragma once
#include "AConsole.h"

const String MAIN_CONSOLE = "MAIN_CONSOLE";

class ConsoleManager
{	
public:
	// default constructor
	ConsoleManager();

	// we can run this to create a console manager pointer
	static void initialize();

	// we get the console manager instance after 
	static ConsoleManager* getInstance();

	void printHeader();
	void drawConsole();

	void registerConsole(AConsole* screenRef);
	void switchConsole(AConsole* screenRef);
	AConsole* getCurrentConsole();

private:
	// stores the console manager pointer so that we only instantiate once
	static ConsoleManager* consoleManager;

	// declare consoles 
	AConsole* currentConsole;
};