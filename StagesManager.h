#ifndef __STAGES_MANAGER_H
#define __STAGES_MANAGER_H

#include <vector>
#include <fstream>
#include <filesystem>
#include "Utils.h"
#include "GameConfig.h"

class Stage;

static const std::string PREFIX = "dkong_";
static const std::string SUFFIX_SCREEN = ".screen";
static const std::string SUFFIX_STEPS = ".steps";
static const std::string SUFFIX_RESULT = ".result";

using namespace std;
namespace fs = std::filesystem;

class StagesManager {

public:
	static bool getAvailableStages(vector<Stage>& stages);
	static void printStages(const vector<Stage>& stages, int x, int y);
	static int findStage(const vector<Stage>& stages, const string& stageName);
	static string getStepsFileName(const string& stageName);
	static string getResultFileName(const string& stageName);
private:
	static void getDynamicPath(fs::path* currentDir);
	static bool loadStageBoard(Stage* stage, const fs::path& currentDir);
	static bool isFileBoardValid(const GameConfig::StageBoard& stageBoard);
	static bool isFileNameLenValid(const string& fileName);
	static string getFilePrefix(const string& fileName);
	static string getFileSUFFIX_SCREEN(const string& fileName);
	static string getStageNameByFileName(const string& fileName);
	static bool isMatchesPattern(const Stage& stage);
	static bool isMarioFirstPositionValid(const GameConfig::StageBoard& stageBoard , int x , int y);
};

#endif