#include "DigitSprites.h"

#include "PlayerCharacterObject.h"


DigitSprites::DigitSprites()
{
    for (int i = 0; i < 10; i++) {
        
        std::string filename = "./data/digit" + std::to_string(i) + ".png";
        digits.push_back(std::unique_ptr<Sprite, void(*)(Sprite*)> (createSprite(filename.c_str()), destroySprite));
    }


}

void DigitSprites::displayScore(int xCoord,int yCoord)
{
    int score = GameParameters::getPlayerCharacter()->getScore();
    int sc = score;
    int w = 0;
    int h = 0;
    int x = xCoord;
    int y = yCoord;
    int sco;
    while (sc != 0) {
        sco = sc - (sc / 10) * 10;
        getSpriteSize(digits[sco].get(), w, h);
        x -= w;
        drawSprite(digits[sco].get(), x, 0);
        sc /= 10;
    
    }



}

