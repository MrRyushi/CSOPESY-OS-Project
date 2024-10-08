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
    while (schedulerRunning) { // Loop while the scheduler is running
        std::shared_ptr<Screen> process; // A local variable to hold the process to be executed

        {
            std::unique_lock<std::mutex> lock(queueMutex); // Lock the queue to prevent concurrent access
            queueCondition.wait(lock, [this] {
                return !processQueue.empty() || !schedulerRunning;
                });
            // Wait until either there's a process in the queue or the scheduler stops running

            if (!schedulerRunning && processQueue.empty()) break;
            // If the scheduler stops running and no more processes are in the queue, exit the loop

            process = processQueue.front(); // Take the next process from the queue
            processQueue.pop(); // Remove it from the queue
        }

        // Simulate process execution
        std::cout << "Core " << coreId << " is executing process: " << process->getProcessName() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate execution time
    }
}

