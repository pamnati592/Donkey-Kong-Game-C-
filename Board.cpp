#include "Board.h"
#include <conio.h>
#include "Utils.h"
#include "Point.h"
#include "Game.h"
#include "Barrel.h"
#include "Ghost.h"
#include <iostream>
#include "SuperGhost.h"
#include "ModeManager.h"

using namespace std;

Board::Board(Game* _pGame, const GameConfig::StageBoard& stageBoard, ModeManager* _modeManager) :
	modeManager(_modeManager),
	pGame(_pGame),
	mario(this, _modeManager),
	activeBarrelsCount(0),
	activeghostCount(0),
	barrelSpawnTimer(0),
	score(0) {
	setInitBoard(stageBoard);
	setEntitiesCoord();
	initBarrels();
}
Board::Board(const Board& other) :
	modeManager(other.modeManager),
	pGame(other.pGame),
	mario(this, other.modeManager),
	activeBarrelsCount(other.activeBarrelsCount),
	activeghostCount(other.activeghostCount),
	barrelSpawnTimer(other.barrelSpawnTimer),
	score(other.score),
	crdData(other.crdData),
	crdPauline(other.crdPauline),
	crdDK(other.crdDK),
	crdHammer(other.crdHammer) {

	for (size_t i = 0; i < GameConfig::MAX_Y; ++i) {
		if (other.initBoard[i] != nullptr) {
			initBoard[i] = new char[GameConfig::MAX_X + 1];
			memcpy(initBoard[i], other.initBoard[i], GameConfig::MAX_X + 1);
		}
		else {
			initBoard[i] = nullptr;
		}
	}

	for (size_t i = 0; i < GameConfig::MAX_Y; ++i) {
		memcpy(currentBoard[i], other.currentBoard[i], GameConfig::MAX_X + 1);
	}

	for (size_t i = 0; i < MAX_BARRELS; ++i) {
		if (other.barrels[i] != nullptr) {
			barrels[i] = new Barrel(*other.barrels[i]); // Assumes Barrel has a proper copy constructor
		}
		else {
			barrels[i] = nullptr;
		}
	}

	for (size_t i = 0; i < MAX_GHOSTS; ++i) {
		if (other.ghosts[i] != nullptr) {
			ghosts[i] = new Ghost(*other.ghosts[i]); // Assumes Ghost has a proper copy constructor
		}
		else {
			ghosts[i] = nullptr;
		}
	}
}
Board::~Board() {
	deleteInitBoard();
	deleteBarrels();
	resetGhosts();
}

