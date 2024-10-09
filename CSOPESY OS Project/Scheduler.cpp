#include "Scheduler.h"
#include "ConsoleManager.h"
#include "Screen.h"
#include <iostream>
#include <chrono>
#include <thread>

Scheduler::Scheduler(int numCores) : numCores(numCores), schedulerRunning(false) {}

Scheduler::~Scheduler() {
    stop();
}

Scheduler::Scheduler() : numCores(1), schedulerRunning(false) {
    // Initialization logic (if any)
}


void Scheduler::start() {
    schedulerRunning = true;
    // Create threads based on the number of cores
    for (int i = 0; i < numCores; ++i) {
        workerThreads.emplace_back([this, i]() {
           while (schedulerRunning || !processQueue.empty()) {
                std::shared_ptr<Screen> process = nullptr;

                {
                    std::unique_lock<std::mutex> lock(queueMutex);
                    // Wait until there are processes in the queue or scheduler stops
                    queueCondition.wait(lock, [this] {
                        return !processQueue.empty() || !schedulerRunning;
                        });

                    if (!schedulerRunning && processQueue.empty()) {
                        return; // Exit thread if scheduler is stopped and no processes are pending
                    }

                    // Retrieve a process from the queue
                    if (!processQueue.empty()) {
                        process = processQueue.front();
                        processQueue.pop();
                    }
                }

                if (process != nullptr) {
                    workerFunction(i, process); // Assign process to the core
                }
            }
            });
    }

    // Wait for all threads to finish their work
    for (auto& thread : workerThreads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

	stop(); 
}

void Scheduler::stop() {
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        schedulerRunning = false;
    }
    queueCondition.notify_all(); // Wake up all threads to allow them to exit
}

void Scheduler::workerFunction(int core, std::shared_ptr<Screen> process) {
    string timestamp = ConsoleManager::getInstance()->getCurrentTimestamp();
    for (int i = 0; i < process->getTotalLine(); i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        process->setCurrentLine(process->getCurrentLine() + 1);
        process->setCPUCoreID(core);
        // Log the process execution (optional)
        std::cout << timestamp << " core: " << core << " executing process "
            << process->getCPUCoreID() << " line: " << process->getCurrentLine() << std::endl;
    }
}

void Scheduler::addProcessToQueue(std::shared_ptr<Screen> process) {
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        processQueue.push(process);
    }
    queueCondition.notify_one(); // Notify a waiting thread about the new process
}
