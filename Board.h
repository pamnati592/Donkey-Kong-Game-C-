#ifndef __BOARD_H
#define __BOARD_H
#include "Utils.h"
#include "GameConfig.h"
#include "Point.h"
#include "Mario.h"
#include <vector>

class Game;
class Barrel;
class Ghost;
class ModeManager;

class Board
{
	static constexpr int MAX_BARRELS = 10;
	static constexpr int MAX_GHOSTS = 50;
	static constexpr int BARREL_SPAWN_INTERVAL = 30;
	ModeManager* modeManager;
	char* initBoard[GameConfig::MAX_Y] = {};
	char currentBoard[GameConfig::MAX_Y][GameConfig::MAX_X+1] = {};
	Game* pGame;
	Mario mario;
	int activeBarrelsCount, activeghostCount, barrelSpawnTimer, score;
	Barrel* barrels[MAX_BARRELS] = {};
	std::vector<Ghost*> ghosts;
	Point crdData, crdPauline, crdDK, crdHammer;

public:
	Board(Game* _pGame, const GameConfig::StageBoard& stageBoard, ModeManager* _modeManager);
	Board(const Board& other);
	~Board();

	// Board management
	GameConfig::eSymbols getInitSymbolByPoint(Point p) const { return getInitSymbolByPoint(p.x, p.y); }
	GameConfig::eSymbols getInitSymbolByPoint(int x, int y) const { return (GameConfig::eSymbols)initBoard[y][x]; }
	GameConfig::eSymbols getSymbolByPoint(Point p) const { return getSymbolByPoint(p.x, p.y); }
	GameConfig::eSymbols getSymbolByPoint(int x, int y) const { return (GameConfig::eSymbols)currentBoard[y][x]; }
	bool isCoordFloor(Point _coord) const;
	void printBoard();
	void updateInitBoardSymbolAt(Point p, GameConfig::eSymbols symbol);
	void updateCurrentBoardSymbolAt(Point p, GameConfig::eSymbols symbol);
	const Point& getDKCoord();
	const Point& getHammerCoord();
	void setNewStage(const GameConfig::StageBoard& stageBoard);
	void eraseHammer();
	void deleteInitBoard();
	void resetSuperGhost();

	// Run cycle
	void handleMarioPrePace();
	void handleMarioPostPace();
	void handleBarrelsPrePace();
	void handleBarrelsPostPace();
	void handleGhostPrePace();
	void handleGhostPostPace();
	void resetBoard();
	// Barrels
	void spawnBarrel();
	void deleteBarrel(size_t barrelIndex);
	void deleteBarrels();
	void resetBarrels();
	bool checkCollisionBarrel(size_t barrelIndex);
	void getRandomBarrelDir(Direction* dir, size_t index);
	// Ghosts
	bool spawnGhost();
	bool spawnSuperGhost();
	void spawnGhosts();
	void deleteGhosts();
	bool checkCollisionGhost(size_t index);
	void checkGhostMeets();
	void getRandomGhostDir(Direction* dir, size_t index);
	// Data
	void displayScore() const;
	void displayData() const;
	void displayLives() const;
	void displayHammer() const;
	//Mario
	bool isMarioReachedPauline() const;
	bool isMarioAlive() const;
	Point marioGetCoord() const;
	void setMarioAttack(bool isAttack);
	
private:
	// Board management
	void setInitBoard(const GameConfig::StageBoard& stageBoard);
	void initializeBoard();
	// Board management
	void setEntitiesCoord();
	Point findEntity(GameConfig::eSymbols entity) const;
	// Barrels
	void initBarrels();
	// Ghosts
	void resetGhosts();
	// Data
	void addScore();
};

#endif
