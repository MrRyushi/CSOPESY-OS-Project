#pragma once
#include "BaseScreen.h"

using namespace std;	

#include <iostream>
class Screen : public BaseScreen
{
public:
	Screen(string processName, int currentLine, int totalLine, string timestamp);
	~Screen();
	void setProcessName(string processName);
	void setCurrentLine(int currentLine);
	void setTotalLine(int totalLine);
	void setTimestamp(string timestamp);
	void populateScreenCommands();

	string getProcessName() override;
	int getCurrentLine() override;
	int getTotalLine() override;
	string getTimestamp() override;

private:
	string processName;
	int currentLine;
	int totalLine;
	string timestamp;
	string printCommands[100];
};
