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

    if (ConsoleManager::getInstance()->getCurrentConsole()->getConsoleName() == MAIN_CONSOLE) {
        if (input == "initialize") {
            ConsoleManager::getInstance()->setInitialized(true);
			ConsoleManager::getInstance()->initializeConfiguration();

            // start scheduler
			Scheduler::getInstance()->initialize(ConsoleManager::getInstance()->getNumCpu());
            std::thread schedulerThread([&] {
                Scheduler::getInstance()->start();
                });
            schedulerThread.detach();

            cout << "'Processor Configuration Initialized'" << endl;
        } else if (input == "exit") {
            ConsoleManager::getInstance()->exitApplication();
        } else if (ConsoleManager::getInstance()->getInitialized() == true) {
            // SCHEDULER TEST 
            if (input == "scheduler-test") {
                if (Scheduler::getInstance()->getSchedulerTestRunning() == false) {
                    cout << "Scheduler Test now running" << endl;
                    Scheduler::getInstance()->setSchedulerTestRunning(true);
				}
				else {
					cout << "Scheduler Test already running" << endl;
				}
            }
            else if (input == "scheduler-stop") {
                if (Scheduler::getInstance()->getSchedulerTestRunning() == true) {
                    cout << "Scheduler Test stopped" << endl;
                    Scheduler::getInstance()->setSchedulerTestRunning(false);
                }
				else {
					cout << "Scheduler Test not running" << endl;
				}
            }
            else if (input == "report-util") {
                cout << "'report-util' command recognized. Doing something." << endl;
            }
            else if (input == "clear") {
                system("cls");
            }
            else if (input == "screen") {
                string screenCommand;
                string processName;
                cin >> screenCommand;

                if (screenCommand == "-s") {

                    cin >> processName;

                    if (ConsoleManager::getInstance()->getScreenMap().contains(processName)) {
                        cout << "Screen already exists." << endl;
                    }
                    else {
                        string timestamp = ConsoleManager::getInstance()->getCurrentTimestamp();
                        std::shared_ptr<Screen> screenInstance = std::make_shared<Screen>(processName, 0, timestamp);
                        ConsoleManager::getInstance()->registerConsole(screenInstance);

                        ConsoleManager::getInstance()->switchConsole(processName);
                        ConsoleManager::getInstance()->drawConsole();
						Scheduler::getInstance()->addProcessToQueue(screenInstance);
                    }
                }
                else if (screenCommand == "-r") {
                    cin >> processName;
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
            else if (input == "print") {
                cout << "Process name: ";
                string enteredProcess;
                cin >> enteredProcess;
                if (enteredProcess.empty()) { // if the process name is empty
                    std::cout << "Command not recognized! Please provide a process name." << std::endl;
                }
                ConsoleManager::getInstance()->printProcess(enteredProcess);
            }
			else {
				cout << "Command not recognized." << endl;
			}
        }
        else {
            cout << "Please initialize the processor configuration first." << endl;
        }
    } 

    // screen is at process
    else {
        if (input == "exit") {
            ConsoleManager::getInstance()->switchConsole(MAIN_CONSOLE);
        }
		else if (input == "process-smi") {
            ConsoleManager::getInstance()->printProcessSmi();
		}
		else {
			cout << "Command not recognized." << endl;
		}
    }

    
}
    
