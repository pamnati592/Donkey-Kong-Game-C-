#ifndef __GAME_ENTITY_H
#define __GAME_ENTITY_H
#include "Point.h"
#include "Direction.h"

class GameEntity {
protected:
	Point coord;
	Direction dir;
	Board* pBoard;

public:
	GameEntity(Point _crd, Direction _dir, Board* _pBoard) :
		coord(_crd),
		dir(_dir),
		pBoard(_pBoard) {}

	void erase(bool silent) const;
	void move();
	Point getLocation() const { return coord; }

protected:
	void draw(GameConfig::eSymbols _symbol, bool silent) const;
};
#endif
