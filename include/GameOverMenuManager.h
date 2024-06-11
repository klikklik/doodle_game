#pragma once

#include <vector>

#include "DisplayableObject.h"
#include "ClickableObject.h"
class GameOverMenuManager
{
public:
	GameOverMenuManager();
	~GameOverMenuManager();
	std::vector<DisplayableObject*> menuContent;
	std::vector<ClickableObject*> clickableMenuContent;


};

