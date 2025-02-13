#ifndef __GHOST_H
#define __GHOST_H
#include "GameEntity.h"
#include "GameConfig.h"
#include "Utils.h"

class Ghost : public GameEntity
{
	bool activeFlag;
public:
	Ghost(Board* _pBoard);
	Ghost(Board* _pBoard, GameConfig::eSymbols _symbol);
	virtual void draw(bool silent) const;
	virtual void move(size_t index);
	void setDir(Direction SetDir) { dir = SetDir; }
	Point findGhost(const Board& board, GameConfig::eSymbols _symbol);
	bool isActive() const { return activeFlag; }
	void deactivate() { activeFlag = false; }
	bool checkMarioHit(Point marioCoord) const { return coord == marioCoord; }
	bool checkHitGhost() const;
	Direction getDir() const { return dir; }

private:
	void checkHitWall();
	void checkEndFloor();
};
#endif

