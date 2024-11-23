#pragma once
#include "Screen.h"
#include <unordered_map>
#include <map>

class PagingAllocator
{
public:
	PagingAllocator(size_t maxMemorySize);

	static void initialize(size_t maximumMemorySize);

	static PagingAllocator* getInstance();

	void* allocate(std::shared_ptr<Screen> process);
	void deallocate(std::shared_ptr<Screen> process);
	void visualizeMemory();

private:
	static PagingAllocator* pagingAllocator;
	std::map<size_t, std::string> frameMap; // Maps frame index to process name
	std::vector<size_t> freeFrameList;

	size_t maxMemorySize;
	size_t numFrames;

	size_t allocateFrames(size_t numFrames, string processName);
	void deallocateFrames(size_t numFrames, size_t frameIndex);
};

