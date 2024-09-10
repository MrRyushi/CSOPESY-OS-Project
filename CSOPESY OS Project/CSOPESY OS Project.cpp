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


void header() {
    cout << "             ________________________________________________\n";
    cout << "            /                                                \\\n";
    cout << "           |    _________________________________________     |\n";
    cout << "           |   |                                         |    |\n";
    cout << "           |   |                                         |    |\n";
    cout << "           |   |                                         |    |\n";
    cout << "           |   |                    _______ _______      |    |\n";
    cout << "           |   |      .-----.--.--.|       |     __|     |    |\n";
    cout << "           |   |      |  _  |  |  ||   -   |__     |     |    |\n";
    cout << "           |   |      |___  |_____||_______|_______|     |    |\n";
    cout << "           |   |      |_____|                            |    |\n";
    cout << "           |   |                                         |    |\n";
    cout << "           |   |                                         |    |\n";
    cout << "           |   |                                         |    |\n";
    cout << "           |   |_________________________________________|    |\n";
    cout << "           |                                                  |\n";
    cout << "            \\_________________________________________________/\n";
    cout << "   		  \\___________________________________/\n";
    cout << "                ___________________________________________\n";
    cout << "             _-'    .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.  --- -_\n";
    cout << "          _-'.-.-. .---.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.  .-.-.-_\n";
    cout << "       _-'.-.-.-. .---.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-__. .-.-.-.-_\n";
    cout << "    _-'.-.-.-.-. .-----.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-----. .-.-.-.-.-_\n";
    cout << " _-'.-.-.-.-.-. .---.-. .-------------------------. .-.---. .---.-.-.-.-_\n";
    cout << ":-------------------------------------------------------------------------:\n";
    cout << "---._.-------------------------------------------------------------._.---'\n";
    cout << "\n________________________________________________________________________________\n";
}
void newLine() {
    cout << "\n";
}

void help() {
    cout << "List of commands:\n";
    cout << "initialize     - Initializes the program\n";
    cout << "screen         - Displays the screen\n";
    cout << "scheduler-test - Tests the scheduler\n";
    cout << "scheduler-stop - Stops the scheduler\n";
    cout << "report-util    - Generates a report\n";
    cout << "clear          - Clears the screen\n";
    cout << "help           - Displays the list of commands\n";
    cout << "exit           - Exits the program\n";
}

int main()
{
    header();
    newLine();
    help();
    string command = "";

    while (command != "exit") {
        cout << "Enter command: ";
        cin >> command;
        // insert code that converts command variable to lowercase
        for (int i = 0; i < command.length(); i++) {
            command[i] = tolower(command[i]);
        }

        if (command == "initialize") {
            cout << "'initialize' command recognized. Doing something.";
            newLine();
        }
        else if (command == "screen") {
            cout << "'screen' command recognized. Doing something.";
            newLine();
        }
        else if (command == "scheduler-test") {
            cout << "'scheduler-test' command recognized. Doing something.";
            newLine();
        }
        else if (command == "scheduler-stop") {
            cout << "'scheduler-stop' command recognized. Doing something.";
            newLine();
        }
        else if (command == "report-util") {
            cout << "'report-util' command recognized. Doing something.";
            newLine();
        }       
        else if (command == "clear") {
            system("cls");
            header();
        }
        else if (command == "help") {
            help();
        }
        else if (command != "exit") {
            cout << "'" << command << "' command not recognized.";
            newLine();
        }
    }

    return 0;
}

