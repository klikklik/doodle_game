#include "ClickableObject.h"



ClickableObject::ClickableObject(int xCoord, int yCoord, const char* texturePath , std::function<void()> onClickBehavior) : DisplayableObject( xCoord, yCoord,texturePath) , onClickBehavior(std::move(onClickBehavior)) {
}

ClickableObject::ClickableObject(int xCoord, int yCoord, int width, int height, const char* texturePath, std::function<void()> onClickBehavior) : DisplayableObject(xCoord, yCoord, width, height, texturePath ), onClickBehavior(std::move(onClickBehavior)) {
}

ClickableObject::ClickableObject(int xCoord, int yCoord, int width, const char* texturePath, std::function<void()> onClickBehavior) :DisplayableObject(xCoord, yCoord, width, texturePath), onClickBehavior(std::move(onClickBehavior))
{
}

ClickableObject::ClickableObject(int xCoord, int yCoord, const char* texturePath, int height, std::function<void()> onClickBehavior): DisplayableObject(xCoord, yCoord, texturePath ,height), onClickBehavior(std::move(onClickBehavior))
{
}
