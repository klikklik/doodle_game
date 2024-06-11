#pragma once
#include <iostream>

class FPSCalculator
{
public:
	FPSCalculator() : timeOfCalculationLeft(1000),FPS(0),createdFramesSinceLastTimeStamp(0){ }
	int calculateFPS(int deltaTime) {  
		createdFramesSinceLastTimeStamp++;
		timeOfCalculationLeft -= deltaTime;
		if (timeOfCalculationLeft <= 0) {
			FPS = createdFramesSinceLastTimeStamp;
			createdFramesSinceLastTimeStamp = 0;
			timeOfCalculationLeft = 1000;

		}
		return FPS;
	}
private :
	int timeOfCalculationLeft;
	int FPS;
	int createdFramesSinceLastTimeStamp;
};

