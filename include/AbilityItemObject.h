#pragma once
#include "TileOccupant.h"
#include "GameParameters.h"
#include <vector>
class PlayerCharacterObject;

class AbilityItemObject :
    public TileOccupant
{
public:
    int getOffsetX() { return offsetXrelativeToPlayer;}
    int getOffsetY() { return offsetYrelativeToPlayer; }
    virtual void actOnPlayerCharacter() {}
    void loadLeftSprite() { sprite = LeftSprite; }
    void loadRightSprite() { sprite = RightSprite; }
protected:
    AbilityItemObject(TileObject* tile, int duration);
    
    
    int duration;
    int offsetXrelativeToPlayer;
    int offsetYrelativeToPlayer;
    std::shared_ptr<Sprite> LeftSprite;
    std::shared_ptr<Sprite> RightSprite;
};

