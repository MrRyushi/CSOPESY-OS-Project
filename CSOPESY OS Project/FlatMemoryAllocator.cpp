using namespace std;

#include "FlatMemoryAllocator.h"
#include <algorithm>


FlatMemoryAllocator::FlatMemoryAllocator(size_t maximumSize) : maximumSize(maximumSize), allocatedSize(0)
{
	memory.reserve(maximumSize);
	initializeMemory();
}

FlatMemoryAllocator::~FlatMemoryAllocator()
{
	memory.clear();
}

FlatMemoryAllocator* FlatMemoryAllocator::flatMemoryAllocator = nullptr;

void FlatMemoryAllocator::initialize(size_t maximumMemorySize){
    flatMemoryAllocator = new FlatMemoryAllocator(maximumMemorySize);
}

FlatMemoryAllocator* FlatMemoryAllocator::getInstance() {
	return flatMemoryAllocator;
}

void* FlatMemoryAllocator::allocate(size_t size) {
	for (size_t i = 0; i < maximumSize - size + 1; ++i) {
		if (!allocationMap[i] && canAllocateAt(i, size)) {
			allocateAt(i, size);
			return &memory[i];
		}
	}

	return nullptr;
}

void FlatMemoryAllocator::deallocate(void* ptr) {
	size_t index = static_cast<char*>(ptr) - &memory[0];
	if (allocationMap[index]) {
		deallocateAt(index);
	}
}

std::string FlatMemoryAllocator:: visualizeMemory(){
	return std::string(memory.begin(), memory.end());
}

void FlatMemoryAllocator:: initializeMemory() {
	std::fill(memory.begin(), memory.end(), '.');
	std::fill(allocationMap.begin(), allocationMap.end(), false);
}

bool FlatMemoryAllocator:: canAllocateAt(size_t index, size_t size) {
	return (index + size <= maximumSize);
}

void FlatMemoryAllocator::allocateAt(size_t index, size_t size) {
	std::fill(&allocationMap.begin() + index, &allocationMap.begin() + index + size, true);
	allocatedSize += size;
}

void FlatMemoryAllocator::deallocateAt(size_t index) {
	allocationMap[index] = false;
}


