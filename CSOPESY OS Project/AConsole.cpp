#include "AConsole.h"

AConsole::AConsole(String name)
{
	AConsole::name = name;
}

std::string AConsole::getName()
{
	return AConsole::name;
}
