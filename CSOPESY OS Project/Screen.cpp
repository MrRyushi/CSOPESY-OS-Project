#include "Screen.h"
#include <fstream> 
#include <filesystem> // for folder creation

namespace fs = std::filesystem; // alias for convenience

Screen::Screen(string processName, int currentLine, int totalLine, string timestamp): BaseScreen(processName)
{
	this->processName = processName;
	this->currentLine = currentLine;
	this->totalLine = totalLine;
	this->timestamp = timestamp;

	// Specify the folder where the text files should be stored
	std::string folderName = "text_files";

	// Check if the folder exists, and create it if it doesn't
	if (!fs::exists(folderName)) {
		fs::create_directory(folderName);
	}

	// Define the full file path (folder + file name)
	std::string filePath = folderName + "/" + processName + "_commands.txt";

	// Open a file to write the print commands in the 'text_files' directory
	std::ofstream outFile(filePath);

	// Check if file is open
	if (!outFile.is_open()) {
		std::cerr << "Failed to create file: " << processName + "_commands.txt" << std::endl;
		return;
	}

	// Populate the screen commands and write to file
	for (int i = 0; i < 100; ++i) {
		this->printCommands[i] = "Printing from " + this->getConsoleName();
		outFile << this->printCommands[i] << std::endl;  // Write each command to the file
	}

	// Close the file after writing all commands
	outFile.close();
}

Screen::~Screen()
{
}

void Screen::setProcessName(string processName)
{
	this->processName = processName;
}

void Screen::setCurrentLine(int currentLine)
{
	this->currentLine = currentLine;
}

void Screen::setTotalLine(int totalLine)
{
	this->totalLine = totalLine;
}

void Screen::setTimestamp(string timestamp)
{
	this->timestamp = timestamp;
}

string Screen::getProcessName()
{
	return this->processName;
}

int Screen::getCurrentLine()
{
	return this->currentLine;
}

int Screen::getTotalLine()
{
	return this->totalLine;
}

string Screen::getTimestamp()
{
	return this->timestamp;
}


