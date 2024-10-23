#pragma once
using namespace std;

#include "ConsoleManager.h"
#include <iostream>
#include <unordered_map>
#include "Screen.h"


// stores the created instance of console manager
ConsoleManager* ConsoleManager::consoleManager = nullptr;

ConsoleManager::ConsoleManager() {
};

void ConsoleManager::initialize() {
    consoleManager = new ConsoleManager();

	

	/*consoleManager->scheduler.initialize(num_cpu);
	consoleManager->scheduler.start();
	consoleManager->running = true;
	consoleManager->switchSuccessful = true;
	consoleManager->initialized = false;
	consoleManager->currentConsole = nullptr;
	consoleManager->screenMap = unordered_map<string, shared_ptr<BaseScreen>>();*/
}

void ConsoleManager::initializeConfiguration() {
    FILE* file;
    file = fopen("config.txt", "r");
    if (file == NULL) {
        cout << "Error opening file" << endl;
    }
    else {
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            string str = line;
            if (str.find("num_cpu") != string::npos) {
                string num_cpu_str = str.substr(str.find("=") + 1);
                ConsoleManager::getInstance()->setNumCpu(stoi(num_cpu_str));
            }
            else if (str.find("scheduler") != string::npos) {
                ConsoleManager::getInstance()->setSchedulerConfig(str.substr(str.find("=") + 1));
            }
            else if (str.find("time_slice") != string::npos) {
                string time_slice_str = str.substr(str.find("=") + 1);
                ConsoleManager::getInstance()->setTimeSlice(stoi(time_slice_str));
            }
            else if (str.find("min_ins") != string::npos) {
                string min_ins_str = str.substr(str.find("=") + 1);
                ConsoleManager::getInstance()->setMinIns(stoi(min_ins_str));
            }
            else if (str.find("max_ins") != string::npos) {
                string max_ins_str = str.substr(str.find("=") + 1);
                ConsoleManager::getInstance()->setMaxIns(stoi(max_ins_str));
            }
            else if (str.find("delay_per_exec") != string::npos) {
                string delay_per_exec_str = str.substr(str.find("=") + 1);
                ConsoleManager::getInstance()->setDelayPerExec(stoi(delay_per_exec_str));
            }
        }
        fclose(file);
    }
}

void ConsoleManager::drawConsole() {
    if (this->switchSuccessful) {
        system("cls");
        string consoleName = this->getCurrentConsole()->getConsoleName();

        if (this->getCurrentConsole()->getConsoleName() == MAIN_CONSOLE) {
            this->printHeader();
        }
        else {
            if (this->screenMap.contains(consoleName)) {
                cout << "Screen Name: " << this->screenMap[consoleName]->getConsoleName() << endl;
                cout << "Current line of instruction / Total line of instruction: ";
                cout << this->screenMap[consoleName]->getCurrentLine();
                cout << "/" << this->screenMap[consoleName]->getTotalLine() << endl;
                cout << "Timestamp: " << this->screenMap[consoleName]->getTimestamp() << endl;
            }
        }
    }
}

void ConsoleManager::destroy() {
    consoleManager->scheduler.stop(); // Stop the scheduler
    delete consoleManager;
}

string ConsoleManager::getCurrentTimestamp() {
    // Get current time as time_t object
    time_t currentTime = time(nullptr);
    // Create tm structure to store local time
    tm localTime;
    // Convert time_t to tm structure 
    localtime_s(&localTime, &currentTime);
    // Create a buffer to store the formatted time
    char timeBuffer[100];
    // Format the time (MM/DD/YYYY, HH:MM:SS AM/PM)
    strftime(timeBuffer, sizeof(timeBuffer), "%m/%d/%Y, %I:%M:%S %p", &localTime);
    return timeBuffer;
}

void ConsoleManager::registerConsole(shared_ptr<BaseScreen> screenRef) {
    this->screenMap[screenRef->getConsoleName()] = screenRef; //it should accept MainScreen and ProcessScreen
    system("cls");
}

void ConsoleManager::switchConsole(string consoleName)
{
    if (this->screenMap.contains(consoleName)) {
        this->currentConsole = this->screenMap[consoleName];

        if (consoleName == MAIN_CONSOLE) {
            this->drawConsole();
        }
    
        this->switchSuccessful = true;
    }
    else {
        cout << "Console name " << consoleName << " not found. Was it initialized?" << endl;
        this->switchSuccessful = false;
    }
}

void ConsoleManager::displayProcessList() {
    unordered_map<string, shared_ptr<BaseScreen>> screenMap = ConsoleManager::getInstance()->getScreenMap();
    Scheduler* scheduler = Scheduler::getInstance();
    int coresUsed = scheduler->getCoresUsed();
    int coresAvailable = scheduler->getCoresAvailable();
	float cpuUtilization = (float)coresUsed / (coresUsed + coresAvailable) * 100;

	cout << "\nCPU Utilization: " << cpuUtilization << "%" << endl;
    cout << "Cores used: " << coresUsed << endl;
	cout << "Cores available: " << coresAvailable << endl;
	cout << "-----------------------------------" << endl;
    cout << "Running processes:" << endl;
    for (const auto& pair : screenMap) {
        shared_ptr<Screen> screenPtr = dynamic_pointer_cast<Screen>(pair.second);

        if (screenPtr && !screenPtr->isFinished()) {

            auto coreID = screenPtr->getCPUCoreID();
            string coreIDstr;
            if (coreID == -1) {
                coreIDstr = "N/A";
            }
            else {
                coreIDstr = to_string(coreID);
            }

            cout << "Name: " << screenPtr->getProcessName() << " | "
                << screenPtr->getTimestamp() << " | "
                << "Core: " << coreIDstr << " | "
                << screenPtr->getCurrentLine() << "/"
                << screenPtr->getTotalLine() << " | " << endl;
        }
    }

    cout << "\nFinished processes:" << endl;
    for (const auto& pair : screenMap) {
        shared_ptr<Screen> screenPtr = dynamic_pointer_cast<Screen>(pair.second);


        if (screenPtr && screenPtr->isFinished()) {
            cout << "Name: " << screenPtr->getProcessName() << " | "
                << screenPtr->getTimestampFinished() << " | "
                << "Finished" << " | "
                << screenPtr->getCurrentLine() << "/"
                << screenPtr->getTotalLine() << " | " << endl;
        }
    }
    cout << "-----------------------------------" << endl;
}

