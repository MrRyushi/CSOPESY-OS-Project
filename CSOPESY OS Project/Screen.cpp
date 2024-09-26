#include "Screen.h"

Screen::Screen(string processName, int currentLine, int totalLine, string timestamp)
{
	this->processName = processName;
	this->currentLine = currentLine;
	this->totalLine = totalLine;
	this->timestamp = timestamp;
}

Screen::Screen(string processName)
{
	this->processName = processName;
}

Screen::Screen()
{
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
	return processName;
}

int Screen::getCurrentLine()
{
	return currentLine;
}

int Screen::getTotalLine()
{
	return totalLine;
}

string Screen::getTimestamp()
{
	return timestamp;
}

