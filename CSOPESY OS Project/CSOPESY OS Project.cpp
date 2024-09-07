// CSOPESY OS Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

using namespace std;

#include <iostream>
#include <cctype>


void header() {
    cout << "  ------     -------      ------     -------  \n";
    cout << "/        |  /        |   /      \\   |   --   \\\n";
    cout << "|     ---   |     ---   |        |  |  |  |  |\n";
    cout << "|    |      |    |      |   ---  |  |   --   /\n";
    cout << "|    |      |     ---   |  |   | |  |   -----\n";
    cout << "|    |      \\        \\  |  |   | |  |  |\n";
    cout << "|    |       ---     |  |  |   | |  |  |\n";
    cout << "|    |          |    |  |   ---  |  |  |\n";
    cout << "|     ---    ---     |  |        |  |  |\n";
    cout << "\\        |  |        /   \\       /  |  |\n";
    cout << " --------    --------     ------     --  \n";
}
void newLine() {
    cout << "\n";
}

int main()
{
    header();
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
        else if (command != "exit") {
            cout << "'" << command << "' command not recognized";
            newLine();
        }
    }

    return 0;
}

