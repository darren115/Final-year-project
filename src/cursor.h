#ifndef CURSOR_H
#define CURSOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include "sprite.h"
#include "player.h"

using std::vector;
using std::string;

///class extending sprite to represent the player
class cursor : public sprite
{
public:
    
    ///constructor
    cursor(SDL_Surface *, int, int, int, int);
    
    ///moves the cursor
    bool move(Uint8 *keys, player *thePlayer);
    
    
    ///returns the current index of the item below the cursor
    int getIndex()
    {
        return invIndex;
    }
        
protected:
    
    ///cursor's speed
    int mSpeed;
    
    int invIndex;
    
};
#endif //CURSOR_H

