#pragma once

#include <vector>
#include "GameParameters.h"
#include "PlayerCharacterObject.h"


#include <iostream>
class TileObject;
class EnemyObject;
class ProjectileObject;
class ClickableObject;

class GameManager
{
private:
	template<typename T>
	T* generateDefaultObject(std::vector<T*>& objectsPtrs , std::vector<T*>& unusedObjectsPtrs);


	std::vector<TileObject*> unusedTilesPtrs;
	std::vector<EnemyObject*> unusedEnemiesPtrs;
	std::vector<ProjectileObject*> unusedProjectilesPtrs;
public:
	GameManager();
	virtual ~GameManager();
	void generateNextRandomTile(TileObject* nextTilePredecessor, bool allowEnemies = true);
	void createProjectile(int aimX, int aimY, int xCoord = GameParameters::getPlayerCharacter()->getX() + GameParameters::getPlayerCharacter()->getWidth() / 2, int yCoord = GameParameters::getPlayerCharacter()->getHitboxY(), int lifeTime = 4000);
    template<typename T>
    void destroyMarked(std::vector<T*>&objectsPtrs, std::vector<T*>&unusedObjectsPtrs);
    void destroyMarked();
	void displayAll();
	
	std::vector<TileObject*> tilesPtrs;
	std::vector<EnemyObject*> enemiesPtrs;
	std::vector<ProjectileObject*> projectilesPtrs;
	//std::vector<DisplayableObject*> displayablesPtrs;
	//std::vector<ClickableObject*> clickablesPtrs;
	AbilityItemObject* liftablePtr;
};

template<typename T>
T* GameManager::generateDefaultObject(std::vector<T*>& objectsPtrs, std::vector<T*>& unusedObjectsPtrs) {
	
	T* newObject = nullptr;
	
	if (!unusedObjectsPtrs.empty()) {
		newObject = unusedObjectsPtrs.front();
		unusedObjectsPtrs.erase(unusedObjectsPtrs.begin());
	}
	else {
		newObject = new T();
	}
	objectsPtrs.push_back(newObject);

	return newObject;
}

template<typename T>
void GameManager::destroyMarked(std::vector<T*>& objectsPtrs, std::vector<T*>& unusedObjectsPtrs) {
	for (auto it = objectsPtrs.begin(); it != objectsPtrs.end(); ) {
		auto& object = *it;
		if (object->shouldBeDestroyed()) {
			object->clear();
			unusedObjectsPtrs.push_back(object);  // move the tile to the back of unusedTiles
			it = objectsPtrs.erase(it);  // erase the tile from tilesPtrs
		}
		else {
			++it;
		}
	}
}
