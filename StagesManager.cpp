#include "StagesManager.h"
#include "Stage.h"
#include <conio.h>
bool StagesManager::getAvailableStages(vector<Stage>& stages) {
	stages.clear();
	fs::path currentDir = fs::current_path();
	getDynamicPath(&currentDir);
	/*Test: cout << "Current directory: " << currentDir << '\n' << " press...";
	while (!_kbhit());*/
	try {
		for (const auto& entry : fs::directory_iterator(currentDir)) {
			string fileName = entry.path().filename().string();
			string stageName = getStageNameByFileName(fileName);
			Stage currStage(stageName, fileName);
			if (entry.is_regular_file() && isMatchesPattern(currStage) && loadStageBoard(&currStage, currentDir) && isFileBoardValid(currStage.getStageBoard()))
				stages.push_back(currStage);
		}
	}
	catch (const fs::filesystem_error& e) {
		cout << "Filesystem error: " << e.what() << '\n';
		return false;
	}

	// Sort by lexicographical order
	sort(stages.begin(), stages.end());

	return !stages.empty();
}
void StagesManager::printStages(const vector<Stage>& stages, int x, int y) {
	gotoxy(x, y);
	for (const Stage& stage : stages) {
		cout << stage.getStageName();
		y++;
		gotoxy(x, y);
	}
	ShowConsoleCursor(false);
}
void StagesManager::getDynamicPath(fs::path* currentDir) {
	// Move up if the working directory is inside x64/Debug (common issue when running from cmd.exe)
	if (currentDir->filename() == "Debug") {
		*currentDir = currentDir->parent_path().parent_path(); // Move up two levels to reach the project root
		*currentDir /= "dkong";
	}
}
bool StagesManager::loadStageBoard(Stage* stage, const fs::path& currentDir) {
	int y = 0;
	const string fileName = stage->getFileName();
	std::filesystem::path fullPath = currentDir / fileName;
	ifstream stageFile(fullPath);
	string line;

	// Check if the file is successfully opened
	if (!stageFile.is_open()) {
		cout << "Error opening file: " << fileName << endl;
		return false;
	}

	// Read the file and populate the stage board
	for (y = 0; getline(stageFile, line); ++y) {
		if (line.size() != GameConfig::MAX_X) {
			cout << "Error size file: " << fileName << endl;
			return false;
		}
		stage->setStageBoardLine(y, line);
	}
	if (y != GameConfig::MAX_Y) {
		cout << "Error size file: " << fileName << endl;
		return false;
	}

	stageFile.close();
	// cout << "Stage board loaded successfully from file: " << fileName << endl;
	return true;
}

int StagesManager::findStage(const vector<Stage>& stages, const string& stageName) {
	for (int i = 0; i < stages.size(); i++) {
		if (stages[i].getStageName() == stageName)
			return i;
	}
	return -1;
}
string StagesManager::getStepsFileName(const string& stageName) {
	return PREFIX + stageName + SUFFIX_STEPS;
}
string StagesManager::getResultFileName(const string& stageName)
{
	return PREFIX + stageName + SUFFIX_RESULT;
}
bool StagesManager::isFileBoardValid(const GameConfig::StageBoard& stageBoard) {
	int countMario = 0, countPauline = 0, countDk = 0, countHM = 0;

	for (int y = 0; y < GameConfig::MAX_Y; ++y) {
		for (int x = 0; x < GameConfig::MAX_X; ++x) {
			if ((x == 0 || x == GameConfig::MAX_X - 1 || y == 0) &&
				stageBoard[y][x] != (char)GameConfig::eSymbols::WALL) {
				std::cout << "Invalid stage board: Board boundaries invalid." << std::endl;
				return false;
			}
			switch (stageBoard[y][x]) {
			case (char)GameConfig::eSymbols::MARIO:
				countMario++;
				if (!isMarioFirstPositionValid(stageBoard, x, y))
					return false;
				break;
			case (char)GameConfig::eSymbols::PAULINE:
				countPauline++;
				break;
			case (char)GameConfig::eSymbols::DK:
				countDk++;
				break;
			case (char)GameConfig::eSymbols::HAMMER:
				countHM++;
				break;
			}
		}
		// Check for too many instances of any symbol
		if (countMario > 1 || countPauline > 1 || countDk > 1 || countHM > 1) {
			std::cout << "Invalid stage board: too many Marios, Paulines, DKs, or Hammers." << std::endl;
			return false;
		}
	}
	if (countMario == 0 || countPauline == 0 || countDk == 0 || countHM == 0) {
		std::cout << "Invalid stage board: Not found Mario or Pauline or DK or Hammer." << std::endl;
		return false;
	}
	return true;
}
bool StagesManager::isFileNameLenValid(const string& fileName) {

	return (fileName.size() >= PREFIX.size() + SUFFIX_SCREEN.size());
}

string StagesManager::getFilePrefix(const string& fileName) {
	string filePrefix;
	if (isFileNameLenValid(fileName)) {
		filePrefix = fileName.substr(0, PREFIX.size());
		return filePrefix;
	}
	return "";
}

string StagesManager::getFileSUFFIX_SCREEN(const string& fileName) {
	string fileSufffix;
	if (isFileNameLenValid(fileName)) {
		fileSufffix = fileName.substr(fileName.size() - SUFFIX_SCREEN.size());
		return fileSufffix;
	}
	return "";
}

string StagesManager::getStageNameByFileName(const string& fileName) {
	if (isFileNameLenValid(fileName))
		return fileName.substr(PREFIX.size(), fileName.size() - PREFIX.size() - SUFFIX_SCREEN.size());
	return "";
}

bool StagesManager::isMatchesPattern(const Stage& stage) {
	const string fileName = stage.getFileName();
	if (!isFileNameLenValid(fileName))
		return false;
	return (PREFIX == getFilePrefix(fileName) && getFileSUFFIX_SCREEN(fileName) == SUFFIX_SCREEN);
}
bool StagesManager::isMarioFirstPositionValid(const GameConfig::StageBoard& stageBoard, int x, int y)
{
	if (y < GameConfig::MAX_Y-1) {
		if (stageBoard[y + 1][x] != (char)GameConfig::eSymbols::FLOOR && 
			stageBoard[y + 1][x] != (char)GameConfig::eSymbols::LFLOOR &&
			stageBoard[y + 1][x] != (char)GameConfig::eSymbols::RFLOOR &&
			stageBoard[y + 1][x] != (char)GameConfig::eSymbols::WALL) {
			cout << "Invalid stage board: Mario must be on a floor." << endl;
			return false;
		}
	}
	return true;
}

