#pragma once
#include "Screen.h"
#include <unordered_map>

class PagingAllocator
{
public:
	PagingAllocator(size_t maxMemorySize);

	void* allocate(Screen* process);
	void deallocate(Screen* process);
	void visualizeMemory();
private:
	size_t maxMemorySize;
	size_t numFrames;
	std::unordered_map<size_t, string> frameMap; 
	std::vector<size_t, size_t> freeFrameList;

	size_t allocateFrames(size_t numFrames, string processName);
	void deallocateFrames(size_t numFrames, size_t frameIndex);
};

