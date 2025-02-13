#include "ModeManager.h"
#include "Utils.h"
#include "StagesManager.h"
#include <iostream>
#include <filesystem> 
#include <conio.h>

ModeManager::ModeManager(const Mode& _mode, const std::string& _stageName) :
	timePoint(0), mode(_mode), stageName(_stageName), test(true) {
	openFiles();
}
Mode ModeManager::defineMode(const char* const argv[]) {
	Mode mode;
	if (argv[1]) {
		std::string argLoadSave = argv[1];
		mode.load = argLoadSave == ARG_LOAD;
		mode.save = argLoadSave == ARG_SAVE;
		if (argv[2]) {
			std::string argSilent = argv[2];
			mode.silent = mode.load ? argSilent == ARG_SILENT : false;
		}
	}
	return mode;
}
void ModeManager::resetModeManager(const std::string& _stageName) {
	resetTick();
	stageName = _stageName;
	closeFiles();
	openFiles();
}
// Files
void ModeManager::getDynamicPath(std::filesystem::path* currentDir) {
	// Move up if the working directory is inside x64/Debug (common issue when running from cmd.exe)
	if (currentDir->filename() == "Debug") {
		*currentDir = currentDir->parent_path().parent_path(); // Move up two levels to reach the project root
		*currentDir /= "dkong";
	}
}
void ModeManager::openFiles() {
	if (!mode.load && !mode.save)
		return;

	fs::path currentDir = fs::current_path();
	getDynamicPath(&currentDir);
	const string stepsFileName = StagesManager::getStepsFileName(stageName);
	const string resultFileName = StagesManager::getResultFileName(stageName);
	std::ios_base::openmode openMode;
	if (mode.load)
		openMode = std::ios_base::in;
	if (mode.save)
		openMode = std::ios_base::out | std::ios_base::trunc;

	stepsFile.open(currentDir / stepsFileName, openMode);
	resultFile.open(currentDir / resultFileName, openMode);

	if (!stepsFile.is_open()) {
		cout << "Error opening file: " << stepsFileName << endl;
		return;
	}
	if (!stepsFile.is_open()) {
		cout << "Error opening file: " << resultFileName << endl;
		return;
	}
}
void ModeManager::closeFiles() {
	if (stepsFile.is_open())
		stepsFile.close();
	if (resultFile.is_open())
		resultFile.close();
}
// Result
void ModeManager::reduceLife() {
	handleAction(MARIO_REDUCE_LIFE);
}
void ModeManager::stageCleared() {
	handleAction(STAGE_CLEARED);
}
void ModeManager::score() {
	handleAction(SCORE);
}
void ModeManager::handleAction(const char action) {
	if (mode.save)
		saveResultAction(action);
	if (mode.load && mode.silent)
		loadResultAction(action);
}
void ModeManager::saveResultAction(const char _action) {
	resultFile << _action << " " << timePoint << endl;
}
void ModeManager::loadResultAction(const char _action) {
	system("cls");
	if (!resultFile.is_open()) {
		gotoxy(0, 1);
		cout << "File is not open";
		test = false;
	}
	std::string line;

	if (!std::getline(resultFile, line) || line.empty()) {
		gotoxy(0, 1);
		cout << "File is empty";
		test = false;
	}

	std::istringstream iss(line);
	char action;
	int time;

	if (!(iss >> action >> time)) {
		gotoxy(0, 1);
		cout << "File is corrupted";
		test = false;
	}

	// Check if this line is representing a valid keyboard hit
	if (!(action == _action && time == timePoint)) {
		gotoxy(0, 1);
		cout << "Action doesn't fit the expected result";
		test = false;
	}
}
// Keyboard hit
bool ModeManager::getKBHit(GameConfig::eKeys* key) {
	char ch;
	if (mode.load)
		return loadKBHit(key);
	if (_kbhit()) {
		ch = tolower(_getch());
		if (!GameConfig::isValidKey(ch))
			return false;
		*key = (GameConfig::eKeys)ch;
		if (mode.save)
			saveKBHit(*key);
		return true;
	}
	return false;
}
bool ModeManager::loadKBHit(GameConfig::eKeys* key) {
	if (!stepsFile.is_open()) {
		return false;
	}

	std::streampos prevPos = stepsFile.tellg();
	std::string line;

	if (!std::getline(stepsFile, line) || line.empty())
		return false;

	std::istringstream iss(line);
	char action;
	int time;
	char keyChar;

	if (!(iss >> action >> time >> keyChar)) {
		stepsFile.seekg(prevPos);
		return false;
	}

	// Check if this line is representing a valid keyboard hit
	if (action == KB_HIT && time == timePoint && GameConfig::isValidKey(keyChar)) {
		*key = (GameConfig::eKeys)keyChar;
		return true;
	}

	// Reset position if not a valid keyboard hit event
	stepsFile.seekg(prevPos);
	return false;
}
void ModeManager::saveKBHit(const GameConfig::eKeys& key) {
	stepsFile << KB_HIT << " " << timePoint << " " << (char)key << endl;
}
// Ghosts
void ModeManager::getRandomGhostDir(Direction* dir, size_t index) {
	if (mode.load) {
		if (loadGhostDirChange(index))
			*dir = -*dir;
		return;
	}
	if (getFivePercentBoolean()) {
		*dir = -*dir;
		if (mode.save)
			saveGhostDirChange(index);
	}
}
bool ModeManager::loadGhostDirChange(size_t _index) {
	if (!stepsFile.is_open()) {
		return false;
	}

	std::streampos prevPos = stepsFile.tellg();
	std::string line;

	if (!std::getline(stepsFile, line) || line.empty()) {
		return false;
	}

	std::istringstream iss(line);
	char action;
	int time, index;

	if (!(iss >> action >> time >> index)) {
		stepsFile.seekg(prevPos);
		return false;
	}

	if (action == GHOST_CHANGE_DIR && time == timePoint && index == _index) {
		return true;
	}

	stepsFile.seekg(prevPos);
	return false;
}
void ModeManager::saveGhostDirChange(size_t index) {
	stepsFile << GHOST_CHANGE_DIR  << " " << timePoint << " " << index << endl;
}
// Barrels
void ModeManager::getRandomBarrelDir(Direction* dir, size_t index) {
	if (mode.load) {
		loadBarrelDir(dir, index);
		return;
	}
	dir->x = getRandomBoolean() ? dir->x + 1 : dir->x - 1;
	if (mode.save)
		saveBarrelDir(*dir, index);
}
void ModeManager::loadBarrelDir(Direction* dir, size_t _index) {
	if (!stepsFile.is_open()) {
		return;
	}

	std::streampos prevPos = stepsFile.tellg();
	std::string line;

	if (!std::getline(stepsFile, line) || line.empty()) {
		return;
	}

	std::istringstream iss(line);
	char action;
	int time, index;

	if (!(iss >> action >> time >> index)) {
		stepsFile.seekg(prevPos); // Reset position if parsing fails
		return;
	}

	// Check if this line represents a valid barrel movement
	if ((action == BARREL_DIR_RIGHT || action == BARREL_DIR_LEFT) && time == timePoint && index == _index) {
		*dir = (action == BARREL_DIR_RIGHT) ? GameConfig::INIT_DIR_R : GameConfig::INIT_DIR_L;
		return;
	}

	// Reset position if conditions are not met
	stepsFile.seekg(prevPos);
}
void ModeManager::saveBarrelDir(const Direction& dir, size_t index) {
	char ch = dir.x > 0 ? BARREL_DIR_RIGHT : BARREL_DIR_LEFT;
	stepsFile << ch << " " << timePoint << " " << index << endl;
}