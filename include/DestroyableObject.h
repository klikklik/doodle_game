#pragma once
#include "GameObject.h"
class DestroyableObject : public GameObject
{
public:
	virtual bool shouldBeDestroyed() const;
	virtual void markToDestroy();
	virtual void clear() = 0;
protected:
	DestroyableObject(bool toDestroy = false);
	bool toDestroy;
};

