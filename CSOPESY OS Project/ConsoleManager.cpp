#include "ConsoleManager.h"
#include "AConsole.h"

AConsole* ConsoleManager::getInstance()
{
	return new AConsole();
}
