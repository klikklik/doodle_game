#pragma once

#include "Framework.h"
#include "GameObject.h"
#include <memory>

class DisplayableObject : public GameObject{
public:
	DisplayableObject(int xCoord, int yCoord, const char* texturePath);
	DisplayableObject(int xCoord, int yCoord, int width, int height, const char* texturePath);
	DisplayableObject(int xCoord, int yCoord, int width, const char* texturePath);
	DisplayableObject(int xCoord, int yCoord, const char* texturePath, int height);
	virtual ~DisplayableObject();
	virtual void setX(float x_);
	virtual void setY(float y_);
	virtual float getX() const;
	virtual float getY() const;
	virtual void move(float xDirection, float yDirection);
	virtual int getWidth() const;
	virtual int getHeight() const;
	virtual void display() const;
	virtual void display(int x, int y) const;

protected:

	DisplayableObject(int xCoord, int yCoord);
	std::shared_ptr<Sprite> sprite;
	
	float x_float;
	float y_float;
	int width;
	int height;
};


