#pragma once
#include "GameObject.h"
#include "PhysicalObject.h"
#include "DestroyableObject.h"

class TileObject;


class TileOccupant :
    public PhysicalObject, public DestroyableObject
   
{
public:
    TileOccupant(TileObject* occupiedTile );
    void setTile(TileObject* tile) { occupiedTile = tile; }
    TileObject* getTile() { return occupiedTile; }


protected:
    TileObject* occupiedTile;

};

