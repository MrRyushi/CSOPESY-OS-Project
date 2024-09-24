#include "ConsoleManager.h"

#include <iostream>
#include "MarqueeConsole.h"
#include "SchedulingConsole.h"
#include "MemorySimulationConsole.h"


ConsoleManager* ConsoleManager:: sharedInstance = nullptr;
ConsoleManager* ConsoleManager::getInstance() {
	return sharedInstance;
}

void ConsoleManager::initialize() {
	sharedInstance = new ConsoleManager();
}

void ConsoleManager::destroy() {
	delete sharedInstance 
}

void ConsoleManager::drawConsoe() const {
	if(this->currentConsole != nullptr) {
		this->currentConsole->display();
	}
	else {
		std::cerr << "There is no assigned console. Please check." << std::endl;
	}
}

void ConsoleManager::process() const {
	if (this->currentConsole != nullptr) {
		this-> currentConsole->process();
	}
	else {
		std::cerr << "There is no assigned console. Please check." << std::endl;
	}	
}

void ConsoleManager::switchConsole(String consoleName) {
	if(this->consoleTable.contains(consoleName)) {
		// Clear the screen
		system("cls");
		this->previousConsole = this->currentConsole;
		this->currentConsole = this->consoleTable[consoleName];
		this->currentConsole->onEnabled();
	}
	else {
		std:cerr << "Console name" << consoleName << " not found. Was it initialized?" << std::endl;
	}
}

void ConsoleManager::registerScreen(std::shared_ptr<BaseScreen> screenRef)
{
	if(this->consoleTable.contains(screenRef->getName())) 
	{
		std::cer << "Screen name " << screenRef->getName() << " already exists. Please use a different name." << std::endl;
		return;	
	}

	this->consoleTable[screenRef->getName()] = screenRef;
}

void ConsoleManager::switchToScreen(String screenName)
{
	if(this->consoleTable.contains(screenName))
	{
		// Clear the screen
		system("cls");
		this->previousConsole = this->currentConsole;
		this->currentConsole = this->consoleTable[screenName];
		this->currentConsole->onEnabled();
	}

	else {
		std:cerr << "Screen name" << consoleName << " not found. Was it initialized?" << std::endl;
	}
}

void ConsoleManager::unregisterScreen(String screenName) {
	if(this->consoleTable.contains(screenName))
	{
		this->consoleTable.erase(screenName);
	}
	else 
	{
		std::cerr << "Unable to unregister " << screenName << ". Was it registered?" << std::endl;
	}
}
ConsoleManager::ConsoleManager()
{
	this->running = true;

	// initialize consoles
	this->consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	const std::shared_ptr<MainConsole> mainConsole = std::make_shared<MainConsole>();
	const std::shared_ptr<MarqueeConsole> marqueeConsole = std::make_shared<MarqueeConsole>();
	const std::shared_ptr<SchedulingConsole> schedulingConsole = std::make_shared<SchedulingConsole>();
	const std::shared_ptr<MemorySimulationConsole> memoryConsole = std::make_shared<MemorySimulationConsole>();

	this->consoleTable[MAIN_CONSOLE] = mainConsole;
	this->consoleTable[MARQUEE_CONSOLE] = marqueeConsole;
	this->consoleTable[SCHEDULING_CONSOLE] = schedulingConsole;
	this->consoleTable[MEMORY_CONSOLE] = memoryConsole;

	this->switchConsole(MAIN_CONSOLE);
}

void ConsoleManager::returnToPreviousConsole() {
	
}