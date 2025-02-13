#include "SuperGhost.h"
#include "Board.h"
#include "Utils.h"
#include "Point.h"
#include "Direction.h"
#include <random>
#include <iostream>

SuperGhost::SuperGhost(Board* pBoard) :
	Ghost(pBoard, GameConfig::eSymbols::SUPERGHOST), initCoord(coord), ladderFlag(false) {}
void SuperGhost::move(size_t index)
{
	if (ladderFlag)
		handleLadder();
	else {
		if (decideIfClimb()) {
			ladderFlag = true;
			moveOnLadder();
		}
		else {
			Ghost::move(index);
		}
	}
}
bool SuperGhost::checkFinishClimb()
{
	if (dir.y == -1 && pBoard->isCoordFloor(Point(coord.x, coord.y - 1))) {
		ladderFlag = false;
		coord.y -= 2;
		dir.x = 0;
		dir.y = 0;
		return true;
	}
	else if (dir.y == 1 && pBoard->isCoordFloor(Point(coord.x, coord.y + 1))) {
		ladderFlag = false;
		dir.x = 0;
		dir.y = 0;
		return true;
	}
	return false;
}
Point SuperGhost::FindSuperGhost(const Board& board)
{
	for (int y = 0; y < GameConfig::MAX_Y; ++y) {
		for (int x = 0; x < GameConfig::MAX_X; ++x) {
			if (board.getInitSymbolByPoint(x, y) == GameConfig::eSymbols::SUPERGHOST) {
				pBoard->updateInitBoardSymbolAt(Point(x, y), GameConfig::eSymbols::SPACE);
				return Point(x, y);
			}
		}
	}
	return Point(0, 0);
}
void SuperGhost::SetInitCord()
{
	coord = initCoord;
}
void SuperGhost::handleLadder() {
	if (!checkFinishClimb())
		moveOnLadder();
	else { dir.x = 1; }
}
//void SuperGhost::draw(GameConfig::eSymbols symbol) const
//{
//	gotoxy(coord.x, coord.y);
//	std::cout << (char)symbol;
//}
bool SuperGhost::isOnLadder() const
{
	return (pBoard->getSymbolByPoint(coord.x, coord.y) == GameConfig::eSymbols::LADDER);
}
bool SuperGhost::isAboveLadder() const
{
	return (isOnFloor() && pBoard->getSymbolByPoint(coord.x, coord.y + 2) == GameConfig::eSymbols::LADDER);
}
bool SuperGhost::isOnFloor() const
{
	return pBoard->isCoordFloor(Point(coord.x, coord.y + 1));
}
bool SuperGhost::decideIfClimb()
{
	if (isOnLadder() && isMarioabove())
		dir.y = -1;
	else if (isOnLadder() && isMarioUnder() && dir.y != 0)
		dir.y = 1;
	else if (isAboveLadder() && isMarioUnder())
		dir.y = 1;
	else
		return false;
	ladderFlag = true;
	return true;
}
bool SuperGhost::isMarioabove()
{
	Point Mariocrd = pBoard->marioGetCoord();
	return Mariocrd.y < coord.y;
}
bool SuperGhost::isMarioUnder()
{
	Point Mariocrd = pBoard->marioGetCoord();
	return Mariocrd.y > coord.y;
}
void SuperGhost::moveOnLadder() {
	coord.y += dir.y;
}