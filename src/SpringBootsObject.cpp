#include "SpringBootsObject.h"
#include "GameParameters.h"
#include "TileObject.h"
#include <cmath>
std::shared_ptr<Sprite> SpringBootsObject::springBootsRight = nullptr;
std::shared_ptr<Sprite> SpringBootsObject::springBootsLeft = nullptr;




SpringBootsObject::SpringBootsObject(TileObject* occupiedTile, int duration) : AbilityItemObject(occupiedTile, duration) {

	if (springBootsRight == nullptr) {
		springBootsRight.reset(createSprite("./data/spring_boots_right.png"), destroySprite);
		springBootsLeft.reset(createSprite("./data/spring_boots_left.png"), destroySprite);

		getSpriteSize(springBootsRight.get(), width, height);
		width *= GameParameters::getScale();
		height *= GameParameters::getScale();
		setSpriteSize(springBootsRight.get(), width, height);
		setSpriteSize(springBootsLeft.get(), width, height);

	}
	LeftSprite = springBootsLeft;
	RightSprite = springBootsRight;

	sprite = springBootsRight;

	getSpriteSize(sprite.get(), width, height);
	occupiedTile->setOccupantAndChangeItsCoords(this);
	hitboxX = x_float;
	hitboxY = y_float;
	hitboxWidth = width;
	hitboxHeight = height;

	offsetXrelativeToPlayer = 29. / 124. * GameParameters::getPlayerCharacter()->getWidth();
	offsetYrelativeToPlayer = 13. / 15. * GameParameters::getPlayerCharacter()->getHeight();
}


void SpringBootsObject::clear() {

	toDestroy = false;
	if (occupiedTile != nullptr) {
		occupiedTile->setOccupantAndChangeItsCoords(nullptr);
	}
	setTile(nullptr);
}

void SpringBootsObject::actOnPlayerCharacter() {
	if (occupiedTile != nullptr) {
		occupiedTile->setOccupantAndChangeItsCoords(nullptr);
	}
	this->occupiedTile = nullptr;
	GameParameters::getPlayerCharacter()->setInitialVerticalVelocity(sqrt(2.5) * GameParameters::getInitialVerticalVelocity());
	GameParameters::getPlayerCharacter()->setActiveAbility(this,duration);
}