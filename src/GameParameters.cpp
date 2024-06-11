#include "GameParameters.h"
#include <iostream>
PlayerCharacterObject* GameParameters::playerCharacterObject = nullptr;
GameManager* GameParameters::gameManager = nullptr;


float GameParameters::scale;
float GameParameters::gravity;
int GameParameters::maxYposition;
int GameParameters::screenHeight;
int GameParameters::screenWidth;
bool GameParameters::gameOn;
float GameParameters::initialVerticalVelocity;
float GameParameters::desiredHorizontalVelocity;
GameParameters::GameState GameParameters::gameState = GameParameters::GameState::Menu;


GameParameters::GameParameters(
	int sHeight, int sWidth,float grav, float initVerVel,
	float desHorVel,
	 bool gameIsOn ) 
{
	screenHeight = sHeight;
	screenWidth = sWidth;
	
	//scale = screenWidth / 800.f;
	int jump = (initVerVel * initVerVel) / (2 * grav);
	float scale1 = screenHeight / (3.* jump);
	float scale2 = screenWidth / 800.;
	if (scale2 > scale1) {
		scale = scale1;
		maxYposition = screenHeight / 3;
	}
	else {
		scale = scale2;
		maxYposition = screenHeight / 2;
	}
	scale = scale1 > scale2 ? scale2 : scale1;
	
	gravity = grav * scale;
	gameOn = gameIsOn;
	initialVerticalVelocity = initVerVel * scale;
	desiredHorizontalVelocity = desHorVel * scale;
	
	
}