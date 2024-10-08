#include "Screen.h"
#include <fstream> 
#include <filesystem> // for folder creation

namespace fs = std::filesystem; // alias for convenience

Screen::Screen(string processName, int currentLine, int totalLine, string timestamp)
    : BaseScreen(processName), cpuCoreID(-1), commandCounter(0), currentState(ProcessState::READY)
{
    this->processName = processName;
    this->currentLine = currentLine;
    this->totalLine = totalLine;
    this->timestamp = timestamp;
}


Screen::~Screen()
{
}

void Screen::setProcessName(string processName)
{
	this->processName = processName;
}

void Screen::setCurrentLine(int currentLine)
{
	this->currentLine = currentLine;
}

void Screen::setTotalLine(int totalLine)
{
	this->totalLine = totalLine;
}

void Screen::setTimestamp(string timestamp)
{
	this->timestamp = timestamp;
}

string Screen::getProcessName()
{
	return this->processName;
}

int Screen::getCurrentLine()
{
	return this->currentLine;
}

int Screen::getTotalLine()
{
	return this->totalLine;
}

string Screen::getTimestamp()
{
	return this->timestamp;
}


void Screen::executeCurrentCommand() const
{
	std::cout << this->printCommands[this->currentLine] << std::endl;
}

void Screen::moveToNextLine()
{
	this->currentLine++;
}

bool Screen::isFinished() const
{
	return this->currentLine >= this->totalLine;
}

int Screen::getCommandCounter() const
{
	return this->commandCounter;
}

int Screen::getCPUCoreID() const
{
	return this->cpuCoreID;
}

Screen::ProcessState Screen::getState() const
{
	return this->currentState;
}

