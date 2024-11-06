#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class FlatMemoryAllocator
{
public:
	~FlatMemoryAllocator();
    
	FlatMemoryAllocator(size_t maximumSize);
    void* allocate(size_t size); 
    void deallocate(void* ptr);
    std::string visualizeMemory();
    void initializeMemory();
    bool canAllocateAt(size_t index, size_t size);
    void allocateAt(size_t index, size_t size);
    void deallocateAt(size_t index);
	static FlatMemoryAllocator* getInstance();
	static void initialize(size_t maximumMemorySize);
    FlatMemoryAllocator() : maximumSize(0), allocatedSize(0) {};

private:
	static FlatMemoryAllocator* flatMemoryAllocator;
	size_t maximumSize;
	size_t allocatedSize;
	std::vector<char> memory;
	std::unordered_map<size_t, bool> allocationMap;


};

