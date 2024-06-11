#pragma once
#include "DisplayableObject.h"
#include <functional>
class ClickableObject :
    public DisplayableObject
{

private:
    std::function<void()> onClickBehavior;
public:
    ClickableObject(int xCoord, int yCoord, const char* texturePath, std::function<void()> onClickBehavior);
    ClickableObject(int xCoord, int yCoord, int width, int height, const char* texturePath, std::function<void()> onClickBehavior);
    ClickableObject(int xCoord, int yCoord, int width, const char* texturePath, std::function<void()> onClickBehavior);
    ClickableObject(int xCoord, int yCoord, const char* texturePath, int height, std::function<void()> onClickBehavior);

    bool containsPoint(int pointX, int pointY) {
        if (x_float <= pointX && pointX <= x_float + width &&
            y_float <= pointY && pointY <= y_float + height)
            return true; else return false;
    }

    void OnClick() {
        onClickBehavior();
    }
};

