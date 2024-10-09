#include "Scheduler.h"
#include "ConsoleManager.h"
#include "Screen.h"
#include <iostream>
#include <chrono>
#include <thread>

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
    for (int i = 0; i < process->getTotalLine(); i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(80));
        process->setCurrentLine(process->getCurrentLine() + 1);
        process->setCPUCoreID(core);
    }
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
