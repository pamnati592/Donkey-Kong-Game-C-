#include "Barrel.h"

Barrel::Barrel(Point _crd, Board* _pBoard, size_t index) :
	GameEntity(_crd, GameConfig::INIT_DIR, _pBoard),
	fallCount(0),
	fallFlag(false), explosionFlag(false), destroyedFlag(false) {
	pBoard->getRandomBarrelDir(&dir, index);
	coord.x = (dir.x > 0) ? coord.x + 1 : coord.x - 1;

}

void Barrel::draw(bool silent) const { GameEntity::draw(GameConfig::eSymbols::BARREL, silent); }
void Barrel::setDirectionByfloor() {
	GameConfig::eSymbols floor = getFloor();
	if (fallFlag)
		fallCount++;
	else {
		switch (floor)
		{
		case GameConfig::eSymbols::SPACE:
			setFallDir();
			fallFlag = true;
			break;
		case GameConfig::eSymbols::RFLOOR:
			dir = GameConfig::INIT_DIR_R;
			break;
		case GameConfig::eSymbols::LFLOOR:
			dir = GameConfig::INIT_DIR_L;
			break;
		default:
			break;
		}
	}
}
void Barrel::move()
{
	checkBarrelExplosion();
	if (checkHitFloor()) {
		setDirAfterFall();
	}
	checkHitWall();
	if (isDeactivated()) {
		dir = GameConfig::INIT_DIR;
	}
	GameEntity::move();
}
GameConfig::eSymbols Barrel::getFloor() const {
	return pBoard->getSymbolByPoint(coord.x, coord.y + 1);
}
bool Barrel::checkHitFloor() const
{
	GameConfig::eSymbols nextCoord = pBoard->getSymbolByPoint(coord.x + dir.x, coord.y + dir.y);
	return (nextCoord == GameConfig::eSymbols::FLOOR ||
			nextCoord == GameConfig::eSymbols::LFLOOR ||
			nextCoord == GameConfig::eSymbols::RFLOOR ||
			coord.y == GameConfig::MAX_Y-1);

}
void Barrel::checkHitWall() {
	if (pBoard->getSymbolByPoint(coord.x + dir.x, coord.y + dir.y) == GameConfig::eSymbols::WALL)
		destroyedFlag = true;
}
void Barrel::checkBarrelExplosion() {
	explosionFlag = fallCount >= EXPLOSION_FALL_HEIGHT && checkHitFloor();
}
void Barrel::setFallDir() {
	dir.y = 1;
}
void Barrel::setDirAfterFall() {
	fallFlag = false;
	fallCount = 0;
	dir.y = 0;
}
bool Barrel::isExploded()const {
	return explosionFlag;
}
bool Barrel::isDeactivated() const {
	return isExploded() || isDestroyed();
}
bool Barrel::checkMarioHit(Point marioCoord) const {
	return coord == marioCoord;
}
bool Barrel::checkMarioNearExplosion(Point marioCoord) const
{
	if (isExploded()) {
		return (abs(marioCoord.x - coord.x) <= LETHAL_DISTANCE_FROM_EXPLOSION && abs(marioCoord.y - coord.y) <= LETHAL_DISTANCE_FROM_EXPLOSION);
	}
	return false; // Barrel hasn't exploded
}
bool Barrel::isHurtMario(Point marioCoord) const {
	return checkMarioHit(marioCoord) || checkMarioNearExplosion(marioCoord);
}