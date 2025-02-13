#ifndef __GAME_H
#define __GAME_H
#include "Board.h"
#include "Mario.h"
#include "Barrel.h"
#include "Point.h"
#include "Ghost.h"
#include "Stage.h"
#include <vector>
#include "ModeManager.h"

class Game
{
	const char* gameOverScreen[GameConfig::MAX_Y] =
	{
		//01234567890123456789012345678901234567890123456789012345678901234567890123456789
		 "                                                                                " , //1
		 "                                                                                " , //2
		 "             ________   ________   _____ ______   ______                     " , //3
		 "            |\\   ____\\ |\\   __  \\|\\   _  \\ _   \\|\\  ___ \\                      " , //4
		 "            \\ \\  \\___| \\ \\  \\|\\  \\ \\  \\\\\\__\\ \\  \\ \\   __/|                   " , //5
		 "             \\ \\  \\   __\\ \\   __  \\ \\  \\\\|__| \\  \\ \\  \\_|/__                  " , //6
		 "              \\ \\  \\|\\   \\ \\  \\ \\  \\ \\  \\    \\ \\  \\ \\  \\_|\\ \\               " , //7
		 "               \\ \\________\\ \\__\\ \\__\\ \\__\\    \\ \\__\\ \\_______\\                 " , //8
		 "                \\|________|\\|__|\\|__|\\|__|     \\|__|\\|_______|      	" , //9
		 "                                                                                    " , //10
		 "                ________  ___      ___ _______   ________                    " , //11
		 "               |\\   __  \\|\\  \\    /  /|\\  ___ \\ |\\   __  \\                   " , //12
		 "               \\ \\  \\|\\  \\ \\  \\  /  / | \\   __/|\\ \\  \\|\\  \\                  " , //13
		 "                \\ \\  \\\\\\  \\ \\  \\/  / / \\ \\  \\_|/_\\ \\   _  _\\                 " , //14
		 "                 \\ \\  \\\\\\  \\ \\    / /   \\ \\  \\_|\\ \\ \\  \\\\  \\|                " , //15
		 "                  \\ \\_______\\ \\__/ /     \\ \\_______\\ \\__\\\\ _\\                " , //16
		 "                   \\|_______|\\|__|/       \\|_______|\\|__|\\|__|               " , //17
		 "                                                                                    " , //18
		 "                                                                                " , //19
		 "                 Press any key to return to the main menu                       " , //20
		 "                                                                                " , //21
		 "                                                                                " , //22
		 "                                                                                " , //23
		 "                                                                                " , //24
		 "                                                                                " , //25
	};
	const char* stageClearedScreen[GameConfig::MAX_Y] =
	{
		//01234567890123456789012345678901234567890123456789012345678901234567890123456789
		"                                                                                ", // 1
		"                                                                                ", // 2
		"                         (                                                      ", // 3
		"                         )\\ )  *   )   (     (                                  ", // 4
		"                        (()/(` )  /(   )\\    )\\ )   (                           ", // 5
		"                         /(_))( )(_)|(((_)( (()/(   )\\                          ", // 6
		"                        (_)) (_(_()) )\\ _ )\\ /(_))_((_)                         ", // 7
		"                        / __||_   _| (_)_\\(_|_)) __| __|                        ", // 8
		"                        \\__ \\  | |    / _ \\   | (_ | _|                         ", // 9
		"                        |___/  (_|   /_/ \\_\\   (___|__(|                        ", // 10
		"                           (   )\\ )      (     )\\ )   )\\ )                      ", // 11
		"                           )\\ (()/( (    )\\   (()/(( (()/(                      ", // 12
		"                         (((_) /(_)))\\((((_)(  /(_))\\ /(_))                     ", // 13
		"                         )\\___(_)) ((_))\\ _ )\\(_))((_|_))_                      ", // 14
		"                        ((/ __| |  | __(_)_\\(_) _ \\ __|   \\                     ", // 15
		"                         | (__| |__| _| / _ \\ |   / _|| |) |                    ", // 16
		"                          \\___|____|___/_/ \\_\\|_|_\\___|___/                     ", // 17
		"                                                                                ", // 18
		"                    									                         ", // 19
		"                    									                         ", // 20
		"                  Press any key to continue to the next stage                   ", //21
		"                    									                         ", // 22
		"                    									                         ", // 23
		"                    									                         ", // 24
		"                    									                         "  // 25
	};
	const char* winnerScreen[GameConfig::MAX_Y] = {
	"                                                                                ", // 1
	"                                                                                ", // 2
	"                                                                                ", // 3
	"                                                                                ", // 4
	"      //   __   __   U  ___ u   _   _                         U  ___ u       ", // 5
	"     \\ \\ / /    \\/ _ \\/U | |u| |         __        __    \\/ _ \\/ | \\ | |     ", // 6
	"      \\ V /     | | | | \\| |\\| |         \\'\\      / /    | | | |<|  \\| |>    ", // 7
	"     U_| |_u.-,_| |_| |  | |_| |         /\\ \\ /\\ / /\\.-,_| |_| |U| |\\  |u    ", // 8
	"       |_|   \\_)-\\___/  <<\\___/         U  \\ V  V /  U\\_)-\\___/  |_| \\_|     ", // 9
	"   .-,//|(_       \\\\   (__) )(          .-,_\\ /\\ /_,-.     \\\\    ||   \\\\     ", // 10
	"    \\_) (__)     (__)      (__)          \\_)-'  '-(_/     (__)   (_)  (_/    ", // 11
	"                                                                                ", // 12
	"                                                                                ", // 13
	"                                                                                ", // 14
	"                                                                                ", // 15
	"                                                                                ", // 16
	"                    Press any key to return to the menu.                        ", // 17
	"                                                                                ", // 18
	"                                                                                ", // 19
	"                                                                                ", // 20
	"                                                                                ", // 21
	"                                                                                ", // 22
	"                                                                                ", // 23
	"                                                                                ", // 24
	"                                                                                "  // 25
	};
	int currentStageIndex;
	std::vector<Stage> stages;
	ModeManager modeManager;
	Board gameBoard;
public:
	Game(const std::vector<Stage>& _stages, const int& initStageIndex, const Mode& _mode);
	void run();
	bool isStageCleard() const;
	void pause(Point crdData);
	std::string getCurrStageName();
private:
	Board& getBoard() { return gameBoard; }
	bool isStageOn() const;
	void initiateGame();
	void runBoardPrePace();
	void paceControl();
	void runBoardPostPace();
	void gameOver();
	void runGameCycle();
	void handleStageCleared();
	void showStageClearedScreen();
	void showWinnerScreen();
	void handleGameFinished();
	bool checkSilentTest(bool finished);
	const GameConfig::StageBoard& getNextStageBoard();
};

#endif