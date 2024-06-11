#pragma once

#include "Framework.h"
#include "GameParameters.h"
#include <memory>
#include<vector>
#include <string>

class DigitSprites
{
	

public:
	std::vector <std::unique_ptr<Sprite, void(*)(Sprite*)>> digits;
	DigitSprites();
	void displayScore(int xCoord = GameParameters::getScreenWidth(), int yCoord = 0);

};
