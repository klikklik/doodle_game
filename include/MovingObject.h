#pragma once
#include "GameObject.h"

class MovingObject : public GameObject
{
public:
    MovingObject(float horizontalVelocity, float verticalVelocity);
    void setHorizontalVelocity(float horizontalVelocity);
    float getHorizontalVelocity() const;
    void setVerticalVelocity(float verticalVelocity);
    float getVerticalVelocity() const;

protected:
    float horizontalVelocity;
    float verticalVelocity;
};

