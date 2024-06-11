#include "PhysicalObject.h"



PhysicalObject::PhysicalObject(int xCoord, int yCoord, const char* texturePath)
	: DisplayableObject(xCoord, yCoord,texturePath),hitboxX(xCoord),hitboxY(yCoord),hitboxWidth(width),hitboxHeight(height)
{
	
}

PhysicalObject::PhysicalObject(int xCoord, int yCoord, int width, int height, const char* texturePath)
	: DisplayableObject(xCoord, yCoord, width, height, texturePath),hitboxX(xCoord), hitboxY(yCoord), hitboxWidth(width), hitboxHeight(height)
{
}

PhysicalObject::PhysicalObject(int xCoord, int yCoord)
	: DisplayableObject(xCoord, yCoord),hitboxX(xCoord),hitboxY(yCoord),hitboxWidth(width), hitboxHeight(height)
{
}

PhysicalObject::~PhysicalObject()
{
	
}

int PhysicalObject::getHitboxWidth() const
{
	return hitboxWidth;
}

int PhysicalObject::getHitboxHeight() const
{
	return hitboxHeight;
}

int PhysicalObject::getHitboxX() const
{
	return hitboxX;
}

int PhysicalObject::getHitboxY() const
{
	return hitboxY;
}

void PhysicalObject::setX(float x_)
{
	int diff = hitboxX - static_cast<int>(x_float);
	x_float = x_;
	hitboxX = static_cast<int>(x_float) + diff;
	
}

void PhysicalObject::setY(float y_)
{
	int diff = hitboxY - static_cast<int>(y_float);
	y_float = y_;
	hitboxY = static_cast<int>(y_float) + diff;
}

bool PhysicalObject::checkCollision(const PhysicalObject* other, bool feet)
{
	int feetFactor = 0;
	if (feet) {
		feetFactor = hitboxHeight;
	}
	if (hitboxX < other->getHitboxX() + other->getHitboxWidth() &&
		hitboxX + hitboxWidth > other->getHitboxX() &&
		hitboxY + feetFactor < other->getHitboxY() + other->getHitboxHeight() &&
		hitboxY + hitboxHeight > other->getHitboxY()) {
		return true;  // Collision detected
	}
	return false;  // No collision
}
