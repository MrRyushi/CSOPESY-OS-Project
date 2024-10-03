#pragma once
using namespace std;
#include <string>

class Process
{
public:
	//struct RequirementFlags // for File and Memory Management extension
	//{
	//	bool requireFiles;
	//	int numFiles;
	//	bool requireMemory;
	//	int memoryRequired;
	//};

	enum ProcessState
	{
		READY,
		RUNNING,
		WAITING,
		FINISHED
	};
	//Process(int pid, String name, RequirementFlags requirementFlags);
	//void addCommand(ICommand::CommandType commandType);

	Process(int pid, string name);
	void executeCurrentCommand() const;
	void moveToNextLine();

	bool isFinished() const;
	int getReamainingTime() const;
	int getCommandCounter() const;
	int getLinesOfCode() const;
	int getPid() const;
	int getCPUCoreID() const;
	ProcessState getState() const;
	string getName() const;

	void test_generateRandomCommands(int limit);

private:
	//typedef std::vector<std::shared_ptr<ICommand>> CommandList;
	//RequirementFlags requirementFlags;
	//friend class ResourceEmulator
	//CommandList commandList;

	int pid;
	string name;
	
	int commandCounter;
	int cpuCoreID = -1;
	ProcessState currentState;

};

