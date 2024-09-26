#pragma once
using namespace std;	

#include <iostream>
class Screen
{
public:
	Screen(string processName, int currentLine, int totalLine, string timestamp);
	Screen(string processName);
	Screen();
	~Screen();
	void setProcessName(string processName);
	void setCurrentLine(int currentLine);
	void setTotalLine(int totalLine);
	void setTimestamp(string timestamp);
	string getProcessName();
	int getCurrentLine();
	int getTotalLine();
	string getTimestamp();

private:
	string processName;
	int currentLine;
	int totalLine;
	string timestamp;
};
