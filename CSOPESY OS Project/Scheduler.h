#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>
#include "Screen.h"

class Scheduler {
public:
    Scheduler(int numCores);
    Scheduler();
    ~Scheduler();
    void start();
    void stop();
    void addProcessToQueue(std::shared_ptr<Screen> process);
	void workerFunction(int core, std::shared_ptr<Screen> process);

private:
    int numCores;
    bool schedulerRunning;
    std::vector<std::thread> workerThreads;
    std::queue<std::shared_ptr<Screen>> processQueue;
    std::mutex queueMutex;
    std::condition_variable queueCondition;
};

#endif // SCHEDULER_H
