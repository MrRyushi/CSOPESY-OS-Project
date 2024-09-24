
void SetConsoleWindowSize(int width, int height) {
    console HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    const COORD newSize = {static_cast<short>(width), static_cast<short>(height)};
    SetConsoleScreenBufferSice(hConsole, newSize);

    const SMALL_RECT rect = { 0, 0, newSize.X - 1, newSize.Y -1 };
    SetConsoleWindowInfo(hConsole, TRUE, &rect);
}

int main () {
    InputManager::initialize();
    FileSystem::initialize();
    // FileSystem::getInstance()->test_createRandomFiles(1000);
    // FileSystem::getInstance()->saveFileSystem();
    FileSystem::getInstance()->loadFileSystem();
    GlobalScheduler::initialize();
    ConsoleManager::initialize();
    MessageBuffer::initialize();
    ResourceEmulator::initialize();
    MemoryManager::initialize();

    ResourceEmulator::getInstance()->startAllCPUs();
    GlobalScheduler::getInstance()->test_createRandomProcesses(50);

    bool running = true;
    while(running) {
        ConsoleManager::getInstance()->process();
        ConsoleManager::getInstance()->drawConsole();
        // std::thread([]() {
        //  GlobalScheduler::getInstance()->tick();}).detach();
        //  
    }

    MemoryTestRun::run();
    // MemoryManager::test_MemoryAllocation();

    MemoryManager::destroy();
    ResourceEmulator::destroy();
    MessageBufferManager::destroy();
    ConsoleManager::destroy();
    GlobalScheduler::destroy(); 
    InputManager::destroy();
    return 0;
}   