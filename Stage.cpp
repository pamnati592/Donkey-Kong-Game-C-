#include "Stage.h"

using namespace std;

Stage::Stage(std::string _stageName, std::string _fileName) : stageName(_stageName), fileName(_fileName) {
	initStageBoard();
}

string Stage::getStageName() const {
	return stageName;
}
string Stage::getFileName() const {
	return fileName;
}
void Stage::setStageBoardLine(int y, const string& line) {
	for (int x = 0; x < GameConfig::MAX_X + 1 && x < line.size(); ++x) {
		stageBoard[y][x] = line[x];
	}

	for (size_t x = line.size(); x < GameConfig::MAX_X+1; ++x) {
		stageBoard[y][x] = '\0';
	}
}
void Stage::initStageBoard() {
	for (int i = 0; i < GameConfig::MAX_Y; i++) {
		for (int j = 0; j < GameConfig::MAX_X; j++) {
			stageBoard[i][j] = (char)GameConfig::eSymbols::SPACE;
		}
	}
}