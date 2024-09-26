#pragma once
#include "BaseScreen.h"

using namespace std;	

#include <iostream>
class Screen : public BaseScreen
{
public:
	Screen(string processName, int currentLine, int totalLine, string timestamp);
	/*Screen(string processName);
	Screen();*/
	~Screen();
	void setProcessName(string processName);
	void setCurrentLine(int currentLine);
	void setTotalLine(int totalLine);
	void setTimestamp(string timestamp);

	string getProcessName() override;
	int getCurrentLine() override;
	int getTotalLine() override;
	string getTimestamp() override;
	
	//void drawScreen();

private:
	string processName;
	int currentLine;
	int totalLine;
	string timestamp;
};
