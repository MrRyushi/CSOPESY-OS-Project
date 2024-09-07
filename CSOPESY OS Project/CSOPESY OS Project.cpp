// CSOPESY OS Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

using namespace std;

#include <iostream>


void header() {
    cout << "  ------     -------   \n";
    cout << "/        |  /        | \n";
    cout << "|     ---   |     ---  \n";
    cout << "|    |      |    |     \n";
    cout << "|    |      |     ---  \n";
    cout << "|    |      \\        \\ \n";
    cout << "|    |       ---     | \n";
    cout << "|    |          |    | \n";
    cout << "|     ---    ---     | \n";
    cout << "\\        |  |        /\n";
    cout << " --------    --------  \n";
}

int main()
{
    header();
    string command = "";

    while (command != "exit") {
        cout << "Enter command: ";
        cin >> command;
        // insert code that converts command variable to lowercase
        // code
        
  
        // add conditions here for other commands
        if (command == "clear") {
            system("cls");
            header();
        }
    }

}

