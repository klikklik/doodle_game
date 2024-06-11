#pragma once

#include "PhysicalObject.h"
#include "DestroyableObject.h"
#include "TileOccupant.h"
#include "TileObject.h"
#include "GameManager.h"

#include <vector>

class EnemyObject :
    public TileOccupant
{
public:
    EnemyObject();
    void construct(TileObject* occupiedTile, int apperanceType); // used after calling default constructor
    ~EnemyObject();
    void setAppearance(int appearanceType) { appearanceType = appearanceType % 2; }

private:
    
    template <typename U>
    friend void GameManager::destroyMarked(std::vector<U*>& objectsPtrs, std::vector<U*>& unusedObjectsPtrs);
    void clear() override;
    int appearanceType;
    static std::shared_ptr<Sprite> monster0;
    static std::shared_ptr<Sprite> monster1;
};

