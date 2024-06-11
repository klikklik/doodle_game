

#include <iostream>


#include "Framework.h"
#include "GameParameters.h"
#include "DisplayableObject.h"
#include "PhysicalObject.h"
#include "PlayerCharacterObject.h"
#include "EnemyObject.h"
#include "TileObject.h"
#include "GameManager.h"
#include "MainMenuManager.h"
#include "GameOverMenuManager.h"
#include "ProjectileObject.h"
#include "AbilityItemObject.h"
#include "DigitSprites.h"
#include "FPSCalculator.h"
#include <random>
#include <vector>
#include <cstdlib>






/* Test Framework realization */
class MyFramework : public Framework {

public:
	MyFramework(int screenWidth, int screenHeight) {
		GameParameters gameParameters = GameParameters(screenHeight, screenWidth, 0.005f, -1.8f, 0.55f);
	}

	struct Point {
		int x;
		int y;
	};

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = GameParameters::getScreenWidth();
		height = GameParameters::getScreenHeight();


		fullscreen = false;
	}

	virtual bool Init() {

		int screenWidth, screenHeight;
		getScreenSize(screenWidth, screenHeight);

		background = new DisplayableObject(0, 0, screenWidth, screenHeight, "./data/bck.png");


		mainMenuManager = new MainMenuManager();
		gameOverMenuManager = new GameOverMenuManager();
		ds = new DigitSprites();

		fpsCalculator = new FPSCalculator();

		cursorLocation = new Point();

		return true;
	}




	virtual void Close() {
		delete cursorLocation;
		delete background;
		delete mainMenuManager;
		delete gameOverMenuManager;
		delete fpsCalculator;
		delete ds;
		if (GameParameters::getGameManager() != nullptr)
			delete  GameParameters::getGameManager();
		if (GameParameters::getPlayerCharacter() != nullptr)
			delete  GameParameters::getPlayerCharacter();




	}

	virtual bool Tick(unsigned int deltaTime) {


		background->display();
		fpsCalculator->calculateFPS(deltaTime);


		switch (GameParameters::getGameState()) {
		case GameParameters::GameState::Menu:
			handleMenu();
			break;

		case GameParameters::GameState::Gameplay:
			handleGameplay(deltaTime);
			break;

		case GameParameters::GameState::GameOver:
			handleGameOver();
			break;
		}


		return false;


	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {

		cursorLocation->x = x;
		cursorLocation->y = y;
	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {

		if (button != FRMouseButton::LEFT || isReleased)
			return;
		switch (GameParameters::getGameState()) {
		case GameParameters::GameState::Menu:
		{
			for (const auto& content : mainMenuManager->clickableMenuContent) {
				if (content->containsPoint(cursorLocation->x, cursorLocation->y)) {
					content->OnClick();
				}
			}

			break;
		}
		case GameParameters::GameState::Gameplay:
		{
			GameParameters::getGameManager()->createProjectile(cursorLocation->x, cursorLocation->y);
			break;
		}
		case GameParameters::GameState::GameOver:
		{
			for (const auto& content : gameOverMenuManager->clickableMenuContent) {
				if (content->containsPoint(cursorLocation->x, cursorLocation->y)) {
					content->OnClick();
				}
			}


			break;
		}


		}


	}

	virtual void onKeyPressed(FRKey k) {
		switch (GameParameters::getGameState()) {
		case GameParameters::GameState::Gameplay:
			GameParameters::getPlayerCharacter()->goDirection(k);
			break;
		}


	}


	virtual void onKeyReleased(FRKey k) {
		switch (GameParameters::getGameState()) {
		case GameParameters::GameState::Gameplay:
			if (k == FRKey::LEFT || k == FRKey::RIGHT)
				GameParameters::getPlayerCharacter()->stopSideMovement(k);
			break;
		}


	}

	virtual const char* GetTitle() override
	{
		return "DoodleJump";
	}


private:

	MainMenuManager* mainMenuManager;
	GameOverMenuManager* gameOverMenuManager;
	DisplayableObject* background;
	DigitSprites* ds;

	FPSCalculator* fpsCalculator;
	Point* cursorLocation;
	void handleMenu();
	void handleGameplay(int deltaTime);
	void handleGameOver();

};

int main(int argc, char* argv[])
{

	int screenWidth = 600; // default screen width
	int screenHeight = 800; // default screen height

	if (argc >= 3) {
		screenWidth = std::atoi(argv[1]);
		screenHeight = std::atoi(argv[2]);
	}




	return run(new MyFramework(screenWidth, screenHeight));

}

void MyFramework::handleGameplay(int deltaTime) {
	GameParameters::getPlayerCharacter()->update(deltaTime);

	// check if the player has passed a certain point on the screen

	if (GameParameters::getPlayerCharacter()->getY() < GameParameters::getMaxYPosition()) {

		// update the positions of other elements so they move in the opposite direction
		GameParameters::getPlayerCharacter()->setY(GameParameters::getMaxYPosition());

		for (auto& tile : GameParameters::getGameManager()->tilesPtrs) {
			tile->move(0, -GameParameters::getPlayerCharacter()->getVerticalVelocity() * deltaTime);

		}
		for (auto& projectile : GameParameters::getGameManager()->projectilesPtrs) {
			projectile->move(0, -GameParameters::getPlayerCharacter()->getVerticalVelocity() * deltaTime);
		}
	}


	for (auto& tile : GameParameters::getGameManager()->tilesPtrs) {
		tile->update(deltaTime);
	}

	while (GameParameters::getGameManager()->tilesPtrs.back()->getY() >= -GameParameters::getGameManager()->tilesPtrs.front()->getHeight()) {			//generate if there are not enough on the screen
		GameParameters::getGameManager()->generateNextRandomTile(GameParameters::getGameManager()->tilesPtrs.back());
	}


	for (auto& projectile : GameParameters::getGameManager()->projectilesPtrs) {
		projectile->update(deltaTime);
	}


	// check for collisions between player and platforms
	if (GameParameters::getPlayerCharacter()->getVerticalVelocity() > 0) {
		for (auto& tile : GameParameters::getGameManager()->tilesPtrs) {
			if (GameParameters::getPlayerCharacter()->checkCollision(tile, true)) {

				GameParameters::getPlayerCharacter()->setVerticalVelocity(GameParameters::getPlayerCharacter()->getInitialVerticalVelocity());
			}
		}
	}

	// check for collisions between player and enemies

	for (auto& enemy : GameParameters::getGameManager()->enemiesPtrs) {

		if (GameParameters::getPlayerCharacter()->checkCollision(enemy, true) && GameParameters::getPlayerCharacter()->getVerticalVelocity() > 0) {
			GameParameters::getPlayerCharacter()->setVerticalVelocity(GameParameters::getPlayerCharacter()->getInitialVerticalVelocity());
			enemy->markToDestroy();
		}
		else if (GameParameters::getPlayerCharacter()->checkCollision(enemy) && GameParameters::getPlayerCharacter()->getImmunityTimeLeft() == 0) {
			GameParameters::getPlayerCharacter()->handleDeath();
		}
	}

	//check for collision between projectiles and enemies

	for (auto& projectile : GameParameters::getGameManager()->projectilesPtrs) {
		for (auto& enemy : GameParameters::getGameManager()->enemiesPtrs) {
			if (projectile->checkCollision(enemy)) {
				enemy->markToDestroy();
				projectile->markToDestroy();
			}
		}
	}

	//check if picked up some items

	if (GameParameters::getGameManager()->liftablePtr != nullptr && GameParameters::getPlayerCharacter()->checkCollision(GameParameters::getGameManager()->liftablePtr)) {
		GameParameters::getGameManager()->liftablePtr->actOnPlayerCharacter();

		GameParameters::getGameManager()->liftablePtr = nullptr;
	}

	//delete objects marked to destroy

	GameParameters::getGameManager()->destroyMarked();

	//diplay current state of gameplay

	GameParameters::getGameManager()->displayAll();


	ds->displayScore();

}

void MyFramework::handleMenu() {


	for (const auto& content : mainMenuManager->menuContent) {

		content->display();
	}


	for (const auto& content : mainMenuManager->clickableMenuContent) {

		content->display();
	}


}

void MyFramework::handleGameOver() {

	for (const auto& content : gameOverMenuManager->menuContent) {

		content->display();
	}

	for (const auto& content : gameOverMenuManager->clickableMenuContent) {

		content->display();
	}

	ds->displayScore();

}