int ConsoleManager::getNumCpu() {
	return this->num_cpu;
}

string ConsoleManager::getSchedulerConfig() {
	return this->schedulerConfig;
}

int ConsoleManager::getTimeSlice() {
	return this->timeSlice;
}

int ConsoleManager::getMinIns() {
	return this->minIns;
}

int ConsoleManager::getMaxIns() {
	return this->maxIns;
}

int ConsoleManager::getDelayPerExec() {
	return this->delayPerExec;
}

void ConsoleManager::setNumCpu(int num_cpu) {
	this->num_cpu = num_cpu;
}

void ConsoleManager::setSchedulerConfig(string scheduler) {
	this->schedulerConfig = scheduler;
}

void ConsoleManager::setTimeSlice(int timeSlice) {
	this->timeSlice = timeSlice;
}

void ConsoleManager::setMinIns(int minIns) {
	this->minIns = minIns;
}

void ConsoleManager::setMaxIns(int maxIns) {
	this->maxIns = maxIns;
}

void ConsoleManager::setDelayPerExec(int delayPerExec) {
	this->delayPerExec = delayPerExec;
}


void ConsoleManager::printProcess(string enteredProcess){
    unordered_map<string, shared_ptr<BaseScreen>> screenMap = ConsoleManager::getInstance()->getScreenMap();
    auto it = screenMap.find(enteredProcess);
    for (const auto& pair : screenMap) {
        shared_ptr<Screen> screenPtr = dynamic_pointer_cast<Screen>(pair.second);

        //check if process name exits
        if (screenPtr->getProcessName() == enteredProcess) {

            //check if process is finished
            if (screenPtr && screenPtr->isFinished()){
                shared_ptr<Screen> screenPtr = dynamic_pointer_cast<Screen>(screenMap.find(enteredProcess)->second);

                auto coreID = screenPtr->getCPUCoreID();
                string coreIDstr;
                if (coreID == -1) {
                    coreIDstr = "N/A";
                }
                else {
                    coreIDstr = to_string(coreID);
                }

                cout << "Process Name: " << enteredProcess << endl;
                cout << "Logs:" << endl;
                cout << "(" << screenPtr->getTimestamp() << ")  "
                    << "Core: " << coreIDstr << "  ";
                //where to put createfile?
                screenPtr->createFile();
                screenPtr->viewFile();
            }
            else {
                cout << "Process is not yet finished" << endl;
            }
            
        }

    }
}


shared_ptr<BaseScreen> ConsoleManager::getCurrentConsole()
{
    return this->currentConsole;
}

void ConsoleManager::setCurrentConsole(shared_ptr<BaseScreen> screenRef)
{
    this->currentConsole = screenRef;
}

ConsoleManager* ConsoleManager::getInstance()
{
    return consoleManager;
}

void ConsoleManager::exitApplication() {
    this->running = false;
	Scheduler::getInstance()->stop();
}

bool ConsoleManager::isRunning() {
    return this->running;
}

unordered_map<string, shared_ptr<BaseScreen>> ConsoleManager::getScreenMap() {
    return this->screenMap;
}

void ConsoleManager::setInitialized(bool initialized) {
	this->initialized = initialized;
}

bool ConsoleManager::getInitialized() {
	return this->initialized;
}

void ConsoleManager::printHeader() {
    cout << "             ________________________________________________\n";
    cout << "            /                                                \\\n";
    cout << "           |    _________________________________________     |\n";
    cout << "           |   |                                         |    |\n";
    cout << "           |   |                                         |    |\n";
    cout << "           |   |                                         |    |\n";
    cout << "           |   |                    _______ _______      |    |\n";
    cout << "           |   |      .-----.--.--.|       |     __|     |    |\n";
    cout << "           |   |      |  _  |  |  ||   -   |__     |     |    |\n";
    cout << "           |   |      |___  |_____||_______|_______|     |    |\n";
    cout << "           |   |      |_____|                            |    |\n";
    cout << "           |   |                                         |    |\n";
    cout << "           |   |                                         |    |\n";
    cout << "           |   |                                         |    |\n";
    cout << "           |   |_________________________________________|    |\n";
    cout << "           |                                                  |\n";
    cout << "            \\_________________________________________________/\n";
    cout << "              \\___________________________________/\n";
    cout << "                ___________________________________________\n";
    cout << "             _-'    .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.  --- -_\n";
    cout << "          _-'.-.-. .---.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.  .-.-.-_\n";
    cout << "       _-'.-.-.-. .---.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-__. .-.-.-.-_\n";
    cout << "    _-'.-.-.-.-. .-----.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-----. .-.-.-.-.-_\n";
    cout << " _-'.-.-.-.-.-. .---.-. .-------------------------. .-.---. .---.-.-.-.-_\n";
    cout << ":-------------------------------------------------------------------------:\n";
    cout << "---._.-------------------------------------------------------------._.---'\n";
    cout << "\n________________________________________________________________________________\n";
    cout << "\n";
}
