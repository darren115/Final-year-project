#ifndef CURSOR_H
#define CURSOR_H

#include <stdio.h>
#include <stdlib.h>
#include "sprite.h"
#include <vector>
#include <string>
#include <SDL/SDL.h>

using std::vector;
using std::string;

///class extending sprite to represent the player
class cursor : public sprite
{
public:
    
    ///constructor
    cursor(spriteBase *, SDL_Surface *, int, int, int, int);
    
    ///sets mSpeed
    void setSpeed(int speed)
    {
        mSpeed = speed;
    }
    
    ///moves the cursor
    void move(Uint8 *keys, int &backX, int &mapX, int &xOffset, int &backY, int &mapY, int &yOffset, int screenWidth, int screenHeight, int levelWidth, int levelHeight);
    
    ///updates the tile image
    void updateTileImage();
    
    ///sets mDeathTime
    void setDeathTime(int time)
    {
        mDeathTime = time;
    }
    
    ///returns mDeathTime
    int getDeathTime()
    {
        return mDeathTime;
    }
        
protected:
    
    ///cursor's speed
    int mSpeed;
    
    ///cursor's deathtime
    int mDeathTime;
    
};
#endif //CURSOR_H
