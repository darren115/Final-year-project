#include "cursor.h"

cursor::cursor(spriteBase *inBase, SDL_Surface *screen, int x, int y, int w, int h)
{
    base = inBase;
    visible = true;
    
    mTile = 1;
    spriteImage = base->getImage(1);
    mScreen = screen;
    mSpeed = 32;
    setX(x);
    setY(y);
    setW(w);
    setH(h);
    setColW((int)(getW()*0.80));
    setColH((int)(getH()*0.80));
    setColXOffset((getW()-getColW())/2);
    setColYOffset((getH()-getColH())/2);
}

void cursor::move(Uint8 *keys, int &backX, int &mapX, int &xOffset, int &backY, int &mapY, int &yOffset, int screenWidth, int screenHeight, int levelWidth, int levelHeight)
{
    
    //If the sprite has been moved of screen by a badguy then reset posistion to the edge
    //of the screen.
    if(getX() < 0)
    {
        setX(0);
    }
    else if(getX() >= (screenWidth-getW()))
    {
       setX((screenWidth)-getW());
    }
    else if(getY() < 0)
    {
        setY(0);
    }
    else if(getY() >= (screenHeight-getH()))
    {
        setY(screenHeight-getH());
    }

    if(keys[SDLK_UP])
    {
        setOldY(getY()+mSpeed);

        if(getY() >= 0+(screenHeight/3))
        {
            setY(getY()-mSpeed);
        }
        else if(mapY >= 0)
        {
            setY(getY()-mSpeed);
        }
        else
        {
            yOffset=backY;
            backY=backY+mSpeed;
            mapY=mapY+mSpeed;
            yOffset=backY-yOffset;
        }
        
        
    }
    else if (keys[SDLK_DOWN])
    {
        setOldY(getY()-mSpeed);
        if(getY() <= (screenHeight-(screenHeight/3)))
        {
            setY(getY()+mSpeed);

        }
        else if(mapY <= (screenHeight-levelHeight))
        {
            setY(getY()+mSpeed);
        }
        else
        {
            yOffset=backY;
            backY=backY-mSpeed;
            mapY=mapY-mSpeed;
            yOffset=backY-yOffset;
        }
        
    }

    if (keys[SDLK_LEFT])
    {
        setOldX(getX()+mSpeed);
        if(getX() >= (0+(screenWidth/3)))
        {
            setX(getX()-mSpeed);
        }
        else if(mapX >= 0)
        {
            setX(getX()-mSpeed);
        }
        else
        {
            xOffset=backX;
            backX=backX+mSpeed;
            mapX=mapX+mSpeed;
            xOffset=backX-xOffset;
        }
        
        
    }

    else if (keys[SDLK_RIGHT])
    {
        setOldX(getX()-mSpeed);
        if(getX() <= (screenWidth-(screenWidth/3)))
        {
            setX(getX()+mSpeed);
        }
        else if(mapX <= (screenWidth-levelWidth))
        {
            setX(getX()+mSpeed);
        }
        else
        {
            xOffset=backX;
            backX=backX-mSpeed;
            mapX=mapX-mSpeed;
            xOffset=backX-xOffset;
        }
           
    }
    
}

void cursor::updateTileImage()
{
     setImage(base->getImage(mTile));
}
