#pragma once
#include "PhysicalObject.h"
#include "MovingObject.h"
#include "DestroyableObject.h"
#include "TileOccupant.h"

#include "GameManager.h"

#include <vector>

class TileObject : public PhysicalObject , public MovingObject, public DestroyableObject{
public:
	TileObject();// to implement
	//TileObject(int xCoord, int yCoord, float verticalVelocity = 0.f, int oscillationPeriod = 0, TileOccupant * occupant = nullptr);
	virtual ~TileObject();
	void construct(int xCoord, int yCoord, float verticalVelocity = 0.f, int oscillationPeriod = 0, TileOccupant* occupant = nullptr);
	int getOscillationPeriod() const;
	void setOscillationPeriod(int milliseconds);
	void setOccupantAndChangeItsCoords(TileOccupant* tileOccupant);
	void setX(float x_) override;
	void setY(float y_) override;
	void markToDestroy() override;
	void update(int deltaTime);
	void clear() override;
	

private:
	
	//template <typename U>
	//friend void GameManager::destroyMarked(std::vector<U*>& objectsPtrs, std::vector<U*>& unusedObjectsPtrs);

	
	static std::shared_ptr<Sprite> sharedGreenTileSprite;
	int oscillationPeriod;
	float timeLeftToChangeDirection;
	TileOccupant * occupant;
};
