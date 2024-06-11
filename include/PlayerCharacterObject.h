#pragma once
#include "PhysicalObject.h"
#include "MovingObject.h"
#include "DigitSprites.h"

class AbilityItemObject;

class PlayerCharacterObject : public PhysicalObject , public MovingObject {
public:
	PlayerCharacterObject(int xCoord, int yCoord, int lifeCount = 5, int immunityDuration = 2000);
	virtual ~PlayerCharacterObject();
	void goDirection(FRKey direction);
	void stopSideMovement(FRKey k);
	void respawn();
	void handleDeath();
	void update(int deltaTime);
	void display() const override;
	int getImmunityTimeLeft();
	int getScore() { return score; }
	float getDesiredHorizontalVelocity();
	float getInitialVerticalVelocity();
	AbilityItemObject* getActiveAbility() { return activeAbility;}
	void setActiveAbility(AbilityItemObject* ability, int duration) { activeAbility = ability; activeBoostTimeLeft = duration; }
	void setInitialVerticalVelocity(float initVertVel) { initialVerticalVelocity = initVertVel; }
	void setX(float x_) override;
	void setY(float y_) override;
	//void setAbility(*AbilityItemObject ability) {}
	void displayHearts();
	void displayScore();

private:
	void turnOffAbility();
	void checkAndApplyChangesIfOffScreen();
	float initialVerticalVelocity;
	float desiredHorizontalVelocity;
	//float sideAcceleration;
	//int maxYposition;
	int immunityDuration;
	int immunityTimeLeft;
	float traveledDistance;
	int score;
	int lifeCount;
	int activeBoostTimeLeft;
	AbilityItemObject* activeAbility;
	DisplayableObject* redHeart;
	DisplayableObject* blackHeart;
	static std::shared_ptr<Sprite> playerLeftSprite;
	static std::shared_ptr<Sprite> playerRightSprite;
};