// Board management
void Board::setInitBoard(const GameConfig::StageBoard& stageBoard) {
	for (size_t i = 0; i < GameConfig::MAX_Y; ++i) {
		initBoard[i] = new char[GameConfig::MAX_X + 1];
		memcpy(initBoard[i], stageBoard[i], GameConfig::MAX_X + 1);
	}
}
void Board::initializeBoard() {
	for (size_t i = 0; i < GameConfig::MAX_Y; ++i) {
		memcpy(currentBoard[i], initBoard[i], GameConfig::MAX_X + 1);
	}
}
void Board::printBoard() {
	gotoxy(0, 0);
	for (size_t i = 0; i < GameConfig::MAX_Y; ++i) {
		cout << currentBoard[i];
	}
}
void Board::updateInitBoardSymbolAt(Point p, GameConfig::eSymbols symbol) {
	initBoard[p.y][p.x] = (char)symbol; // Update the board's symbol
}
void Board::updateCurrentBoardSymbolAt(Point p, GameConfig::eSymbols symbol) {
	currentBoard[p.y][p.x] = (char)symbol; // Update the board's symbol
}
const Point& Board::getDKCoord() {
	return crdDK;
}
const Point& Board::getHammerCoord() {
	return crdHammer;
}
void Board::setEntitiesCoord() {
	mario.setInitCoord(findEntity(GameConfig::eSymbols::MARIO));
	crdData = findEntity(GameConfig::eSymbols::DATA);
	crdPauline = findEntity(GameConfig::eSymbols::PAULINE);
	crdDK = findEntity(GameConfig::eSymbols::DK);
	crdHammer = findEntity(GameConfig::eSymbols::HAMMER);
}
Point Board::findEntity(GameConfig::eSymbols entity) const {
	for (int y = 0; y < GameConfig::MAX_Y; y++) {
		for (int x = 0; x < GameConfig::MAX_X; x++) {
			if (getInitSymbolByPoint(x, y) == entity)
				return Point(x, y);
		}
	}
	return Point(-1, -1);
}
void Board::setNewStage(const GameConfig::StageBoard& stageBoard) {
	setInitBoard(stageBoard);
	setEntitiesCoord();
	resetBoard();
	resetGhosts();
	mario.toStartPoint();
}
void Board::eraseHammer() {
	updateCurrentBoardSymbolAt(crdHammer, GameConfig::eSymbols::SPACE);
	gotop(crdHammer);
	cout << (char)GameConfig::eSymbols::SPACE;
}
void Board::deleteInitBoard() {
	for (size_t i = 0; i < GameConfig::MAX_Y; ++i) {
		if (initBoard[i] != nullptr) {
			delete[] initBoard[i];
			initBoard[i] = nullptr;
		}
	}
}
void Board::resetSuperGhost() {
	// for (int i = 0; i < activeghostCount; i++) {
	for (int i = 0; i < ghosts.size(); i++) {
		SuperGhost* superGhost = dynamic_cast<SuperGhost*>(ghosts[i]);
		if (superGhost)
			superGhost->SetInitCord();
	}
}
// Run cycle
void Board::handleMarioPrePace() {
	GameConfig::eKeys key = GameConfig::eKeys::STAY;
	mario.draw();
	if (modeManager->getKBHit(&key)) {
		switch (key) {
		case GameConfig::eKeys::ESC:
			pGame->pause(this->crdData);
			break;
		case GameConfig::eKeys::UP:
		case GameConfig::eKeys::LEFT:
		case GameConfig::eKeys::RIGHT:
		case GameConfig::eKeys::DOWN:
		case GameConfig::eKeys::STAY:
		case GameConfig::eKeys::ATTACK:
			mario.setDirectionByKey(key);
			break;
		default:
			break;
		}
	}
}
void Board::handleMarioPostPace() {
	mario.erase(modeManager->getSilent());
	mario.move();
	if (mario.isDeadlyFall()) {
		resetBoard();
	}
}
void Board::handleBarrelsPrePace() {
	deleteBarrels();
	for (size_t i = 0; i < activeBarrelsCount; i++) {
		barrels[i]->draw(modeManager->getSilent());
		barrels[i]->setDirectionByfloor();
	}
}
void Board::handleBarrelsPostPace() {
	deleteBarrels();
	for (size_t i = 0; i < activeBarrelsCount; i++) {
		if (checkCollisionBarrel(i))
			break;
		barrels[i]->erase(modeManager->getSilent());
		barrels[i]->move();
		if (checkCollisionBarrel(i))
			break;
	}
	spawnBarrel();
}
void Board::handleGhostPrePace() {
	deleteGhosts();
	for (auto ghost : ghosts)
		ghost->draw(modeManager->getSilent());
	/*for (size_t i = 0; i < activeghostCount; i++) {
		ghosts[i]->draw();
	}*/
}
void Board::handleGhostPostPace() {
	checkGhostMeets();
	/*for (vector<Ghost*>::iterator it = ghosts.begin(); it != ghosts.end(); it++) {
		if (checkCollisionGhost(it))
			break;
		(*it)->erase();
		(*it)->move();
		if (checkCollisionGhost(it))
			break;
	}*/
	for (size_t i = 0; i < ghosts.size(); i++) {
		if (checkCollisionGhost(i))
			break;

		ghosts[i]->erase(modeManager->getSilent());
		ghosts[i]->move(i);

		if (checkCollisionGhost(i))
			break;
	}
	deleteGhosts();
}
void Board::resetBoard() {
	initializeBoard();
	if (!modeManager->getSilent())
		printBoard();
	mario.setArmed(false);
	resetBarrels();
	resetSuperGhost();
}
// Barrels
void Board::initBarrels() {
	for (size_t i = 0; i < MAX_BARRELS; i++) {
		barrels[i] = nullptr;
	}
}
void Board::spawnBarrel() {
	if (barrelSpawnTimer == 0 && activeBarrelsCount < MAX_BARRELS) {
		barrels[activeBarrelsCount] = new Barrel(this, activeBarrelsCount);
		activeBarrelsCount++;
		barrelSpawnTimer = BARREL_SPAWN_INTERVAL;
	}
	else
		barrelSpawnTimer--;
}
void Board::deleteBarrel(size_t barrelIndex) {
	delete barrels[barrelIndex];
	barrels[barrelIndex] = nullptr;

	for (size_t i = barrelIndex; i < activeBarrelsCount - 1; i++) {
		barrels[i] = barrels[i + 1];
	}
	barrels[activeBarrelsCount - 1] = nullptr;
	activeBarrelsCount--;
}
void Board::deleteBarrels() {
	for (size_t i = 0; i < activeBarrelsCount; i++) {
		if (barrels[i]->isDeactivated())
			deleteBarrel(i);
	}
}
void Board::resetBarrels() {
	activeBarrelsCount = 0;
	barrelSpawnTimer = BARREL_SPAWN_INTERVAL;
	for (size_t i = 0; i < MAX_BARRELS; i++) {
		if (barrels[i] != nullptr) {
			delete barrels[i];
			barrels[i] = nullptr;
		}
	}
}
bool Board::checkCollisionBarrel(size_t barrelIndex) {
	if (barrels[barrelIndex]->isHurtMario(mario.getLocation())) {
		if (mario.isAttack()) {
			barrels[barrelIndex]->setDestroyed(true);
			addScore();
			return true;
		}
		else
			mario.reduceLife();
		resetBoard();
		return true;
	}
	return false;
}
void Board::getRandomBarrelDir(Direction* dir, size_t index) {
	modeManager->getRandomBarrelDir(dir, index);
}

