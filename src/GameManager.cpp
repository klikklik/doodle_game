#include "GameManager.h"
#include "TileObject.h"
#include "EnemyObject.h"
#include "SpringBootsObject.h"
#include "ProjectileObject.h"
#include "GameParameters.h"
#include "PlayerCharacterObject.h"
#include "ClickableObject.h"

#include <random>
#include <iostream>

GameManager::GameManager(): liftablePtr(nullptr){
	
	
	tilesPtrs.emplace_back(new TileObject());
	
	int tileHeight = tilesPtrs.front()->getHeight();
	
	tilesPtrs.back()->construct(0, GameParameters::getScreenHeight() - 2 * tileHeight);
	
	
	while (tilesPtrs.back()->getY() >= -tileHeight) {
		
		generateNextRandomTile(tilesPtrs.back(),false);
	}
	
	
}

GameManager:: ~GameManager() {
	


	for (auto& tile : tilesPtrs) {
		delete tile;
	}

	for (auto& enemy : enemiesPtrs) {
		delete enemy;
	}

	for (auto& tile : unusedTilesPtrs) {
		delete tile;
	}
	for (auto& enemy : unusedEnemiesPtrs) {
		delete enemy;
	}

	for (auto& projectile : projectilesPtrs) {
		delete projectile;
	}

	for (auto& projectile : unusedProjectilesPtrs) {
		delete projectile;
	}
	/*
	for (auto& displayable : displayablesPtrs) {
		delete displayable;
	}
	for (auto& clickable : clickablesPtrs) {
		delete clickable;
	}
	*/
	
}

void GameManager:: generateNextRandomTile( TileObject* nextTilePredecessor, bool allowEnemies) {
	
	
	TileObject* nextTile = generateDefaultObject<TileObject>(tilesPtrs,unusedTilesPtrs);
	TileOccupant* nextTileOccupant = nullptr;
	float nextTileVerticalVelocity = 0;
	int nextTileOscillationPeriod = 0;

	float initialVerticalVelocity = GameParameters::getInitialVerticalVelocity();
	float desiredHorizontalVelocity = GameParameters::getDesiredHorizontalVelocity();

	int tileWidth = nextTilePredecessor->getWidth();

	float gravity = GameParameters::getGravity();
	int jumpHeight = initialVerticalVelocity * initialVerticalVelocity / (2 * gravity);
	int maxSide = -initialVerticalVelocity * desiredHorizontalVelocity / gravity ;
	

	int previousTile_x = nextTilePredecessor->getX();
	int previousTile_y = nextTilePredecessor->getY();
	
	std::random_device rd;
	std::mt19937 gen = std::mt19937(rd());

	std::uniform_int_distribution<int> disX(0, 2 * maxSide);
	int x = disX(gen);
	
	if (gen() % 9 == 0 && nextTilePredecessor->getOscillationPeriod() == 0) {
		std::uniform_int_distribution<int> disV(5, 10);
		std::uniform_int_distribution<int> disS(jumpHeight/2, jumpHeight);

		nextTileVerticalVelocity = - disV(gen)/50.f * initialVerticalVelocity;
		nextTileOscillationPeriod = disS(gen) / nextTileVerticalVelocity;
		
	}
	float timeElapsedSincePeak = (x - maxSide) / desiredHorizontalVelocity;
	
	int maxUp = x > maxSide ? std::abs(jumpHeight - timeElapsedSincePeak * timeElapsedSincePeak * gravity / 2) : jumpHeight;
	
	std::uniform_int_distribution<int> disY(0, maxUp);

	int y = previousTile_y - disY(gen);
	
	if (gen() % 2 == 0) {
			
		x = previousTile_x + tileWidth + x; //tile should be reachable jumping to right
	}
	else {
		x = previousTile_x - tileWidth  - x; //tile should be reachable jumping to left
		
	}
	
	if (x < 0) {
		if (x + tileWidth < 0) {
			x += GameParameters::getScreenWidth();
		}
		else x = 0;
	}

	if (x > GameParameters::getScreenWidth() - tileWidth) {
		if (x > GameParameters::getScreenWidth()) {
			x -= GameParameters::getScreenWidth();
		}
		else x = GameParameters::getScreenWidth() - tileWidth;
	}


	

	if (allowEnemies && gen() % 11== 0) {
		
		EnemyObject* newEnemy = generateDefaultObject<EnemyObject>(enemiesPtrs, unusedEnemiesPtrs);
		
		newEnemy->construct(nextTile, gen());
		
		nextTileOccupant = newEnemy;
		

	}
	
	else if (liftablePtr == nullptr && gen() % 99 == 0) {
		SpringBootsObject* newSpringBoots = new SpringBootsObject(nextTile, 20000);

		nextTileOccupant = newSpringBoots;
		liftablePtr = newSpringBoots;
	}
	
	nextTile->construct(x, y, nextTileVerticalVelocity, nextTileOscillationPeriod, nextTileOccupant);

	return;

}

void GameManager::destroyMarked() {
	destroyMarked(tilesPtrs, unusedTilesPtrs);
	destroyMarked(enemiesPtrs, unusedEnemiesPtrs);
	destroyMarked(projectilesPtrs, unusedProjectilesPtrs);
	if (liftablePtr != nullptr && liftablePtr->shouldBeDestroyed()) {
		liftablePtr->clear();
		delete liftablePtr;
		liftablePtr = nullptr;
	}
}

void GameManager::displayAll()
{
	for (const auto& tile : tilesPtrs) {
		tile->display();
	}
	for (const auto& enemy : enemiesPtrs) {

		enemy->display();
	}

	GameParameters::getPlayerCharacter()->display();

	for (const auto& projectile : projectilesPtrs) {
		projectile->display();
	}

	GameParameters::getPlayerCharacter()->displayHearts();

	if (liftablePtr != nullptr)
		liftablePtr->display();

	if (GameParameters::getPlayerCharacter()->getActiveAbility() != nullptr)
		GameParameters::getPlayerCharacter()->getActiveAbility()->display();
	/*
	for (const auto& clickable : clickablesPtrs) {
		clickable->display();
	}
	for (const auto& diplayable : displayablesPtrs) {
		diplayable->display();
	}
	*/

}

void GameManager::createProjectile(int aimX, int aimY, int xCoord, int yCoord, int lifeTime)
{
	int deltaX = aimX - xCoord;
	int deltaY = aimY - yCoord;
	float velocityMagnitude = sqrt(deltaX * deltaX + deltaY * deltaY);
	if (velocityMagnitude < 0.1) return;
	ProjectileObject* newProjectile = generateDefaultObject<ProjectileObject>(projectilesPtrs, unusedProjectilesPtrs);

	newProjectile->construct(xCoord, yCoord,
		1.5f * GameParameters::getScale() * deltaX / velocityMagnitude,
		1.5f * GameParameters::getScale() * deltaY / velocityMagnitude,
		lifeTime);
	

}