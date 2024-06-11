#pragma once
#include "DisplayableObject.h"



class PhysicalObject : public DisplayableObject {
protected:
	PhysicalObject(int xCoord, int yCoord, const char* texturePath);
	PhysicalObject(int xCoord, int yCoord, int width, int height, const char* texturePath);
	PhysicalObject(int xCoord, int yCoord);
	virtual ~PhysicalObject();
	int hitboxWidth;
	int hitboxHeight;
	int hitboxX;
	int hitboxY;
public:
	int getHitboxWidth() const;
	int getHitboxHeight() const;
	int getHitboxX() const;
	int getHitboxY() const;
	void setX(float x_) override;
	void setY(float y_) override;
	bool checkCollision(const PhysicalObject* other, bool feet = false);


};


