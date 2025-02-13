#include "GameEntity.h"
#include "Board.h"

void GameEntity::erase(bool silent) const {
	if (!silent)
		draw(pBoard->getSymbolByPoint(coord), silent);
}
void GameEntity::move() {
	coord.x += dir.x;
	coord.y += dir.y;
}
void GameEntity::draw(GameConfig::eSymbols _symbol, bool silent) const {
	if (!silent) {
		gotoxy(coord.x, coord.y);
		std::cout << (char)_symbol;
	}
}
