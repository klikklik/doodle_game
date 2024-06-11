#pragma once

#include "PhysicalObject.h"
#include "DestroyableObject.h"
#include "MovingObject.h"
#include "GameManager.h"
#include <vector>

class ProjectileObject : public PhysicalObject, public DestroyableObject, public MovingObject  {
public:
    ProjectileObject();
  
    void construct(int xCoord, int yCoord, float horVel = 0, float vertVel = 0, int lifeTime = 4000);

    virtual ~ProjectileObject();
    void update(int deltaTime);
    void setInitialLifeTime(int milliseconds) { initialLifeTime = milliseconds; lifeTime = milliseconds; }
private:
    template <typename U>
    friend void GameManager::destroyMarked(std::vector<U*>& objectsPtrs, std::vector<U*>& unusedObjectsPtrs);

    void checkAndApplyChangesIfOffScreen();
    void clear() override;
    static std::shared_ptr<Sprite> projectileSprite;
    int lifeTime;
    int initialLifeTime;
};
