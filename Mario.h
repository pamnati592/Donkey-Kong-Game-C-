#ifndef __MARIO_H
#define __MARIO_H
#include "GameEntity.h"
#include "GameConfig.h"
#include "ModeManager.h"

class Mario : public GameEntity {
	static constexpr int MAX_LIVES = 3;
	static constexpr int RESPAWN_BLINKS = 3;
	static constexpr int LETHAL_FALL_HEIGHT = 5;
	static constexpr Direction INIT_DIR = { 0, 0 };

	ModeManager* modeManager;
	Point crdInit;
	int lives, jumpCount, fallCount, ladderCount;
	bool jumpFlag, fallFlag, DeadlyFall, ladderDownFlag, armedFlag, attackFlag;

public:
	Mario(Board* _pBoard, ModeManager* _modeManager) : Mario(crdInit, _pBoard, _modeManager) {}
	Mario(Point _crdInit, Board* _pBoard, ModeManager* _modeManager);

	void draw() const;
	void move();
	bool isDeadlyFall();
	void setDirectionByKey(GameConfig::eKeys key);
	int getLives() const { return lives; }
	bool isAlive() const { return lives > 0; }
	bool reachedPauline() const;
	void reduceLife();
	void toStartPoint();
	void respawn();
	void setAttack(bool isAttack) { attackFlag = isAttack; }
	bool isAttack() const { return attackFlag; }
	void setArmed(bool isArmed) { armedFlag = isArmed; }
	bool isArmed() const { return armedFlag; }
	void setInitCoord(Point crd);
private:
	void handleLadder();
	void handleFall();
	void setJumpDir();
	void handleJump();
	void checkHitWall();
	bool checkHitFloor();
	bool checkLethalFall();
	bool isOnLadder() const;
	bool isOnFloor() const;
	bool isAboveLadder() const ;
	bool isFalling() const;
	void checkHammer();

};
#endif