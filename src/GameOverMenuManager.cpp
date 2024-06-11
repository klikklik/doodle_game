#include "GameOverMenuManager.h"
#include "GameParameters.h"
#include "PlayerCharacterObject.h"
#include "GameManager.h"


GameOverMenuManager::GameOverMenuManager()
{
	
	auto startGame = []() {
		if (GameParameters::getPlayerCharacter() != nullptr && GameParameters::getGameManager() != nullptr) {
			delete GameParameters::getPlayerCharacter();
			delete GameParameters::getGameManager();
			GameParameters::setPlayerObject(nullptr);
			GameParameters::setGameManager(nullptr);
		}
		GameParameters::setGameState(GameParameters::GameState::Gameplay);
		GameParameters::setPlayerObject(new PlayerCharacterObject(0, GameParameters::getScreenHeight() / 2));
		GameParameters::setGameManager(new GameManager());
	};
	auto goToMenu = []() {
		if (GameParameters::getPlayerCharacter() != nullptr && GameParameters::getGameManager() != nullptr) {
			delete GameParameters::getPlayerCharacter();
			delete GameParameters::getGameManager();
			GameParameters::setPlayerObject(nullptr);
			GameParameters::setGameManager(nullptr);
		}
		GameParameters::setGameState(GameParameters::GameState::Menu);


	};



	clickableMenuContent.emplace_back(new ClickableObject(GameParameters::getScreenWidth() / 7, GameParameters::getScreenHeight() / 2, 2 * GameParameters::getScreenWidth() / 7, "./data/play_again.png", startGame));
	clickableMenuContent.emplace_back(new ClickableObject(4*GameParameters::getScreenWidth() / 7, GameParameters::getScreenHeight() / 2, 2 * GameParameters::getScreenWidth() / 7, "./data/menu.png", goToMenu));
	menuContent.emplace_back(new DisplayableObject(0, GameParameters::getScreenHeight() / 6, "./data/game_over.png", GameParameters::getScreenHeight() / 6));
	menuContent.back()->setX((GameParameters::getScreenWidth() - menuContent.back()->getWidth()) / 2);




}

GameOverMenuManager::~GameOverMenuManager()
{
	for (auto& content : clickableMenuContent) {
		delete content;
	}

	for (auto& content : menuContent) {
		delete content;
	}
}


