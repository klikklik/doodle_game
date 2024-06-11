#include "ProjectileObject.h"
#include "GameParameters.h"
std::shared_ptr<Sprite> ProjectileObject::projectileSprite = nullptr;


/*
ProjectileObject::ProjectileObject(int xCoord, int yCoord, float horVel, float vertVel, int lifeTime)
    : PhysicalObject(xCoord, yCoord), MovingObject(horVel, verticalVelocity), lifeTime(lifeTime) , initialLifeTime(lifeTime)
{
    if (projectileSprite == nullptr) {
        projectileSprite.reset(createSprite("./data/projectile.png"), destroySprite);
        
        getSpriteSize(projectileSprite.get(), width, height);
        width *= GameParameters::getScale();
        height *= GameParameters::getScale();
        setSpriteSize(projectileSprite.get(), width, height);
       
    }
    sprite = projectileSprite;
    getSpriteSize(sprite.get(), width, height);

    // Set the hitbox dimensions (if different from the projectile's dimensions)
    hitboxWidth = width;
    hitboxHeight = height;
    hitboxX = x_float;
    hitboxY = y_float;
}
*/

ProjectileObject::ProjectileObject()
    : PhysicalObject(0, 0), MovingObject(0, 0), lifeTime(4000), initialLifeTime(4000)
{
    if (projectileSprite == nullptr) {
        projectileSprite.reset(createSprite("./data/projectile.png"), destroySprite);

        getSpriteSize(projectileSprite.get(), width, height);
        width *= GameParameters::getScale();
        height *= GameParameters::getScale();
        setSpriteSize(projectileSprite.get(), width, height);

    }
    sprite = projectileSprite;
    getSpriteSize(sprite.get(), width, height);

    hitboxWidth = width;
    hitboxHeight = height;
    hitboxX = x_float;
    hitboxY = y_float;
}


void ProjectileObject::construct(int xCoord, int yCoord, float horVel, float vertVel, int lifeTime) {
    this->setX(xCoord);
    this->setY(yCoord);
    this->horizontalVelocity = horVel;
    this->verticalVelocity = vertVel;
    this->lifeTime = lifeTime;
}

void ProjectileObject::update(int deltaTime)
{
    // Update the projectile's position based on its velocity
    this->move(horizontalVelocity * deltaTime, verticalVelocity * deltaTime);
    lifeTime -= deltaTime;
    if (lifeTime <= 0) {
        markToDestroy();
    }
    checkAndApplyChangesIfOffScreen();
    
}





void ProjectileObject::checkAndApplyChangesIfOffScreen()
{
    // Check if the projectile is off-screen based on the game's screen dimensions
    // Adjust the conditions according to your specific game
    if (y_float < 0 || y_float > GameParameters::getScreenHeight()) {
        this->markToDestroy();
    }else if (x_float < 0 ) {
        this->setX(GameParameters::getScreenWidth() );
    }
    else if (x_float > GameParameters::getScreenWidth()) {
        this->setX(0);
    }
    
}
void ProjectileObject::clear() {
    toDestroy = false;
    lifeTime = initialLifeTime;
}

ProjectileObject:: ~ProjectileObject() {
   
}