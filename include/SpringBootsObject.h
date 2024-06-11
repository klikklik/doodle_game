#pragma once

#include "AbilityItemObject.h"

class GameManager;

class SpringBootsObject :
    public AbilityItemObject
{
public:
    SpringBootsObject(TileObject* occupiedTile, int duration);
    void actOnPlayerCharacter() override;

private:
    //friend void GameManager::destroyMarked();
    static std::shared_ptr<Sprite> springBootsRight;
    static std::shared_ptr<Sprite> springBootsLeft;
    void clear() override;
};


