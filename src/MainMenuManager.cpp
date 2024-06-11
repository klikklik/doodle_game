#include "MainMenuManager.h"
#include "GameParameters.h"
#include "PlayerCharacterObject.h"
#include "GameManager.h"



MainMenuManager::MainMenuManager() {
	
	


	auto startGame = []() {
		if (GameParameters::getPlayerCharacter() != nullptr && GameParameters::getGameManager() != nullptr) {
			delete GameParameters::getPlayerCharacter();
			delete GameParameters::getGameManager();
			GameParameters::setPlayerObject(nullptr);
			GameParameters::setGameManager(nullptr);
		}
		GameParameters::setGameState(GameParameters::GameState::Gameplay); 
		GameParameters::setPlayerObject(new PlayerCharacterObject(0, GameParameters::getScreenHeight()/2));
		GameParameters::setGameManager(new GameManager());
	};
	clickableMenuContent.emplace_back(new ClickableObject(GameParameters::getScreenWidth() / 4, GameParameters::getScreenHeight() / 2, GameParameters::getScreenWidth() / 2,  "./data/play.png",startGame));
	menuContent.emplace_back(new DisplayableObject(0, GameParameters::getScreenHeight() / 6, "./data/doodle_jump.png", GameParameters::getScreenHeight() / 12));
	menuContent.back()->setX((GameParameters::getScreenWidth() - menuContent.back()->getWidth()) / 2);


}

MainMenuManager::~MainMenuManager() {
	for (auto& content : clickableMenuContent) {
		delete content;
	}

	for (auto& content : menuContent) {
		delete content;
	}


}