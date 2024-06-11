#include "EnemyObject.h"
#include "TileObject.h"
#include "GameParameters.h"
std::shared_ptr<Sprite> EnemyObject::monster0 = nullptr;
std::shared_ptr<Sprite> EnemyObject::monster1 = nullptr;

/*
EnemyObject::EnemyObject(TileObject* occupiedTile, int appearanceType) :
	TileOccupant(occupiedTile), appearanceType(appearanceType%2) 
{
	if (monster0 == nullptr) {
		monster0.reset(createSprite("./data/monster1.png"), destroySprite);
		monster1.reset(createSprite("./data/monster2.png"), destroySprite);

		getSpriteSize(monster0.get(), width, height);
		width *= GameParameters::getScale();
		height *= GameParameters::getScale();
		setSpriteSize(monster0.get(), width, height);
		setSpriteSize(monster1.get(), width, height);

	}
	if (appearanceType % 2 == 0) {
		sprite = monster0;
	}
	else {
		sprite = monster1;
	}
	getSpriteSize(sprite.get(), width, height);
	occupiedTile->setOccupantAndChangeItsCoords(this);
	//x_float = occupiedTile->getX() + ( occupiedTile->getWidth() - width) / 2;  //middle of tile minus half of width
	//y_float = occupiedTile->getY() - height;
	hitboxX = x_float + width / 15;
	hitboxY = y_float + height / 10;

	hitboxWidth = static_cast<int>(width * 13.f/15.f);
	hitboxHeight = height * 0.9f;
}
*/

EnemyObject::EnemyObject() :
	TileOccupant(nullptr), appearanceType(0)
{

	if (monster0 == nullptr) {
		monster0.reset(createSprite("./data/monster1.png"), destroySprite);
		monster1.reset(createSprite("./data/monster2.png"), destroySprite);

		getSpriteSize(monster0.get(), width, height);
		width *= GameParameters::getScale();
		height *= GameParameters::getScale();
		setSpriteSize(monster0.get(), width, height);
		setSpriteSize(monster1.get(), width, height);

	}

	sprite = monster0;
	
	getSpriteSize(sprite.get(), width, height);

	hitboxX = x_float + width / 15;
	hitboxY = y_float + height / 10;

	hitboxWidth = static_cast<int>(width * 13.f / 15.f);
	hitboxHeight = height * 0.9f;
}



void EnemyObject::construct(TileObject* occupiedTile, int appearanceType) {
	this->occupiedTile = occupiedTile;
	this->appearanceType = appearanceType % 2;
	if (appearanceType % 2 == 0) {
		sprite = monster0;
	}
	else {
		sprite = monster1;
	}
	getSpriteSize(sprite.get(), width, height);
	occupiedTile->setOccupantAndChangeItsCoords(this);
	hitboxX = x_float + width / 15;
	hitboxY = y_float + height / 10;

	hitboxWidth = static_cast<int>(width * 13.f / 15.f);
	hitboxHeight = height * 0.9f;
}

void EnemyObject::clear() {

	toDestroy = false;
	if (occupiedTile != nullptr) {
		occupiedTile->setOccupantAndChangeItsCoords(nullptr);
	}
	setTile(nullptr);
}



EnemyObject::~EnemyObject()
{
	
}

