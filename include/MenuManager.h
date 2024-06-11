#pragma once

#include <vector>

#include "DisplayableObject.h"
#include "ClickableObject.h"
class MainMenuManager
{
public:
	MainMenuManager();
	std::vector<DisplayableObject*> menuContent;
	std::vector<ClickableObject*> clickableMenuContent;

private:


};

