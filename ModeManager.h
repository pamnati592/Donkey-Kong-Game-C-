#ifndef __MODE_MANAGER_H
#define __MODE_MANAGER_H

#include "GameConfig.h"
#include <string>
#include "Mode.h"
#include <fstream>

struct Direction;

static const std::string ARG_LOAD = "-load";
static const std::string ARG_SAVE = "-save";
static const std::string ARG_SILENT = "-silent";

class ModeManager {
	static constexpr const char KB_HIT = '^';
	static constexpr const char GHOST_CHANGE_DIR = '%';
	static constexpr const char BARREL_DIR_RIGHT = '?';
	static constexpr const char BARREL_DIR_LEFT = '!';
	static constexpr const char MARIO_REDUCE_LIFE = '<';
	static constexpr const char STAGE_CLEARED = ':';
	static constexpr const char SCORE = ')';

	int timePoint;
	Mode mode;
	std::string stageName;
	std::fstream stepsFile, resultFile;
	bool test;

public:
	ModeManager(const Mode& _mode, const std::string& stageName);
	~ModeManager() {
		closeFiles();
	}
	static Mode defineMode(const char* const argv[]);
	void resetModeManager(const std::string& stageName);
	void tick() { timePoint++; };
	bool getLoad() const { return mode.load; }
	bool getSave() const { return mode.save; }
	bool getSilent() const { return mode.silent; }
	bool getTest() const { return test; }
	bool getKBHit(GameConfig::eKeys* key);
	void getRandomGhostDir(Direction* dir, size_t index);
	void getRandomBarrelDir(Direction* dir, size_t index);
	// Result
	void reduceLife();
	void stageCleared();
	void score();

private:
	// Files
	static void getDynamicPath(std::filesystem::path* currentDir);
	void openFiles();
	void closeFiles();

	void resetTick() { timePoint = 0; };
	// Keyboard Hit
	bool loadKBHit(GameConfig::eKeys* key);
	void saveKBHit(const GameConfig::eKeys& key);
	// Ghosts
	bool loadGhostDirChange(size_t _index);
	void saveGhostDirChange(size_t index);
	// Barrels
	void loadBarrelDir(Direction* dir, size_t _index);
	void saveBarrelDir(const Direction& dir, size_t index);
	// Result
	void handleAction(const char action);
	void saveResultAction(const char _action);
	void loadResultAction(const char _action);
};

#endif