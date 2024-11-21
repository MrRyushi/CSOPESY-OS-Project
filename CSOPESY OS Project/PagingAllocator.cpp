#include "PagingAllocator.h"
#include "Screen.h"

void* PagingAllocator::allocate(Screen* process) {
	string processId = process->getProcessName();
	size_t numFramesNeeded = process->getNumPages();
	if (numFramesNeeded > freeFrameList.size()) {
		std::cerr << "Memory allocation failed. Not enough free frames.\n";
		return nullptr;
	}

	size_t frameIndex = allocateFrames(numFramesNeeded, processId); 
	return reinterpret_cast<void*>(frameIndex);
}

void PagingAllocator::deallocate(Screen* process) {
	string processName = process->getProcessName();

	auto it = std::find_if(frameMap.begin(), frameMap.end(),
		[processName](const auto& entry) {return entry.second == processName;  });

	while (it != frameMap.end()) {
		size_t frameIndex = it->first;
		deallocateFrames(1, frameIndex);
		it = std::find_if(frameMap.begin(), frameMap.end(),
			[processName](const auto& entry) { return entry.second == processName; };
	}
}

size_t PagingAllocator::allocateFrames(size_t numFrames, string processName) {
	size_t frameIndex = freeFrameList.back();
	freeFrameList.pop_back();

	for (size_t i = 0; i < numFrames; ++i) {
		frameMap[frameIndex + i] = processName;
	}

	return frameIndex;
}

void PagingAllocator::deallocateFrames(size_t numFrames, size_t frameIndex) {
	for (size_t i = 0; i < numFrames; ++i) {
		frameMap.erase(frameIndex + i);
	}

	for (size_t i = 0; i < numFrames; ++i) {
		freeFrameList.push_back(frameIndex + i);
	}
}