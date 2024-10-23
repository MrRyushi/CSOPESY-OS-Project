#pragma once
#include "Screen.h"
#include <unordered_map>
#include "Scheduler.h"
#include <string>

const string MAIN_CONSOLE = "MAIN_CONSOLE";

class ConsoleManager
{	
public:
	enum ProcessState
	{
		READY,
		RUNNING,
		WAITING,
		FINISHED
	};

	// default constructor
	ConsoleManager();

	// we can run this to create a console manager pointer
	static void initialize();

	// we get the console manager instance after 
	static ConsoleManager* getInstance();

	void printHeader();
	void drawConsole();
	void destroy();
	string getCurrentTimestamp();
	std::unordered_map<string, std::shared_ptr<BaseScreen>> getScreenMap();

	void registerConsole(std::shared_ptr<BaseScreen> screenRef);
	void switchConsole(string consoleName);
	std::shared_ptr<BaseScreen> getCurrentConsole();
	void setInitialized(bool initialized);
	bool getInitialized();

	void setNumCpu(int num_cpu);
	void setSchedulerConfig(string schedulerConfig);
	void setTimeSlice(int timeSlice);
	void setBatchProcessFrequency(int batchProcessFrequency);
	void setMinIns(int minIns);
	void setMaxIns(int maxIns);
	void setDelayPerExec(int delayPerExec);
	void initializeConfiguration();

	int getNumCpu();
	string getSchedulerConfig();
	int getTimeSlice();
	int getBatchProcessFrequency();
	int getMinIns();
	int getMaxIns();
	int getDelayPerExec();
	void printProcessSmi(); 

	void exitApplication();
	bool isRunning();
	void setCurrentConsole(std::shared_ptr<BaseScreen> screenRef);
	void displayProcessList();
	void printProcess(string enteredProcess);


private:
	// stores the console manager pointer so that we only instantiate once
	static ConsoleManager* consoleManager;
	string consoleName = "";
	bool running = true;
	bool switchSuccessful = true;
	bool initialized = false;
	int num_cpu = 0;
	string schedulerConfig = "";
	int timeSlice = 0;
	int batchProcessFrequency = 0;
	int minIns = 0;
	int maxIns = 0;
	int delayPerExec = 0;

	// declare consoles 
	std::shared_ptr<BaseScreen> currentConsole;
	std::unordered_map<string, std::shared_ptr<BaseScreen>> screenMap;

	Scheduler scheduler;
};