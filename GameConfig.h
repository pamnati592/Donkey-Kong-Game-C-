#ifndef __GAMECONFIG_H
#define __GAMECONFIG_H

#include "Direction.h"

class Board;

class GameConfig
{
public:
	static constexpr int INACTIVE_X = -1;
	static constexpr int INACTIVE_Y = -1;
	static constexpr int MAX_X = 80;
	static constexpr int MAX_Y = 25;
	static constexpr int STAGES_X = 37;
	static constexpr int STAGES_Y = 14;
	static constexpr const char* PAUSE_MSG = "Paused";
	static constexpr int MAX_LIVES_STRING_LEN = 12;
	static constexpr int SCORE_PER_HIT = 100;
	static constexpr Direction INIT_DIR = { 0, 0 };
	static constexpr Direction INIT_DIR_L = { -1, 0 };
	static constexpr Direction INIT_DIR_R = { 1, 0 };
	enum class eKeys {
		UP = 'w',
		DOWN = 'x',
		LEFT = 'a',
		RIGHT = 'd',
		STAY = 's',
		ATTACK = 'p',
		ESC = 27,
		START = '1',
		STAGE = '7',
		INST = '8',		// Game instructions display
		EXIT = '9'
	};
	
	enum class eSymbols {
		SPACE = ' ',
		WALL = 'Q',
		LADDER = 'H',
		FLOOR = '=',
		RFLOOR = '>',
		LFLOOR = '<',
		PAULINE = '$',
		MARIO = '@',
		DK = '&',
		BARREL = 'O',
		GHOST = 'x' ,
		SUPERGHOST = 'X',
		HAMMER = 'p',
		DATA = 'L'
	};
	using StageBoard = char[GameConfig::MAX_Y][GameConfig::MAX_X+1];
	
	static bool isValidKey(char ch);
};

#endif