#include "DestroyableObject.h"
#include <iostream>


DestroyableObject::DestroyableObject(bool toDestroy)
	: toDestroy(toDestroy)
{
}

bool DestroyableObject::shouldBeDestroyed() const
{
	return toDestroy;
}

void DestroyableObject::markToDestroy()
{
	toDestroy = true;
	
}