// Ghosts
bool Board::spawnGhost() {
	// Check if we've reached the maximum number of ghosts
	if (ghosts.size() >= MAX_GHOSTS) {
		std::cerr << "Maximum number of ghosts reached!" << std::endl;
		return false;
	}

	Ghost* newGhost = new Ghost(this);
	if (newGhost->getLocation().x == 0 && newGhost->getLocation().y == 0) {
		delete newGhost;
		return false;
	}

	ghosts.push_back(newGhost);
	return true;
}
bool Board::spawnSuperGhost() {
	// Check if we've reached the maximum number of ghosts
	if (ghosts.size() >= MAX_GHOSTS) {
		std::cerr << "Maximum number of ghosts reached!" << std::endl;
		return false;
	}

	// Create a new SuperGhost and add it to the vector
	Ghost* newSuperGhost = new SuperGhost(this);
	if (newSuperGhost->getLocation().x == 0 && newSuperGhost->getLocation().y == 0) {
		delete newSuperGhost; // Free the memory if the ghost's location is invalid
		return false;
	}

	ghosts.push_back(newSuperGhost); // Add the SuperGhost to the vector
	return true;
}
void Board::spawnGhosts() {
	while (spawnGhost());
	while (spawnSuperGhost());
}
void Board::deleteGhosts() {
	for (auto it = ghosts.begin(); it != ghosts.end();) {
		if (!(*it)->isActive()) {
			delete* it;
			it = ghosts.erase(it);
		}
		else
			it++;
	}
}
bool Board::isCoordFloor(Point _coord) const {
	GameConfig::eSymbols symbol = getSymbolByPoint(_coord);
	return (symbol == GameConfig::eSymbols::FLOOR ||
		symbol == GameConfig::eSymbols::RFLOOR ||
		symbol == GameConfig::eSymbols::LFLOOR ||
		symbol == GameConfig::eSymbols::WALL ||
		_coord.y == GameConfig::MAX_Y);
}
void Board::resetGhosts() {
	for (Ghost* ghost : ghosts) {
		delete ghost; // Free the memory for each ghost
	}
	ghosts.clear(); // Remove all pointers from the vector
}
//bool Board::checkCollisionGhost(vector<Ghost*>::iterator it) {
//	if ((*it)->checkMarioHit(mario.getLocation())) {
//		if (mario.isAttack()) {
//			(*it)->deactivate();
//			score += GameConfig::SCORE_PER_HIT;
//			return true;
//		}
//		mario.reduceLife();
//		resetBoard();
//		return true;
//	}
//	return false;
//}
bool Board::checkCollisionGhost(size_t index) {
	if (index >= ghosts.size()) // Ensure index is valid
		return false;

	Ghost* ghost = ghosts[index]; // Get ghost pointer

	if (ghost->checkMarioHit(mario.getLocation())) {
		if (mario.isAttack()) {
			ghost->deactivate();
			addScore();
			return true;
		}
		mario.reduceLife();
		resetBoard();
		return true;
	}
	return false;
}
void Board::checkGhostMeets() {
	for (Ghost* ghost : ghosts) {
		if (ghost->checkHitGhost())
			ghost->setDir(-(ghost->getDir()));
	}
	//// for (int i = 0; i < activeghostCount; i++)
	//for (int i = 0; i < ghosts.size(); i++)
	//{
	//	if (ghosts[i]->checkHitGhost())
	//		ghosts[i]->setDir(-(ghosts[i]->getDir()));
	//}
}
void Board::getRandomGhostDir(Direction* dir, size_t index) {
	modeManager->getRandomGhostDir(dir, index);
}
// Data
void Board::addScore() {
	score += GameConfig::SCORE_PER_HIT;
	modeManager->score();
}
void Board::displayData() const {
	if (!modeManager->getSilent()) {
		displayLives();
		displayScore();
		displayHammer();
	}
}
void Board::displayLives() const {
	int i = 0;
	gotop(crdData);
	cout << "Lives: ";
	for (i = 0; i < mario.getLives(); i++) {
		cout << "\x03 ";
	}
	for (; i < 3; i++) {
		cout << "  ";
	}
}
void Board::displayScore() const {
	gotoxy(crdData.x, crdData.y + 1);
	cout << "Score: " << score;
}
void Board::displayHammer() const {
	gotoxy(crdData.x, crdData.y + 2);
	cout << "Hammer: ";
	cout << (mario.isArmed() ? "Yes" : "No");
}
bool Board::isMarioReachedPauline() const
{
	return mario.reachedPauline();
}
bool Board::isMarioAlive() const {
	return mario.isAlive();
}
Point Board::marioGetCoord() const {
	return mario.getLocation();
}
void Board::setMarioAttack(bool isAttack) {
	mario.setAttack(isAttack);
}
