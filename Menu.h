#ifndef __NENU_H
#define __MENU_H
#include "Game.h"
#include "GameConfig.h"
#include <conio.h>
#include <vector>

class ModeManager;

class Menu
{
    const char* menuPrompt[GameConfig::MAX_Y] =
    {
        "                                                                                ", //1
        "        ________  ________  ________   ___  __    _______       ___    ___      ", //2
        "       |\\   ___ \\|\\   __  \\|\\   ___  \\|\\  \\|\\  \\ |\\  ___ \\     |\\  \\  /  /|     ", //3
        "       \\ \\  \\_|\\ \\ \\  \\|\\  \\ \\  \\\\ \\  \\ \\  \\/  /|\\ \\   __/|    \\ \\  \\/  / /     ", //4
        "        \\ \\  \\ \\\\ \\ \\  \\\\\\  \\ \\  \\\\ \\  \\ \\   ___  \\ \\  \\_|/__   \\ \\    / /      ", //5
        "         \\ \\  \\_\\\\ \\ \\  \\\\\\  \\ \\  \\\\ \\  \\ \\  \\\\ \\  \\ \\  \\_|\\ \\   \\/   / /      ", //6
        "          \\ \\_______\\ \\_______\\ \\__\\\\ \\__\\ \\__\\\\ \\__\\ \\_______\\__/   / /        ", //7
        "           \\|_______|\\|_______|\\|__| \\|__|\\|__| \\|__|\\|_______|\\____/ /         ", //8
        "                                                                \\|__|/          ", //09
        "                                                                                ", //10
        "                  ___  __    ________  ________   ________                      ", //11
        "                 |\\  \\|\\  \\ |\\   __  \\|\\   ___  \\|\\   ____\\                     ", //12
        "                 \\ \\  \\/  /|\\ \\  \\|\\  \\ \\  \\\\ \\  \\ \\  \\___|                     ", //13
        "                  \\ \\   ___  \\ \\  \\\\\\  \\ \\  \\\\ \\  \\ \\  \\  ___                   ", //14
        "                   \\ \\  \\\\ \\  \\ \\  \\\\\\  \\ \\  \\\\ \\  \\ \\  \\|\\  \\                  ", //15
        "                    \\ \\__\\\\ \\__\\ \\_______\\ \\__\\\\ \\__\\ \\_______\\                 ", //16
        "                     \\|__| \\|__|\\|_______|\\|__| \\|__|\\|_______|                 ", //17
        "                                                                                ", //18
        "                      (1) Start a new game                                      ", //19
		"                      (7) Select level                                          ", //20
        "                      (8) Present instructions and keys                         ", //21
        "                      (9) EXIT                                                  ", //22
        "                                                                                ", //23
        "                                                                                ", //24
        "                                                                                "  //25
    };
    const char* selectStagePrompt[GameConfig::MAX_Y] = {
    "                                                                                ", // 1
    "                                                                                ", // 2
    "                                                                                ", // 3
    "         _____       _           _           _                                  ", // 4
    "        / ____|     | |         | |         | |                                 ", // 5
    "        | (___   ___| | ___  ___| |_     ___| |_ __ _  __ _  ___              ", // 6
    "         \\___ \\ / _ \\ |/ _ \\/ __| __|   / __| __/ _` |/ _` |/ _ \\             ", // 7
    "         ____) |  __/ |  __/ (__| |_    \\__ \\ || (_| | (_| |  __/              ", // 8
    "        |_____/ \\___|_|\\___|\\___|\\__|   |___/\\__\\__,_|__, |___|             ", // 9
    "                                                      __/ |                    ", // 10
    "                                                     |___/                     ", // 11
    "                                                                                ", // 12
    "                                                                                ", // 13
    "                                                                                ", // 14
    "                                                                                ", // 15
    "                                                                                ", // 16
    "                                                                                ", // 17
    "                                                                                ", // 18
    "                                                                                ", // 19
    "                                                                                ", // 20
    "                                                                                ", // 21
    "                                                                                ", // 22
    "                                                                                ", // 23
    "                                                                                ", // 24
    "                                                                                "  // 25
    };
    const char* instructionsPage[GameConfig::MAX_Y] =
    {
        "                                                                                ", //1
        "                               GAME INSTRUCTIONS                                ", //2
        "                                                                                ", //3
        "    Welcome to Donkey Kong! Your goal is to help Mario save Pauline.            ", //4
        "                                                                                ", //5
        "    Controls:                                                                   ", //6
        "      - Move Left:    'A' or 'a'                                                ", //7
        "      - Move Right:   'D' or 'd'                                                ", //8
        "      - Move Up:      'W' or 'w'                                                ", //9
        "      - Move Down:    'X' or 'x'                                                ", //10
        "      - Stay:         'S' or 's'                                                ", //11
        "      - Pause/Resume: 'ESC'                                                     ", //12
        "                                                                                ", //13
        "    Rules:                                                                      ", //14
        "      - Avoid barrels thrown by Donkey Kong.                                    ", //15
        "      - Use ladders and jumps to navigate the levels.                           ", //16
        "      - Falling too far or being hit by an explosion will cost you a life.      ", //17
        "      - Rescue Pauline by reaching her at the top of the stage!                 ", //18
        "    score :                                                                     ", //19
        "      - For kill ghost or destroy barrel you got 100 points                     ", //20
        "                                                                                ", //21
        "    Tips:                                                                       ", //22
        "      - Time your jumps carefully to avoid obstacles.                           ", //23
        "      - Plan your moves to avoid getting cornered by barrels.                   ", //24
        "                Press any key to return to the menu.                            "  //25
    };
public:
	void run(const Mode& mode);
private:
    void selectStage(bool isDefault, const Mode& mode) const;
	void startGame(const std::vector<Stage>& stages, const int& selectedStageIndex, const Mode& mode) const;
	void displayMenu() const;
	void showInstructions() const;
	void showSelectStage() const;
};

#endif