#pragma once

#include <SFML/Graphics.hpp>

// Bonus for any found bugs in the framework!


class Window {
public:
    static sf::RenderWindow& getInstance();
};



class Sprite{
public:
    sf::Texture texture;
    sf::Sprite sprite;
};
Sprite* createSprite(const char* path);
void drawSprite(Sprite*, int x, int y);

void getSpriteSize(Sprite* s, int& w, int &h);
void setSpriteSize(Sprite* s, int w, int h);
void destroySprite(Sprite* s);

void drawTestBackground();

void getScreenSize(int& w, int &h);

// Get the number of milliseconds since library initialization.


void showCursor(bool bShow);

enum class FRKey {
	RIGHT,
	LEFT,
	DOWN,
	UP,
	COUNT,
    UNKNOWN
};

enum class FRMouseButton {
	LEFT,
	MIDDLE,
	RIGHT,
	COUNT
};

class Framework {
public:
	


	// no function calls are available here, this function should only return width, height and fullscreen values
	virtual void PreInit(int& width, int& height, bool& fullscreen) = 0;

	// return : true - ok, false - failed, application will exit
	virtual bool Init() = 0;

	virtual void Close() = 0;

	// return value: if true will exit the application
	virtual bool Tick(unsigned int deltaTime) = 0;

	// param: xrel, yrel: The relative motion in the X/Y direction 
	// param: x, y : coordinate, relative to window
	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) = 0;

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) = 0;

	virtual void onKeyPressed(FRKey k) = 0;

	virtual void onKeyReleased(FRKey k) = 0;

	virtual const char* GetTitle() = 0;

	virtual ~Framework() {};
};


int run(Framework*);
