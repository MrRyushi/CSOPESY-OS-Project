#include "Scheduler.h"
#include <iostream>
#include <chrono>

Scheduler::Scheduler(int numCores) : numCores(numCores), schedulerRunning(false) {}

Scheduler::~Scheduler() {
    stop();
}

void Scheduler::start() {
    schedulerRunning = true;
    for (int i = 0; i < numCores; ++i) {
        workerThreads.emplace_back(&Scheduler::workerFunction, this, i);
    }
}

void Scheduler::stop() {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        schedulerRunning = false;
    }
    queueCondition.notify_all();
    for (auto& thread : workerThreads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
    workerThreads.clear();
}

void Scheduler::addProcessToQueue(std::shared_ptr<Screen> process) {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        processQueue.push(process);
    }
    queueCondition.notify_one();
}

void Scheduler::workerFunction(int coreId) {
    while (schedulerRunning) {
        std::shared_ptr<Screen> process;

        {
            std::unique_lock<std::mutex> lock(queueMutex);
            queueCondition.wait(lock, [this] { return !processQueue.empty() || !schedulerRunning; });

            if (!schedulerRunning && processQueue.empty()) break;

            process = processQueue.front();
            processQueue.pop();
        }

        // Simulate process execution
        std::cout << "Core " << coreId << " is executing process: " << process->getProcessName() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate process execution time
    }
}
