#include "cursor.h"

cursor::cursor(SDL_Surface *screen, int x, int y, int w, int h)
{
    visible = true;
    
    mScreen = screen;
    mSpeed = 50;
    setX(x);
    setY(y);
    setW(w);
    setH(h);
    invIndex=0;
}

bool cursor::move(Uint8 *keys, player *thePlayer)
{
    
    //Move the cursor to highlight any available items
    
    if(keys[SDLK_UP])
    {
        setOldY(getY()+mSpeed);

        if((getY() > 70)&&(invIndex-5<=5)&&(thePlayer->returnInventory()[invIndex-5]->getVisible()))
        {
            setY(getY()-mSpeed);
            invIndex-=5;
            return true;
        }
        else
        {//Searches for next available item in inventory that the player has collected
            for (int j=(invIndex/5-1); j>=0; j--)
            {
                for (int i=4; i>=0; i--)
                {
                    if((j*5+i)>0)
                    {
                          if (thePlayer->returnInventory()[(j*5+i)]->getVisible())
                          {
                                setX(88+(i*mSpeed));
                                setY(70+(j*mSpeed));
                                invIndex=(j*5)+i;
                                i=-1;
                                j=-1;
                                return true;
                          }
                    }
                }
            }
        }        
    }
    else if (keys[SDLK_DOWN])
    {
        setOldY(getY()-mSpeed);
        if((getY() < 120)&&(invIndex+5<=5)&&(thePlayer->returnInventory()[invIndex+5]->getVisible()))
        {
            setY(getY()+mSpeed);
            invIndex+=5;
            return true;
        }
        else
        {//Searches for next available item in inventory that the player has collected
            for (int j=(invIndex/5+1); j<=1; j++)
            {
                for (int i=0; i<=4; i++)
                {
                    if((j*5+i)<6)
                    {
                          if (thePlayer->returnInventory()[(j*5+i)]->getVisible())
                          {
                                setX(88+(i*mSpeed));
                                setY(70+(j*mSpeed));
                                invIndex=(j*5)+i;
                                i=6;
                                j=2;
                                return true;
                          }
                    }
                }
            }
        }
    }

    if (keys[SDLK_LEFT])
    {
        setOldX(getX()+mSpeed);
        if((getX() > 88)&&(invIndex-1<=4)&&(thePlayer->returnInventory()[invIndex-1]->getVisible()))
        {
            setX(getX()-mSpeed);
            invIndex-=1;
            return true;
        }
        else
        {//Searches for next available item in inventory that the player has collected
            for (int i=invIndex-1; i>=0; i--)
            {
                if(thePlayer->returnInventory()[i]->getVisible())
                {
                           setX(88+(i*mSpeed));
                           invIndex=i;
                           i=-1;
                           return true;
                }
            }
        }
    }

    else if (keys[SDLK_RIGHT])
    {
        setOldX(getX()-mSpeed);
        if((getX() < 288)&&(invIndex+1<=4)&&(thePlayer->returnInventory()[invIndex+1]->getVisible()))
        {
            setX(getX()+mSpeed);
            invIndex+=1;
            return true;
        }
        else
        {//Searches for next available item in inventory that the player has collected
            for (int i=invIndex+1; i<=4; i++)
            {
                if(thePlayer->returnInventory()[i]->getVisible())
                {
                           setX(88+(i*mSpeed));
                           invIndex=i;
                           i=6;
                           return true;
                }
            }
        }
           
    }
    return false;
}
