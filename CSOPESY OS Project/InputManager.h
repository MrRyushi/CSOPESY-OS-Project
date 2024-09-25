#pragma once
#include <unordered_map>

#include "AConsole.h"
#include "Screen.h"

class InputManager
{
public:
	InputManager();
	static void initialize();
	static InputManager* getInstance();
	void handleMainConsoleInput();
	void destroy();

private:
	static InputManager* inputManager;

	//unordered_map<String, std::shared_ptr<Screen>> screenMap;
};

