#include "boworc.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265
void boworc::initArrows(spriteBase *weaponBase)
{
    theArrows.resize(4);
    
    timeDiff=10;
    
    arrowBase=weaponBase;
    for(unsigned int i=0;i<theArrows.size();i++)
    {
        theArrows[i] = NULL;
    }
}
    
void boworc::fireArrow(SDL_Surface *screen, int x, int y, int w, int h, char direction)
{
    if (timeDiff>=40)
    { 
    for(unsigned int i=0; i<theArrows.size(); i++)
    {
        if(theArrows[i] == NULL)
        {     
            theArrows[i] = new sprite;
    	    if(direction == 'E')
            {
    	        theArrows[i]->initSprite(arrowBase, screen, x+(w/2), y+(h/2), 15, 5);
                theArrows[i]->setImage(arrowBase->getImage("right"));
                timeDiff=0;
    	    }
    	    else if(direction == 'W')
    	    {
        		theArrows[i]->initSprite(arrowBase, screen, x+(w/2), y+(h/2), 15, 5);
                theArrows[i]->setImage(arrowBase->getImage("left"));
                timeDiff=0;
    	    }
    	    else if(direction == 'N')
    	    {
        		theArrows[i]->initSprite(arrowBase, screen, x+(w/2), y+(h/2), 5, 15);
                theArrows[i]->setImage(arrowBase->getImage("up"));
                timeDiff=0;
    	    }
    	    else if(direction == 'S')
    	    {
        		theArrows[i]->initSprite(arrowBase, screen, x+(w/2), y+(h/2), 5, 15);
                theArrows[i]->setImage(arrowBase->getImage("down"));
                timeDiff=0;
    	    }
    	    
            theArrows[i]->setDirection(direction);
            
            i=4;
        }
    }
    }

}
