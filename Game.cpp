#include "Game.h"
#include <conio.h>
#include "Utils.h"
#include "GameConfig.h"
#include <windows.h>
#include <iostream>
#include "StagesManager.h"
#include "ModeManager.h"

using namespace std;

Game::Game(const std::vector<Stage>& _stages, const int& initStageIndex, const Mode& _mode) :
	currentStageIndex(initStageIndex),
	stages(_stages),
	modeManager(_mode, getCurrStageName()),
	gameBoard(this, _stages[initStageIndex].getStageBoard(), &modeManager) {
}

void Game::run() {
	while (isStageOn() && checkSilentTest(false)) {
		initiateGame();
		runGameCycle();
		handleGameFinished();
	}
	checkSilentTest(true);
}
bool Game::isStageCleard() const {
	return gameBoard.isMarioReachedPauline();
}
void Game::initiateGame() {
	ShowConsoleCursor(false);
	modeManager.resetModeManager(getCurrStageName());
	gameBoard.spawnGhosts();
	gameBoard.resetBoard();
}
bool Game::isStageOn() const {
	return gameBoard.isMarioAlive() && !gameBoard.isMarioReachedPauline();
}
void Game::runBoardPrePace() {
	gameBoard.displayData();
	gameBoard.handleBarrelsPrePace();
	gameBoard.handleMarioPrePace();
	gameBoard.handleGhostPrePace();
}
void Game::paceControl() {
	if (!modeManager.getSilent())
		Sleep(100);
	modeManager.tick();
}
void Game::runBoardPostPace() {
	gameBoard.handleMarioPostPace();
	gameBoard.handleBarrelsPostPace();
	gameBoard.handleGhostPostPace();
	gameBoard.setMarioAttack(false);
}
void Game::pause(Point crdData) {
	GameConfig::eKeys key = GameConfig::eKeys::STAY;
	size_t len = strlen(GameConfig::PAUSE_MSG);

	Point crdMessage = Point(crdData.x + GameConfig::MAX_LIVES_STRING_LEN + 2, crdData.y);

	gotop(crdMessage);
	cout << GameConfig::PAUSE_MSG;

	while (key != GameConfig::eKeys::ESC)
	{
		if (_kbhit()) {
			key = (GameConfig::eKeys)_getch();
		}
	}

	gotop(crdMessage);
	for (size_t i = 0; i < len; i++) {
		cout << " ";
	}
}
std::string Game::getCurrStageName() {
	return stages[currentStageIndex].getStageName();
}
void Game::gameOver() {
	if (!modeManager.getSilent()) {
		system("cls");
		gotoxy(0, 0);
		for (int i = 0; i < GameConfig::MAX_Y; i++) {
			cout << gameOverScreen[i] << endl;
		}
		gotoxy(0, 0);
	}
}
void Game::runGameCycle() {
	while (isStageOn() && (!modeManager.getSilent() || modeManager.getTest())) {
		runBoardPrePace();
		paceControl();
		runBoardPostPace();
	}
}
void Game::handleStageCleared() {
	modeManager.stageCleared();

	if (currentStageIndex == stages.size() - 1) {
		showWinnerScreen();
	}
	else {
		const GameConfig::StageBoard& nextStageBoard = getNextStageBoard();
		showStageClearedScreen();
		gameBoard.setNewStage(nextStageBoard);
	}
}
void Game::showStageClearedScreen() {
	if (!modeManager.getLoad()) {
		system("cls");
		gotoxy(0, 0);
		for (int i = 0; i < GameConfig::MAX_Y; i++) {
			cout << stageClearedScreen[i] << endl;
		}
		gotoxy(0, 0);
		while (!_kbhit()) {} // Wait for the user to press any key
	}
}
void Game::showWinnerScreen() {
	if (!modeManager.getSilent()) {
		system("cls");
		gotoxy(0, 0);
		for (int i = 0; i < GameConfig::MAX_Y; i++) {
			cout << winnerScreen[i] << endl;
		}
		gotoxy(0, 0);

		while (!_kbhit()) {} // Wait for the user to press any key
	}
}
void Game::handleGameFinished() {
	if (!isStageCleard()) {
		gameOver();
	}
	else
		handleStageCleared();
}
bool Game::checkSilentTest(bool finished) {
	if (!modeManager.getSilent())
		return true;
	gotoxy(0, 0);
	if (!modeManager.getTest()) {
		cout << "Test Failed.";
		gotoxy(0, 2);
		return false;
	}
	if (finished) {
		cout << "Test Passed.";
		gotoxy(0, 2);
		return true;
	}
	return true;
}
const GameConfig::StageBoard& Game::getNextStageBoard() {
	currentStageIndex++;
	return stages[currentStageIndex].getStageBoard();
}