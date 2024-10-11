#include "Scheduler.h"
#include "ConsoleManager.h"
#include "Screen.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>

Scheduler::Scheduler(int numCores) : numCores(numCores), schedulerRunning(false), coresUsed(0), coresAvailable(numCores) {}


Scheduler* Scheduler::scheduler = nullptr;

void Scheduler::initialize(int numCores) {
    scheduler = new Scheduler(numCores);
}

Scheduler::~Scheduler() {
    stop();
}

Scheduler::Scheduler() : numCores(-1), schedulerRunning(false) {
}

void Scheduler::start() {
    
    schedulerRunning = true;
    while (processQueue.size() > 0) {

        for (int i = 0; i < numCores; i++) {
            if (processQueue.empty()) {
                break;
            }
            else {
                std::shared_ptr<Screen> process = processQueue.front();

                coresUsed++;
                coresAvailable--;

                workerThreads.emplace_back([this, i, process]() {
                    workerFunction(i, process);
                        coresUsed--;
                        coresAvailable++;
                    });
                processQueue.pop();
            }     
        }

		for (auto& thread : workerThreads) {
			if (thread.joinable()) {
				thread.join();
			}
		}
    }

	stop();
}

int Scheduler::getCoresUsed() const {
    return coresUsed;
}

int Scheduler::getCoresAvailable() const {
    return coresAvailable;
}

void Scheduler::stop() {
    {
 
        schedulerRunning = false;
    }
}

void Scheduler::workerFunction(int core, std::shared_ptr<Screen> process) {
    string timestamp = ConsoleManager::getInstance()->getCurrentTimestamp();
    fstream file;
    string fileName = process->getProcessName() + ".txt";
    file.open(fileName, std::ios::app);
    file << "Process name: " << process->getProcessName() << std::endl;
    file << "Logs: " << endl << endl;
    for (int i = 0; i < process->getTotalLine(); i++) {
        process->setCPUCoreID(core);
        std::this_thread::sleep_for(std::chrono::milliseconds(80));
        string coreIDstr;
        string printed;
        unordered_map<string, shared_ptr<BaseScreen>> screenMap = ConsoleManager::getInstance()->getScreenMap();
        auto it = screenMap.find(process->getProcessName());
        for (const auto& pair : screenMap) {
        	shared_ptr<Screen> screenPtr = dynamic_pointer_cast<Screen>(screenMap.find(process->getProcessName())->second);
            auto coreID = screenPtr->getCPUCoreID();
            
            if (coreID == -1) {
                coreIDstr = "N/A";
            }
            else {
                coreIDstr = to_string(coreID);
            }
            
        }
            if (file.is_open()) {
                shared_ptr<Screen> screenPtr = dynamic_pointer_cast<Screen>(screenMap.find(process->getProcessName())->second);
                file << "(" << ConsoleManager::getInstance()->getCurrentTimestamp() << ")";
                file << "  Core: " << coreIDstr;
            	file << " \"Hello world from " << process->getProcessName() << "!\"" <<std::endl;
            }
            else {
                std::cerr << "Failed to open " << fileName << std::endl;
            }
            process->setCurrentLine(1 + process->getCurrentLine());

    }
    file.close();
	string timestampFinished = ConsoleManager::getInstance()->getCurrentTimestamp();
	process->setTimestampFinished(timestampFinished);
}

void Scheduler::addProcessToQueue(std::shared_ptr<Screen> process) {
    {
        processQueue.push(process);
    }
}

Scheduler* Scheduler::getInstance() {
	if (scheduler == nullptr) {
		scheduler = new Scheduler();
	}
	return scheduler;
}
