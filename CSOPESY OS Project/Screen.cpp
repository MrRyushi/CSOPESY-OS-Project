#include "Screen.h"

Screen::Screen(string processName, int currentLine, int totalLine, string timestamp): BaseScreen(processName)
{
	this->processName = processName;
	this->currentLine = currentLine;
	this->totalLine = totalLine;
	this->timestamp = timestamp;
}

//Screen::Screen(string processName): BaseScreen(processName)
//{
//	
//}

//Screen::Screen()
//{
//}

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

//void Screen::drawScreen()
//{
//	cout << "This is a sample screen." << endl;
//}

