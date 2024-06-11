#include "TileOccupant.h"

TileOccupant::TileOccupant(TileObject* occupiedTile) : 
	PhysicalObject(0, 0),
	occupiedTile(occupiedTile) {}