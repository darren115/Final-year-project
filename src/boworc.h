#ifndef BOWORC_H
#define BOWORC_H

#include "sprite.h"
#include <stdlib.h>
#include <vector>

using std::vector;

///Class to represent an orc/enemy with a bow.  
class boworc
{
public:
    
    void initArrows(spriteBase *weaponBase);
    
    ///fires an arrow
    void fireArrow(SDL_Surface *screen, int x, int y, int w, int h, char direction);
    
    ///returns theArrows
    vector<sprite *>& getArrows()
    {
        return theArrows;
    }
    
    //sets the time since the last arrow was fired
    void setTimeDiff(int time)
    {
         timeDiff=time;
    }
    
    //returns the time since the last arrow was fired
    int getTimeDiff()
    {
         return timeDiff;
    }

private:
    
    ///Enemies's arrows
    vector<sprite *> theArrows;
    
    ///spriteBase for the arrows 
    spriteBase *arrowBase;
    
    //Integer to indicate how long it has been since the last arrow was fired
    int timeDiff;
        
};
#endif //BOWORC_H
