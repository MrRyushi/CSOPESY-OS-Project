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
    getline(cin, input); // Capture entire line input

    // Convert input to lowercase
    for (char &c : input) {
        c = tolower(c);
    }

    // Split input by spaces
    istringstream iss(input);
    vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}};

    if (tokens.empty()) {
        cout << "No command entered." << endl;
        return;
    }

    string command = tokens[0];

    // Check initialization state once
    if (!ConsoleManager::getInstance()->getInitialized() && command != "initialize") {
        cout << "Please initialize the processor configuration first." << endl;
        return;
    }

    // Main Console commands
    if (ConsoleManager::getInstance()->getCurrentConsole()->getConsoleName() == MAIN_CONSOLE) {
        if (command == "initialize") {
            ConsoleManager::getInstance()->setInitialized(true);
            ConsoleManager::getInstance()->initializeConfiguration();

            // Start scheduler
            Scheduler::getInstance()->initialize(ConsoleManager::getInstance()->getNumCpu());
            std::thread schedulerThread([&] {
                Scheduler::getInstance()->start();
            });
            schedulerThread.detach();

            cout << "'Processor Configuration Initialized'" << endl;
        }
        else if (command == "exit") {
            ConsoleManager::getInstance()->exitApplication();
        }
        else if (command == "scheduler-test") {
            if (!Scheduler::getInstance()->getSchedulerTestRunning()) {
                cout << "Scheduler Test now running" << endl;
                Scheduler::getInstance()->setSchedulerTestRunning(true);
                // create batchProcessFrequency number of processes
                std::thread schedulerTestThread([&] {
					ConsoleManager::getInstance()->schedulerTest();
                    });
                schedulerTestThread.detach();
               
            }
            else {
                cout << "Scheduler Test already running" << endl;
            }
        }
        else if (command == "scheduler-stop") {
            if (Scheduler::getInstance()->getSchedulerTestRunning()) {
                cout << "Scheduler Test stopped" << endl;
                Scheduler::getInstance()->setSchedulerTestRunning(false);
            }
            else {
                cout << "Scheduler Test not running" << endl;
            }
        }
        else if (command == "report-util") {
            ConsoleManager::getInstance()->reportUtil();
        }
        else if (command == "clear") {
            system("cls");
            ConsoleManager::getInstance()->drawConsole();
        }
        else if (command == "screen") {
            if (tokens.size() > 1) {
                string screenCommand = tokens[1];
                string processName = (tokens.size() > 2) ? tokens[2] : "";

                if (screenCommand == "-s" && !processName.empty()) {
                    if (ConsoleManager::getInstance()->getScreenMap().contains(processName)) {
                        cout << "Screen already exists." << endl;
                    }
                    else {
                        string timestamp = ConsoleManager::getInstance()->getCurrentTimestamp();
                        auto screenInstance = std::make_shared<Screen>(processName, 0, timestamp);
                        ConsoleManager::getInstance()->registerConsole(screenInstance);

                        ConsoleManager::getInstance()->switchConsole(processName);
                        ConsoleManager::getInstance()->drawConsole();
                        Scheduler::getInstance()->addProcessToQueue(screenInstance);
                    }
                }
                else if (screenCommand == "-r" && !processName.empty()) {
                    ConsoleManager::getInstance()->switchConsole(processName);
                    ConsoleManager::getInstance()->drawConsole();
                }
                else if (screenCommand == "-ls") {
                    ConsoleManager::getInstance()->displayProcessList();
                }
                else {
                    cout << "Command not recognized." << endl;
                }
            }
            else {
                cout << "Command not recognized." << endl;
            }
        }
        else {
            cout << "Command not recognized." << endl;
        }
    }
    else {
        // Process-specific commands
        if (command == "exit") {
            ConsoleManager::getInstance()->switchConsole(MAIN_CONSOLE);
        }
        else if (command == "process-smi") {
            ConsoleManager::getInstance()->printProcessSmi();
        }
        else {
            cout << "Command not recognized." << endl;
        }
    }
}

    
