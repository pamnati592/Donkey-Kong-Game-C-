#ifndef __SUPER_GHOST_H
#define __SUPER_GHOST_H
#include "Ghost.h"

class SuperGhost : public Ghost 
{
	Point initCoord;
	bool ladderFlag;
public:
	SuperGhost(Board* pBoard);
	void draw(bool silent) const { GameEntity::draw(GameConfig::eSymbols::SUPERGHOST, silent); }
	void move(size_t index);
	Point FindSuperGhost(const Board& board);
	void SetInitCord();

private:
	void handleLadder();
	bool isOnLadder() const;
	bool isAboveLadder() const;
	bool isOnFloor() const;
	bool decideIfClimb();
	bool isMarioabove();
	bool isMarioUnder();
	void moveOnLadder();
	bool checkFinishClimb();
};

#endif