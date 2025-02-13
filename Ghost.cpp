#include "Ghost.h"
#include "GameConfig.h"
#include "Board.h"
#include "Utils.h"
#include "Point.h"
#include "Direction.h"
#include <random>
#include <iostream>

Ghost::Ghost(Board* _pBoard) :
	GameEntity(Point(), GameConfig::INIT_DIR_R, _pBoard),
	activeFlag(true) {
	coord = findGhost(*pBoard, GameConfig::eSymbols::GHOST);
}
Ghost::Ghost(Board* _pBoard, GameConfig::eSymbols _symbol) :
	GameEntity(Point(), GameConfig::INIT_DIR_R, _pBoard),
	activeFlag(true) {
	coord = findGhost(*pBoard, _symbol);
}

void Ghost::move(size_t index) {
	pBoard->getRandomGhostDir(&dir, index);
	checkHitWall();
	checkEndFloor();
	GameEntity::move();
}
void Ghost::draw(bool silent) const { GameEntity::draw(GameConfig::eSymbols::GHOST, silent); }
Point Ghost::findGhost(const Board& board, GameConfig::eSymbols _symbol) {
	for (int y = 0; y < GameConfig::MAX_Y; ++y) {
		for (int x = 0; x < GameConfig::MAX_X; ++x) {
			if (board.getInitSymbolByPoint(x, y) == _symbol) {
				pBoard->updateInitBoardSymbolAt(Point(x, y), GameConfig::eSymbols::SPACE);
				return Point(x, y);
			}
		}
	}
	return Point(0, 0);
}
void Ghost::checkHitWall() {
	if (pBoard->getSymbolByPoint(coord.x + dir.x, coord.y + dir.y) == GameConfig::eSymbols::WALL) {
		dir = -dir;
	}
}
void Ghost::checkEndFloor() {
	if (pBoard->getSymbolByPoint(coord.x + dir.x, coord.y + 1) == GameConfig::eSymbols::SPACE &&
		coord.y < GameConfig::MAX_Y) {
		dir = -dir;
	}
}

bool Ghost::checkHitGhost() const {
	return pBoard->getSymbolByPoint(coord.x + dir.x, coord.y) == GameConfig::eSymbols::GHOST ||
		pBoard->getSymbolByPoint(coord.x + dir.x, coord.y) == GameConfig::eSymbols::SUPERGHOST;
}
//void Ghost::draw(GameConfig::eSymbols _symbol) const {
//	gotoxy(coord.x, coord.y);
//	std::cout << (char)_symbol;
//}