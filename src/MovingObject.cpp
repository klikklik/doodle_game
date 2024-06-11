#include "MovingObject.h"

MovingObject::MovingObject(float horizontalVelocity, float verticalVelocity)
    : GameObject(), horizontalVelocity(horizontalVelocity), verticalVelocity(verticalVelocity)
{
}

void MovingObject::setHorizontalVelocity(float horizontalVelocity)
{
    this->horizontalVelocity = horizontalVelocity;
}

float MovingObject::getHorizontalVelocity() const
{
    return horizontalVelocity;
}

void MovingObject::setVerticalVelocity(float verticalVelocity)
{
    this->verticalVelocity = verticalVelocity;
}

float MovingObject::getVerticalVelocity() const
{
    return verticalVelocity;
}
