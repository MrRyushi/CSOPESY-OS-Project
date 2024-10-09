#pragma once
#include "BaseScreen.h"

class ListScreen : public BaseScreen {
public:
	static void initialize();

	ListScreen(string name);
	ListScreen();
	void drawProcessList();
	static ListScreen* getInstance();


private:
	static ListScreen* listScreen; 
};