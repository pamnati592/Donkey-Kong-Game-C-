#include "Mario.h"
#include "Utils.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Game.h"

Mario::Mario(Point _crdInit, Board* _pBoard, ModeManager* _modeManager) :
	GameEntity(_crdInit, INIT_DIR, _pBoard),
	modeManager(_modeManager),
	crdInit(_crdInit),
	lives(MAX_LIVES), jumpCount(0), fallCount(0), ladderCount(0),
	jumpFlag(false), fallFlag(false), DeadlyFall(false), ladderDownFlag(false), armedFlag(false), attackFlag(false) {}

void Mario::setInitCoord(Point crd) {
	crdInit = crd;
	toStartPoint();

	pBoard->updateInitBoardSymbolAt(crd, GameConfig::eSymbols::SPACE);
}
//void Mario::draw(GameConfig::eSymbols _symbol) const {
//	gotoxy(coord.x, coord.y);
//	std::cout << (char)_symbol;
//}
void Mario::draw() const { GameEntity::draw(GameConfig::eSymbols::MARIO, modeManager->getSilent()); }
void Mario::setDirectionByKey(GameConfig::eKeys key) {
	if (!fallFlag && isOnFloor()) {
		switch (key)
		{
		case GameConfig::eKeys::UP:
			if (isOnLadder()) { dir = { 0, -1 }; }
			else
				setJumpDir();
			break;
		case GameConfig::eKeys::DOWN:
			if (isAboveLadder()) { dir = { 0, 1 }; }
			break;
		case GameConfig::eKeys::LEFT:
			dir = { -1, 0 };
			break;
		case GameConfig::eKeys::RIGHT:
			dir = { 1, 0 };

			break;
		case GameConfig::eKeys::STAY:
			dir = { 0, 0 };
			break;
		case GameConfig::eKeys::ATTACK:
			if(armedFlag)
			Mario::attackFlag = true;
		}
	}
}
void Mario::checkHammer() {
	if (pBoard->getSymbolByPoint(coord.x, coord.y) == GameConfig::eSymbols::HAMMER) {
		armedFlag = true;
		pBoard->eraseHammer();
	}
}
void Mario::reduceLife() {
	if (lives > 0) {
		--lives;
		toStartPoint();
	}
	modeManager->reduceLife();
	respawn();
}
void Mario::toStartPoint() {
	coord = crdInit;
	dir = GameConfig::INIT_DIR;
}
void Mario::respawn() {
	if (!modeManager->getSilent()) {
		const int RESPAWN_INTERVAL = 400;
		for (size_t i = 0; i < RESPAWN_BLINKS; i++) {
			Sleep(RESPAWN_INTERVAL);
			erase(false);
			Sleep(RESPAWN_INTERVAL);
			draw();
		}
	}
}
bool Mario::reachedPauline() const {
	return pBoard->getSymbolByPoint(coord.x, coord.y) == GameConfig::eSymbols::PAULINE;
}
void Mario::move() {
	handleLadder();
	handleFall();
	handleJump();
	checkHitFloor();
	checkHitWall();
	checkHammer();
	GameEntity::move();
}
void Mario::handleJump() {
	if (jumpFlag) {
		if (!jumpCount) {
			dir.y = 1;
			jumpFlag = false;
		}
		else
			dir.y = -1;
		jumpCount--;
	}
}
void Mario::setJumpDir() {
	if (!jumpFlag) {
		jumpFlag = true;
		jumpCount = 2;
	}
}
void Mario::handleFall() {
	if (fallFlag) {
		if (checkLethalFall() && checkHitFloor())
			reduceLife();
		else
			fallCount++;
	}
	else if (isFalling()) {
		fallFlag = true;
		dir.y = 1;
	}
}
bool Mario::checkLethalFall() {
	return (fallCount >= LETHAL_FALL_HEIGHT) ? DeadlyFall = true : false;
}
bool Mario::checkHitFloor() {
	if (pBoard->isCoordFloor(Point(coord.x, coord.y + dir.y))) {
		ladderDownFlag = false;
		fallFlag = false;
		fallCount = 0;
		dir.y = 0;
		return true;
	}
	return false;
}
bool Mario::isFalling() const {
	return (pBoard->getSymbolByPoint(coord.x, coord.y + 1) == GameConfig::eSymbols::SPACE);
}
bool Mario::isDeadlyFall() {
	return DeadlyFall ? !(DeadlyFall = false) : false;
}
void Mario::handleLadder() {
	// Finishing climbing up
	if (pBoard->isCoordFloor(Point(coord.x, coord.y - 1)) && isOnLadder() && dir.y < 0) {
		dir.y = 0;
		coord.y -= 2;
	}
	// Stating climbing down
	else if (isAboveLadder() && dir.y > 0 && !ladderDownFlag && !fallFlag) {
		coord.y += 1;
		ladderDownFlag = true;
	}
}
bool Mario::isOnLadder() const
{
	return (pBoard->getSymbolByPoint(coord.x, coord.y) == GameConfig::eSymbols::LADDER);
}
bool Mario::isAboveLadder() const
{
	return (isOnFloor() && pBoard->getSymbolByPoint(coord.x, coord.y + 2) == GameConfig::eSymbols::LADDER);
}
void Mario::checkHitWall() {
	if (pBoard->getSymbolByPoint(coord.x, coord.y + dir.y) == GameConfig::eSymbols::WALL) {
		dir.y = 0;
	}
	if (pBoard->getSymbolByPoint(coord.x + dir.x, coord.y) == GameConfig::eSymbols::WALL ||
		pBoard->isCoordFloor(Point (coord.x + dir.x, coord.y))) {
		dir.x = 0;
	}
}
bool Mario::isOnFloor() const {
	return pBoard->isCoordFloor(Point(coord.x, coord.y+1 ));
}
