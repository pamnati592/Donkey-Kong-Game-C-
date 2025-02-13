#ifndef __BARREL_H
#define __BARREL_H
#include "GameEntity.h"
#include "GameConfig.h"
#include "Utils.h"
#include "Board.h"

class Barrel : public GameEntity {

	static constexpr int FINAL_X = 1;
	static constexpr int FINAL_Y = 22;
	static constexpr int EXPLOSION_FALL_HEIGHT = 8;
	static constexpr int LETHAL_DISTANCE_FROM_EXPLOSION = 2;

	int fallCount;
	bool fallFlag, explosionFlag, destroyedFlag;

public:
	Barrel(Board* _pBoard, size_t index) : Barrel(_pBoard->getDKCoord(), _pBoard, index) {}
	Barrel(Point _crd, Board* _pBoard, size_t index);
	
	void draw(bool silent) const;
	void move();
	void setFallDir();
	void setDirAfterFall();
	void setDestroyed(bool destroyed) { destroyedFlag = destroyed; }
	void setDirectionByfloor();
	bool isDeactivated() const;
	bool isHurtMario(Point marioCoord) const;

private:
	void draw(GameConfig::eSymbols symbol) const;
	GameConfig::eSymbols getFloor() const;
	bool isExploded() const;
	void checkBarrelExplosion();
	bool checkHitFloor() const;
	void checkHitWall();
	bool checkMarioHit(Point marioCoord) const;
	bool checkMarioNearExplosion(Point marioCoord) const;
	bool isDestroyed() const { return destroyedFlag; }
};
#endif