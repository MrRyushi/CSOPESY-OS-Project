#include "Process.h"

void Process::executeCurrentCommand() const
{
	//this->commandList[this->commandCounter]->execute();
}

void Process::moveToNextLine()
{
	this->commandCounter++;
}