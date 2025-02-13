#include "Menu.h"
#include "Utils.h"
#include "Stage.h"
#include "StagesManager.h"
#include "ModeManager.h"
using namespace std;

void Menu::run(const Mode& mode) {
	GameConfig::eKeys key = GameConfig::eKeys::STAY;
	bool exitFlag = false;
	
	if (mode.load) {
		selectStage(true, mode);
	}
	else {
		displayMenu();
		while (!exitFlag)
		{
			if (_kbhit()) {
				key = (GameConfig::eKeys)_getch();
				switch (key) {
				case GameConfig::eKeys::START:
					selectStage(true, mode);
					while (!_kbhit()) {} // Wait for the user to press any key
					this->displayMenu(); // Redisplay the menu
					break;
				case GameConfig::eKeys::INST:
					this->showInstructions();
					while (!_kbhit()) {} // Wait for the user to press any key
					this->displayMenu(); // Redisplay the menu
					continue;
				case GameConfig::eKeys::STAGE:
					this->selectStage(false, mode);
					while (!_kbhit()) {} // Wait for the user to press any key
					this->displayMenu(); // Redisplay the menu
					continue;
				case GameConfig::eKeys::EXIT:
					exitFlag = true;
					break;
				default:
					break;
				}
			}
		}
	}
}
void Menu::selectStage(bool isDefault, const Mode& mode) const {
	vector<Stage> stages;
	string selectedStageName;
	int selectedStageIndex;

	if (!StagesManager::getAvailableStages(stages)) {
		cout << "There is no stages available";
		return;
	}
	if (isDefault) {
		selectedStageIndex = 0;
	}
	else {
		system("cls");
		showSelectStage();
		StagesManager::printStages(stages, GameConfig::STAGES_X, GameConfig::STAGES_Y);
		cout << endl << "Enter the selected stage name: ";
		cin >> selectedStageName;

		selectedStageIndex = StagesManager::findStage(stages, selectedStageName);
		if (selectedStageIndex == -1) {
			cout << "Invalid stage name." << endl << "Press any key to get back to the menu...";
			return;
		}
	}
	startGame(stages, selectedStageIndex, mode);
}
void Menu::startGame(const vector<Stage>& stages, const int& selectedStageIndex, const Mode& mode) const {
	Game(stages, selectedStageIndex, mode).run();
}
void Menu::displayMenu() const {
	gotoxy(0, 0);
	for (int i = 0; i < GameConfig::MAX_Y; i++) {
		cout << menuPrompt[i] << endl;
	}
}
void Menu::showInstructions() const {
	gotoxy(0, 0);
	for (int i = 0; i < GameConfig::MAX_Y; i++) {
		cout << instructionsPage[i] << endl;
	}

}
void Menu::showSelectStage() const
{
	gotoxy(0, 0);
	for (int i = 0; i < GameConfig::MAX_Y; i++) {
		cout << selectStagePrompt[i] << endl;
	}

}

