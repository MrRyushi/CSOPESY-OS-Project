/**
*  CSOPESY OS Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
*  CSOPESY - S16 (Group 11)
*  Members:
*          - CAASI, SAMANTHA NICOLE LINTAG
*          - GUTIERREZ, CARLOS KRISTOFFER PABALAN
*          - MARCELLANA, JOHN PATRICK TABERNILLA
*          - SAYO, TRISHA ALISSANDRA
*  
*  Submitted to: Prof. Neil Patrick Del Gallego
**/

using namespace std;

#include <iostream>
#include <cctype>
#include <vector>
#include <ctime>
#include "ConsoleManager.h"
#include "InputManager.h"
/*
// structure to represent a screen process
struct Screen {
    string processName;
    int currentLine;
    int totalLine;
    string timestamp;
};

vector<string> outputHistory;
vector<Screen> screens;
ConsoleManager consoleManager;

void newLine() {
    cout << "\n";
}

void clearScreen() {
    system("cls");
	consoleManager.printHeader();
}

void clearOutputHistory() {
	outputHistory.clear();
}

void displayOutputHistory() {
	for (int i = 0; i < outputHistory.size(); i++) {
		cout << outputHistory[i] << endl;
	}
}

string getCurrentTimestamp() {
    // Get current time as time_t object
    std::time_t currentTime = std::time(nullptr);
    // Create tm structure to store local time
    std::tm localTime;
    // Convert time_t to tm structure 
    localtime_s(&localTime, &currentTime);
    // Create a buffer to store the formatted time
    char timeBuffer[100];
    // Format the time (MM/DD/YYYY, HH:MM:SS AM/PM)
    std::strftime(timeBuffer, sizeof(timeBuffer), "%m/%d/%Y, %I:%M:%S %p", &localTime);
    return timeBuffer;
}

void storeOutput(string text) {
	outputHistory.push_back(text);
}

void displayScreen(Screen screen) {
    cout << "Process name: " << screen.processName << endl;
    cout << "Line: " << screen.currentLine << " of " << screen.totalLine << endl;
    cout << "Created on: " << screen.timestamp << endl;
    cout << "Type 'exit' to return to the main menu" << endl;
    
    string processCommand;
    while (processCommand != "exit") {
        cout << "Enter command: ";
        cin >> processCommand;
    }
    clearScreen();
	displayOutputHistory();
}
*/
/*
void handleCommands() {
    string command = "";

    while (command != "exit") {
        cout << "Enter command: ";
        cin >> command;
        if (command != "screen") {
            storeOutput("Enter command: " + command);
        }

        // insert code that converts command variable to lowercase
        for (int i = 0; i < command.length(); i++) {
            command[i] = tolower(command[i]);
        }

        if (command == "initialize") {
            cout << "'initialize' command recognized. Doing something.";
            newLine();
            storeOutput("'initialize' command recognized. Doing something.");
        }
        else if (command == "scheduler-test") {
            cout << "'scheduler-test' command recognized. Doing something.";
            newLine();
            storeOutput("'scheduler-test' command recognized. Doing something.");
        }
        else if (command == "scheduler-stop") {
            cout << "'scheduler-stop' command recognized. Doing something.";
            newLine();
            storeOutput("'scheduler-stop' command recognized. Doing something.");
        }
        else if (command == "report-util") {
            cout << "'report-util' command recognized. Doing something.";
            newLine();
            storeOutput("'report-util' command recognized. Doing something.");
        }
        else if (command == "clear") {
            clearScreen();
        }
        else if (command == "screen") {
            string screenCommand;
            string processName;
            cin >> screenCommand;

            // creates a new process
            if (screenCommand == "-s") {
                // get the process name
                cin >> processName;
                storeOutput("Enter command: screen " + screenCommand + " " + processName);

                // Check if processName already exists in the vector
                bool processExists = false;
                for (int i = 0; i < screens.size(); i++) {
                    if (screens[i].processName == processName) {
                        processExists = true;
                        break;
                    }
                }

                if (processExists) {
                    cout << "Error: process name already exists" << endl;
                }
                else if (!processName.empty()) {
                    // If the process name doesn't exist and is not empty, add a new screen
                    Screen newScreen = { processName, 1, 10, getCurrentTimestamp() };
                    screens.push_back(newScreen);
                    system("cls");
                    displayScreen(newScreen);
                }
            }

            // read an existing process
            else if (screenCommand == "-r") {
                cin >> processName;
                storeOutput("Enter command: screen " + screenCommand + " " + processName);

                bool processFound = false;  // Flag to check if processName is found

                for (int i = 0; i < screens.size(); i++) {
                    if (screens[i].processName == processName) {
                        processFound = true;
                        system("cls");
                        displayScreen(screens[i]);
                        break;  // Exit loop after finding the process
                    }
                }

                if (!processFound) {
                    cout << "Error: process name not found" << endl;
                }
            }


 

        }
        else if (command != "exit") {
            cout << "'" << command << "' command not recognized.";
            newLine();
			storeOutput("'" + command + "' command not recognized.");
        }
    }
}
*/

int main()
{
    ConsoleManager::initialize();
	InputManager::initialize();

    // this should be called when displaying main console 
    //ConsoleManager::getInstance()->printHeader();

    // register main screen
    ConsoleManager::getInstance()->registerConsole(new AConsole(MAIN_CONSOLE));
    
    
    bool running = true;
    ConsoleManager::getInstance()->drawConsole();
    while (running) {
        InputManager::getInstance()->handleMainConsoleInput();
    }
    
	InputManager::getInstance()->destroy();
    ConsoleManager::getInstance()->destroy();
}

