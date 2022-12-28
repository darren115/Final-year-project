#include "draw.h"
           
void draw::drawSprite(sprite *spriteName, engine *engineName, SDL_Surface *screen)
{
    engineName->Display->drawSurface(spriteName->getImage(), spriteName->getX(), spriteName->getY(), 0, 0, screen);
}
    
void draw::drawSprite(sprite *spriteName, SDL_Surface *curs, engine *engineName, SDL_Surface *screen)
{
    engineName->Display->drawSurface(curs, spriteName->getX(), spriteName->getY(), 0, 0, screen);
}
    
void draw::drawAll(engine *theEngine, SDL_Surface *back, SDL_Surface *screen, player *thePlayer, vector<orc *> badGuys, vector<sprite *> goodGuys, vector<Item *> theObjects, vector<sprite *> screenInfo, vector<sprite *> theDoors, int backX, int backY, int screenWidth, int screenHeight, SFont *fonta, vector<Item *> uItems)
{ 
                  
    theEngine->Display->drawSurface(back, backX, backY, screenWidth, screenHeight, screen);
    
    for(unsigned int i=0; i < theDoors.size(); i++)
    {
        drawSprite(theDoors[i], theEngine, screen);
    }
    
    vector<sprite *>& playerArrows = thePlayer->getWeapon();
    for(unsigned int i=0; i < playerArrows.size(); i++)
    {
        if(playerArrows[i] != NULL)
        {
            drawSprite(playerArrows[i], theEngine, screen);
        }
    }
   
   
    sprite *& playerBoomerang = thePlayer->getBoomerang();
        if(playerBoomerang != NULL)
        {
            drawSprite(playerBoomerang, theEngine, screen);
        }
    
    
    
    for(unsigned int i=0; i < goodGuys.size(); i++)
    {
        if (goodGuys[i]->getVisible())
        {
           drawSprite(goodGuys[i], theEngine, screen);
        }
    }
    
    
    for(unsigned int i=0; i < badGuys.size(); i++)
    {
        drawSprite(badGuys[i], theEngine, screen);
        
        if (badGuys[i]->getEType()==1)
        {    
            vector<sprite *>& enemyArrows = badGuys[i]->getWeapon();
            for(unsigned int i=0; i < enemyArrows.size(); i++)
            {
                if(enemyArrows[i] != NULL)
                {
                    drawSprite(enemyArrows[i], theEngine, screen);
                }
            }
        }
    }
    
    for(unsigned int i=0; i < theObjects.size(); i++)
    {
        if (theObjects[i]->getVisible())
        {
            drawSprite(theObjects[i], theEngine, screen);
        }
    }
        
    
    for(unsigned int i=0; i< screenInfo.size(); i++)
    {
        drawSprite(screenInfo[i], theEngine, screen);
    }

    vector<sprite *>& playersLife = thePlayer->getLifeIcon();
    for(unsigned int i=0; i < thePlayer->getHearts(); i++)
    {
        if(playersLife[i] != NULL)
        {
            drawSprite(playersLife[i], theEngine, screen);
        }
    }
    
    
    
    string msg = fonta->IntToString(thePlayer->getScore());
    int fw = (fonta->getTextWidth(msg))/2;
    fonta->write(screen,msg,380-fw,25);
    
    msg = fonta->IntToString(thePlayer->getArrows());
    fw = (fonta->getTextWidth(msg))/2;
    fonta->write(screen,msg,310-fw,25);
    
    msg = fonta->IntToString(thePlayer->getBombs());
    fw = (fonta->getTextWidth(msg))/2;
    fonta->write(screen,msg,235-fw,25);


    msg = fonta->IntToString(thePlayer->getRupees());
    fw = (fonta->getTextWidth(msg))/2;
    fonta->write(screen,msg,170-fw,25);
    
    vector<Item *> mInv = thePlayer->returnInventory(); 
    
    if (mInv[0] != NULL)
    {
    SDL_Surface *invImage;
    SDL_Rect srcdest;
    for (int i=0; i<6; i++)
    {
        if (mInv[i]->getSelected())
        {
        invImage = thePlayer->getInvImage(i);
        srcdest.x = 92;
        srcdest.y = 14;
        srcdest.w = 32;
        srcdest.h = 32;
        SDL_BlitSurface(invImage, NULL, screen, &srcdest);
        
        }
    }
    }
    
    //Draw collectable items
    for(unsigned int i=0; i < uItems.size(); i++)
    {
        if (uItems[i]->getVisible())
        {
            drawSprite(uItems[i], theEngine, screen);
        }
    }
        
    j = thePlayer->drawMagic();
            
    SDL_Rect srcdest2;
    srcdest2.x = 40;
    srcdest2.y = 15;
    srcdest2.w = 22;
    srcdest2.h = 68;
                
    SDL_BlitSurface(j, NULL, screen, &srcdest2); 
    
    sprite *& playerLamp = thePlayer->getLamp();
    if(playerLamp != NULL)
    {
        drawSprite(playerLamp, theEngine, screen);
    }
    
    drawSprite(thePlayer, theEngine, screen);
    
    SDL_Flip(screen);
    SDL_FreeSurface(j);
}
