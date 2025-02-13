#ifndef __STAGE_H
#define __STAGE_H
#include <string> 
#include <iostream> 
#include "GameConfig.h"

class Stage {
	std::string stageName;
	std::string fileName;
	GameConfig::StageBoard stageBoard;

public:
	Stage(std::string _stageName, std::string _fileName);
	bool operator<(const Stage& other) const { return stageName < other.stageName; }
	std::string getStageName() const;
	std::string getFileName() const;
	const GameConfig::StageBoard& getStageBoard() const { return stageBoard; }
	void setStageBoardLine(int y, const std::string& line);

private:
	void initStageBoard();
};
#endif