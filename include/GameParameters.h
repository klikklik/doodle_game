#pragma once

#include <iostream>

class PlayerCharacterObject;
class GameManager;
class ProjectilesManager;


class GameParameters
{
public:
    GameParameters(
    int sHeight, int sWidth, float gravity, float initialVerticalVelocity,
    float desiredHorizontalVelocity, bool gameOn = true);

    // Getter methods for each parameter

    static float getScale() { return scale; }
    static int getMaxYPosition() { return maxYposition; }
    static int getScreenHeight() { return screenHeight; }
    static int getScreenWidth() {return screenWidth; }
    static float getGravity() { return gravity; }
    static float getInitialVerticalVelocity() { return initialVerticalVelocity; }
    static float getDesiredHorizontalVelocity() { return desiredHorizontalVelocity; }
    static PlayerCharacterObject* getPlayerCharacter() { return playerCharacterObject; }
    static void setPlayerObject(PlayerCharacterObject* playCharObj) {playerCharacterObject = playCharObj;}
    static GameManager* getGameManager() { return gameManager; }
    static void setGameManager(GameManager* gameMan) { gameManager = gameMan; }

    enum class GameState {
        Menu,
        Gameplay,
        GameOver
    };
    static void setGameState(GameState state) { gameState = state; }
    static GameState getGameState() { return gameState; }
    
private:

    static GameState gameState;
    static float scale;
    static float initialVerticalVelocity;
    static float desiredHorizontalVelocity;

    static int maxYposition;
    static int screenHeight;
    static int screenWidth;
    static bool gameOn;
    static float gravity;
    static PlayerCharacterObject* playerCharacterObject;
    static GameManager* gameManager;
 
};
