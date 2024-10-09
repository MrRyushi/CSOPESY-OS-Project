#include "BaseScreen.h"
#include "ListScreen.h"
#include <iostream> 
#include "ConsoleManager.h"
#include <unordered_map>

ListScreen* ListScreen::listScreen = nullptr;

ListScreen::ListScreen(string name) : BaseScreen(name)
{
    
}

void ListScreen::drawProcessList() 
{
    std::unordered_map<string, std::shared_ptr<BaseScreen>> screenMap = ConsoleManager::getInstance()->getScreenMap();
    std::cout << "Running processes:" << std::endl;
    for (const auto& pair : screenMap) {
        std::shared_ptr<Screen> screenPtr = std::dynamic_pointer_cast<Screen>(pair.second);

        if (screenPtr && !screenPtr->isFinished()) {
            std::cout << screenPtr->getProcessName() << " "
                << screenPtr->getTimestamp() << " "
                << "core:" << screenPtr->getCPUCoreID() << " "
                << screenPtr->getCurrentLine() << "/"
                << screenPtr->getTotalLine() << std::endl;
        }
    }

    std::cout << "\nFinished processes:" << std::endl;
    for (const auto& pair : screenMap) {
        std::shared_ptr<Screen> screenPtr = std::dynamic_pointer_cast<Screen>(pair.second);

        if (screenPtr && screenPtr->isFinished()) {
            std::cout << screenPtr->getProcessName() << " "
                << screenPtr->getTimestamp() << " "
                << "core:" << screenPtr->getCPUCoreID() << " "
                << screenPtr->getCurrentLine() << "/"
                << screenPtr->getTotalLine() << std::endl;
        }
    }
}

ListScreen* ListScreen::getInstance()
{
    return listScreen;
}

void ListScreen::initialize() {
    listScreen = new ListScreen(SCREEN_LS);
}