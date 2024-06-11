#include "PlayerCharacterObject.h"
#include "GameManager.h"
#include "TileObject.h"
#include "EnemyObject.h"
#include "GameParameters.h"
#include "AbilityItemObject.h"

#include <cmath>


std::shared_ptr<Sprite> PlayerCharacterObject::playerLeftSprite = nullptr;
std::shared_ptr<Sprite> PlayerCharacterObject::playerRightSprite = nullptr;

PlayerCharacterObject::PlayerCharacterObject(int xCoord, int yCoord, int lifeCount, int immunityDuration)
	: PhysicalObject(xCoord, yCoord),
	MovingObject(0, initialVerticalVelocity* GameParameters::getScale()),
	lifeCount(lifeCount), immunityTimeLeft(immunityDuration), immunityDuration(immunityDuration),
	initialVerticalVelocity(GameParameters::getInitialVerticalVelocity()),
	desiredHorizontalVelocity(GameParameters::getDesiredHorizontalVelocity()),
	traveledDistance(0),
	activeAbility(nullptr),
	activeBoostTimeLeft ( 0 ),
	score(0)
{
	if (playerLeftSprite == nullptr) {
		playerLeftSprite.reset(createSprite("./data/char_blue_left.png"), destroySprite);
		playerRightSprite.reset(createSprite("./data/char_blue_right.png"), destroySprite);
		getSpriteSize(playerLeftSprite.get(), width, height);
		width *= GameParameters::getScale();
		height *= GameParameters::getScale();
		setSpriteSize(playerLeftSprite.get(), width, height);
		setSpriteSize(playerRightSprite.get(), width, height);
	}
	
	sprite = playerRightSprite;
	getSpriteSize(sprite.get(), width, height);
	hitboxWidth = hitboxX = width / 3;
	hitboxY = y_float + round(height / 3.f);
	hitboxHeight = round(2.f * height / 3.f);
	
	redHeart = new DisplayableObject(0, 0, GameParameters::getScreenWidth() / 15, GameParameters::getScreenWidth() / 15, "./data/heart_red.png");
	blackHeart = new DisplayableObject(0, 0, GameParameters::getScreenWidth() / 15, GameParameters::getScreenWidth() / 15,"./data/heart_black.png");
}

PlayerCharacterObject::~PlayerCharacterObject()
{
	
}

void PlayerCharacterObject::goDirection(FRKey direction)
{
	if (direction == FRKey::LEFT) {
		sprite = playerLeftSprite;
		if (activeAbility != nullptr) {
			activeAbility->loadLeftSprite();
		}
		horizontalVelocity = -desiredHorizontalVelocity;
	}
	if (direction == FRKey::RIGHT) {
		sprite = playerRightSprite;
		if (activeAbility != nullptr) {
			activeAbility->loadRightSprite();
		}
		horizontalVelocity = desiredHorizontalVelocity;
	}



	/*
	if (direction == FRKey::LEFT) {
		if (horizontalVelocity >= 0) {	//going right
			sprite = playerLeftSprite;
			horizontalVelocity = -0.3f; //= -sideacceleration;
			return;
		}
		
		horizontalVelocity -= 0.3f;
		if (horizontalVelocity < -desiredHorizontalVelocity){  // + acceleration
			horizontalVelocity = -desiredHorizontalVelocity;
		}
			
	}
	if (direction == FRKey::RIGHT) {
		if (horizontalVelocity <= 0) {
			sprite = playerRightSprite;
			horizontalVelocity = 0.3f; //= -sideacceleration;
			return;
		}
		horizontalVelocity += 0.3f;
		if (horizontalVelocity > desiredHorizontalVelocity) {  // + acceleration
			horizontalVelocity = desiredHorizontalVelocity;
		}
	}
	*/
}
void PlayerCharacterObject::stopSideMovement(FRKey k)
{
	if(k == FRKey::LEFT xor horizontalVelocity > 0 ) 
	horizontalVelocity = 0.f;
	
}


void PlayerCharacterObject::update(int deltaTime) {

	verticalVelocity += GameParameters::getGravity() * deltaTime;
	immunityTimeLeft = immunityTimeLeft < deltaTime ? 0 : immunityTimeLeft - deltaTime;
	this->move(horizontalVelocity * deltaTime , verticalVelocity * deltaTime );

	traveledDistance += -verticalVelocity / GameParameters::getScale() * deltaTime;
	if (traveledDistance > score) {
		score = traveledDistance;
	}
	this->checkAndApplyChangesIfOffScreen();
	if (activeAbility == nullptr) {
		return;
	}
	activeBoostTimeLeft -= deltaTime;
	if (activeBoostTimeLeft <= 0) {
		turnOffAbility();
	}

}

int PlayerCharacterObject::getImmunityTimeLeft() {
	return immunityTimeLeft;
}

float PlayerCharacterObject::getDesiredHorizontalVelocity() {
	return desiredHorizontalVelocity;
}
float PlayerCharacterObject::getInitialVerticalVelocity() {
	return initialVerticalVelocity;
}	


void PlayerCharacterObject::respawn() {
	for (const auto& tile : GameParameters::getGameManager()->tilesPtrs) {			//respawn on the lowest standing platform
		if (tile->getY() < GameParameters::getScreenHeight() && tile->getVerticalVelocity() < 0.001f) {   // epsilon = 0.001
			this->setX(tile->getX());
			this->setY(tile->getY() - this->getHeight());
			break;
		}
	}
}

void PlayerCharacterObject::handleDeath() {
	if (activeAbility != nullptr)
	turnOffAbility();
	if (immunityTimeLeft > 0) {
		respawn();
		return;
	}

	lifeCount--;
	if (lifeCount > 0) {
		respawn();
		immunityTimeLeft = immunityDuration;
		return;
	}
	GameParameters::setGameState(GameParameters::GameState::GameOver);

	
}

void PlayerCharacterObject::checkAndApplyChangesIfOffScreen() {

	if (this->getX() < -this->getWidth() / 2) {
		this->setX(GameParameters::getScreenWidth() - this->getWidth() / 2);	//passed the left border
	}
	if (this->getX() > GameParameters::getScreenWidth() - this->getWidth() / 2) {		//passed the right border
		this->setX(-this->getWidth() / 2);
	}


	if (this->getY() >= GameParameters::getScreenHeight()) {		//is on the bottom?
		
		handleDeath();
		
	}
	
}

void PlayerCharacterObject::display() const {


	if (immunityTimeLeft / 100 % 2 == 0) {
		DisplayableObject::display();
	}
}
void PlayerCharacterObject::displayHearts( ) {
	for (int i = 0; i < lifeCount; i++) {
		redHeart->display(GameParameters::getScreenWidth() / 3 + i * redHeart->getWidth(), 0);
	}
	for (int i = lifeCount; i < 5; i++) {
		blackHeart->display(GameParameters::getScreenWidth() / 3 + i * blackHeart->getWidth(), 0);
	}
}

void PlayerCharacterObject::turnOffAbility() {
	activeAbility->markToDestroy();
	activeAbility = nullptr;
	initialVerticalVelocity = GameParameters::getInitialVerticalVelocity();
}

void PlayerCharacterObject::setX(float x_) {
	if (activeAbility != nullptr) {
		activeAbility->setX(x_ + activeAbility->getOffsetX());
	}
	PhysicalObject::setX(x_);

}
void PlayerCharacterObject::setY(float y_) {
	if (activeAbility != nullptr) {
		activeAbility->setY(y_ + activeAbility->getOffsetY());
	}
	PhysicalObject::setY(y_);
}