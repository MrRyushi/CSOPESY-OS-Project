using namespace std;

#include "InputManager.h"
#include <iostream>
#include "ConsoleManager.h"
#include "Screen.h"

InputManager::InputManager()
{
}

// stores the created instance of console manager
InputManager* InputManager::inputManager = inputManager;


void InputManager::initialize()
{
	inputManager = new InputManager();
}

void InputManager::destroy()
{
	delete inputManager;
}

InputManager* InputManager::getInstance()
{
	return inputManager;
}


void InputManager::handleMainConsoleInput()
{
	cout << "Enter a command: ";
	string input;
	cin >> input;

	for (int i = 0; i < input.length(); i++) {
		input[i] = tolower(input[i]);
	}

    if (input == "screen") {
        string screenCommand;
        string processName;
        cin >> screenCommand;

        // creates a new process
        if (screenCommand == "-s") {
            // get the process name
            cin >> processName;
			string timestamp = ConsoleManager::getInstance()->getCurrentTimestamp();
            //Screen screenInstance(processName, 1, 10, timestamp);
            // store the new screen in the screen map

            // Create a new screen instance
            std::shared_ptr<Screen> screenInstance = std::make_shared<Screen>(processName, 1, 10, timestamp);


            //ConsoleManager::getInstance()->getScreenMap()[processName] = screenInstance;

            // Call registerConsole and pass the shared pointer to the Screen instance
            ConsoleManager::getInstance()->registerConsole(screenInstance);

            // Optionally print the size of the screenMap
            cout << "Size of screenMap: " << ConsoleManager::getInstance()->getScreenMap().size() << endl;

            // switch console?? implement switch console first
        }

        // read an existing process
        else if (screenCommand == "-r") {
            cin >> processName;
        }
        else if (input == "exit"){
	        // one option is for the main screen exit and the other for the process screen
        }
    }
}


