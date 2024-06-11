#include "DisplayableObject.h"

#include "GameParameters.h"
#include <iostream>
DisplayableObject::DisplayableObject(int xCoord, int yCoord, const char* texturePath)
	: x_float(static_cast<float>(xCoord)), y_float(static_cast<float>(yCoord))
{
	sprite.reset(createSprite(texturePath), destroySprite);
	getSpriteSize(sprite.get(), width, height);

	width *= GameParameters::getScale();

	height *= GameParameters::getScale();
	setSpriteSize(sprite.get(), width, height);

}

DisplayableObject::DisplayableObject(int xCoord, int yCoord, int width, int height, const char* texturePath)
	: x_float(static_cast<float>(xCoord)), y_float(static_cast<float>(yCoord)), width(width), height(height)
{
	sprite.reset(createSprite(texturePath), destroySprite);
	setSpriteSize(sprite.get(), width, height);
}

DisplayableObject::DisplayableObject(int xCoord, int yCoord, int width, const char* texturePath) : x_float(static_cast<float>(xCoord)), y_float(static_cast<float>(yCoord)), width(width)
{
	sprite.reset(createSprite(texturePath), destroySprite);
	int textureWidth, textureHeight;
	getSpriteSize(sprite.get(), textureWidth, textureHeight);
	float scale = static_cast<float>(width) / textureWidth;
	height = textureHeight * scale;
	setSpriteSize(sprite.get(), width, height);

}

DisplayableObject::DisplayableObject(int xCoord, int yCoord, const char* texturePath , int height) : x_float(static_cast<float>(xCoord)), y_float(static_cast<float>(yCoord)), height(height)
{
	sprite.reset(createSprite(texturePath), destroySprite);
	int textureWidth, textureHeight;
	getSpriteSize(sprite.get(), textureWidth, textureHeight);
	float scale = static_cast<float>(height) / textureHeight;
	width = textureWidth * scale;
	setSpriteSize(sprite.get(), width, height);


}

DisplayableObject::~DisplayableObject()
{
	
}

void DisplayableObject::setX(float x_)
{
	x_float = x_;
}

void DisplayableObject::setY(float y_)
{
	y_float = y_;
}

float DisplayableObject::getX() const
{
	return x_float;
}

float DisplayableObject::getY() const
{
	return y_float;
}

void DisplayableObject::move(float xDirection, float yDirection) {
	this->setX(x_float + xDirection);
	this->setY(y_float + yDirection);
}


//Sprite* DisplayableObject::getSprite() const
//{
//	return sprite;
//}

int DisplayableObject::getWidth() const
{
	return width;
}

int DisplayableObject::getHeight() const
{
	return height;
}

void DisplayableObject::display() const
{
	if (sprite != nullptr) {
		drawSprite(sprite.get(), static_cast<int>(x_float), static_cast<float>(y_float));
	}
}


void DisplayableObject::display(int x, int y) const {
	if (sprite != nullptr) {
		drawSprite(sprite.get(), x, y);
	}
}

DisplayableObject::DisplayableObject(int xCoord, int yCoord)
	: x_float(static_cast<float>(xCoord)), y_float(static_cast<float>(yCoord)), sprite(nullptr), height(0), width(0)
{
}
