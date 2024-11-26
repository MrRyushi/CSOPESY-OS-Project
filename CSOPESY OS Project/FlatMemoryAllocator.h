#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Screen.h"

using namespace std;

class FlatMemoryAllocator
{
public:
	~FlatMemoryAllocator();
    
	FlatMemoryAllocator(size_t maximumSize);
    void* allocate(size_t size, string process, std::shared_ptr<Screen>);
    void deallocate(void* ptr, std::shared_ptr<Screen>);
    std::string visualizeMemory();
	void visualizeMemoryASCII();
    void initializeMemory();
    bool canAllocateAt(size_t index, size_t size);
    void allocateAt(size_t index, size_t size, string processName);
    void deallocateAt(size_t index, std::shared_ptr<Screen>);
	static FlatMemoryAllocator* getInstance();
	static void initialize(size_t maximumMemorySize);
    FlatMemoryAllocator() : maximumSize(0), allocatedSize(0) {};
	size_t getProcessMemoryUsage(const std::string& processName) const;

	size_t getTotalMemoryUsage() const;

	void printMemoryInfo(int quantum);
	size_t calculateExternalFragmentation();
	size_t getNumberOfProcessesInMemory();

private:
	static FlatMemoryAllocator* flatMemoryAllocator;
	size_t maximumSize;
	size_t allocatedSize;
	std::vector<char> memory;
	std::unordered_map<size_t, string> allocationMap;
	std::unordered_map<std::string, size_t> processMemoryMap;


};

