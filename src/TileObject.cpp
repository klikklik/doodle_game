#include "TileObject.h"
#include "EnemyObject.h"
#include "GameParameters.h"
#include <iostream>
std::shared_ptr<Sprite> TileObject::sharedGreenTileSprite = nullptr;


/*
TileObject::TileObject(int xCoord, int yCoord, float verticalVelocity, int oscillationPeriod, TileOccupant* occupant )
	: PhysicalObject(xCoord, yCoord) , MovingObject(0,verticalVelocity), oscillationPeriod(oscillationPeriod) , timeLeftToChangeDirection(oscillationPeriod/2), occupant(occupant)
{
	
	if (sharedGreenTileSprite == nullptr) {
		sharedGreenTileSprite.reset(createSprite("./data/tile_green.png"), destroySprite);
		getSpriteSize(sharedGreenTileSprite.get(), width, height);
		width *= GameParameters::getScale();
		height *= GameParameters::getScale();
		setSpriteSize(sharedGreenTileSprite.get(), width, height);
	}
	
	
	sprite = sharedGreenTileSprite;
	getSpriteSize(sprite.get(), width, height);
	
	hitboxX = x_float + width / 20;
	hitboxY = y_float + height / 10;
	
	hitboxWidth = static_cast<int>(width * 0.9f);
	hitboxHeight = height / 2;
	
}
*/

TileObject::TileObject()
	: PhysicalObject(0, 0), MovingObject(0, 0), oscillationPeriod(0), timeLeftToChangeDirection(0), occupant(nullptr)
{

	if (sharedGreenTileSprite == nullptr) {
		sharedGreenTileSprite.reset(createSprite("./data/tile_green.png"), destroySprite);
		getSpriteSize(sharedGreenTileSprite.get(), width, height);
		width *= GameParameters::getScale();
		height *= GameParameters::getScale();
		setSpriteSize(sharedGreenTileSprite.get(), width, height);
	}


	sprite = sharedGreenTileSprite;
	getSpriteSize(sprite.get(), width, height);

	hitboxX = x_float + width / 20;
	hitboxY = y_float + height / 10;

	hitboxWidth = static_cast<int>(width * 0.9f);
	hitboxHeight = height / 2;

}

void TileObject::construct(int xCoord, int yCoord, float verticalVelocity, int oscillationPeriod, TileOccupant* occupant) {
	this->setX(xCoord);
	this->setY(yCoord);
	this->setVerticalVelocity(verticalVelocity);
	this->setOscillationPeriod(oscillationPeriod);
	this->setOccupantAndChangeItsCoords(occupant);
}



int TileObject::getOscillationPeriod() const {
	return oscillationPeriod;
}
void TileObject::setOscillationPeriod(int milliseconds) {
	oscillationPeriod = milliseconds;
	timeLeftToChangeDirection = oscillationPeriod / 2;
}
void TileObject::setOccupantAndChangeItsCoords(TileOccupant* tileOccupant) {
	
	this->occupant = tileOccupant;						//place new enemy
	if (this->occupant != nullptr) {					//if it is actually placed an enemy then connect this tile to enemy

		//coordinates of enemy depends of coordinates of tile
		//need to be changed
		this->occupant->setX((2 * this->getX() + this->getWidth() - this->occupant->getWidth()) / 2); //the same as in the enemy constructor
		this->occupant->setY(this->getY() - this->occupant->getHeight());
	
	}

}
void TileObject::setX(float x_) {
	if (occupant != nullptr) {
		float relative_x = this->x_float - occupant->getX();
		occupant->setX(x_ - relative_x);
	}
	PhysicalObject::setX(x_);
}
void TileObject::setY(float y_) {
	
	if (occupant != nullptr) {
		occupant->setY(y_ - occupant->getHeight());
	}
	PhysicalObject::setY(y_);
}

void TileObject::clear() {
	toDestroy = false;
	if (occupant != nullptr) {
		occupant->setTile(nullptr);
	}
	setOccupantAndChangeItsCoords(nullptr);
}

void TileObject::update(int deltaTime) {

	this->move(0,this->verticalVelocity * deltaTime);
	this->timeLeftToChangeDirection -= deltaTime;
	if (this->timeLeftToChangeDirection <= 0) {
		
		this->timeLeftToChangeDirection = this->oscillationPeriod;
		this->verticalVelocity *= -1;
	}
	if (this->getY() > 2 * GameParameters::getScreenHeight())
		this->markToDestroy();
	
}

void TileObject::markToDestroy() {
	toDestroy = true;
	if (this->occupant != nullptr) {
		this->occupant->markToDestroy();
	}
}


TileObject::~TileObject()
{
}
