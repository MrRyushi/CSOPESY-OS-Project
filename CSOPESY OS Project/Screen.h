#pragma once
#include "BaseScreen.h"
#include "PrintCommand.h"
#include <vector>
#include <fstream>

using namespace std;	

#include <iostream>
class Screen : public BaseScreen
{
public:
	Screen(string processName, int currentLine, string timestamp, size_t memoryRequired);
	~Screen();

	enum ProcessState
	{
		READY,
		RUNNING,
		WAITING,
		FINISHED
	};

	
	void setProcessName(string processName);
	void setCurrentLine(int currentLine);
	void setTotalLine(int totalLine);
	void setTimestamp(string timestamp);
	void setTimestampFinished(string timestampFinished);
	void setMemoryRequired(size_t memoryRequired);
	void setNumPages(size_t numPages);

	void executeCurrentCommand();
	void moveToNextLine();
	bool isFinished() const;
	int getCommandCounter() const;
	int getCPUCoreID() const;
	void setCPUCoreID(int coreID);
	void createFile();
	void viewFile();
	void setRandomIns();
	size_t getMemoryRequired() const;
	void setMemoryUsage(size_t memoryUsage);
	size_t getMemoryUsage() const;
	void setIsRunning(bool isRunning);
	bool getIsRunning() const;

	ProcessState getState() const;

	string getProcessName() override;
	int getCurrentLine() override;
	int getTotalLine() override;
	string getTimestamp() override;
	string getTimestampFinished();
	size_t getNumPages();

private:
	string processName;
	int currentLine;
	int totalLine;
	int commandCounter;
	int cpuCoreID = -1;
	size_t numPages;
	string timestamp;
	bool isRunning = false;
	string timestampFinished;
	std::vector<PrintCommand> printCommands;
	ProcessState currentState;
	size_t memoryRequired;
	size_t memoryUsage;

};
