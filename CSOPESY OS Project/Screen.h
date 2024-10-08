#pragma once
#include "BaseScreen.h"

using namespace std;	

#include <iostream>
class Screen : public BaseScreen
{
public:
	Screen(string processName, int currentLine, int totalLine, string timestamp);
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

	void executeCurrentCommand() const;
	void moveToNextLine();
	bool isFinished() const;
	int getCommandCounter() const;
	int getCPUCoreID() const;
	ProcessState getState() const;

	string getProcessName() override;
	int getCurrentLine() override;
	int getTotalLine() override;
	string getTimestamp() override;



private:
	string processName;
	int currentLine;
	int totalLine;
	int commandCounter;
	int cpuCoreID = -1;
	string timestamp;
	string printCommands[100];
	ProcessState currentState;

};
