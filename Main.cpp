#include <iostream>
#include "Menu.h"
#include "ModeManager.h"

void main(int argc, char* argv[]) {
	Mode mode = ModeManager::defineMode(argv);
	Menu().run(mode);
	ShowConsoleCursor(true);
}