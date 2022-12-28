#include "player.h"
#include "math.h"



player::player(vector<spriteBase *> inBase, SDL_Surface *screen, int x, int y, int w, int h, spriteBase *weaponBase, spriteBase *boomBase)
{
    //Default starting values for the player      
    
    for(int i=0; i<inBase.size(); i++)              
            theBases.push_back(inBase[i]);
            
    base = theBases[2];
    mLife = 3;
    tHearts = 3;
    arrowBase = weaponBase;
    boomerangBase = boomBase;
    frame = 0;
    progress=0;
    rupees=0;
    mbombs=0;
    mMagic=0;
    marrows=0;
    visible = true;
    hPieces=0;
    slashTime=0;
    boomHeld=1;
    theSlashes=NULL;
    theBoomerang=NULL;
    sframe=0;
    lastWeapon=3;
    slashing = false;
    colHearts.resize(4);
    for(unsigned int i=0;i<colHearts.size();i++)
    {
        colHearts[i] = 0;
    }
    
    
    //Variables for controlling heart locations in HUD
    yLoc=20;
    unsigned int life=0;
    row = 0;
    location = 0;
    
    theArrows.resize(4);
    
    for(unsigned int i=0;i<theArrows.size();i++)
    {
        theArrows[i] = NULL;
    }
    
    //Draws full and empty hearts and also handles new lines for large numbers of hearts
    playerLife.resize(tHearts);
    for(;row<=tHearts/8;row++)
    {  
                              
        location =0;
        for(unsigned int i=0;i<8;i++)
        {            
                     if(life<mLife)
                     {
                     playerLife[life] = new sprite;
	                 playerLife[life]->initSprite("data/images/items/life2.png", screen, 435+(i*25), yLoc, w, h);
	                 life++;
	                 location+=1;
                     }
                     else if ((life>=mLife) && (life <tHearts))
                     {
                     playerLife[life] = new sprite;
	                 playerLife[life]->initSprite("data/images/items/life4.png", screen, 435+(i*25), yLoc, w, h);
	                 life++;	          
	                 location+=1;     
                     }   
                     if (location>7)
                     {
                     yLoc+=15;
                     location =0;
                     }
        }
    }
    
    spriteImage = base->getImage2(8);
    mBackReplacement = SDL_DisplayFormat(spriteImage);
    updateBgReplacement(screen);
    mScreen = screen;
    mSpeed = 2;
    
    setX(x);
    setY(y);
    setW(w);
    setH(h);
    setColW((int)(getW()*0.80));
    setColH((int)(getH()*0.80));
    setColXOffset((getW()-getColW())/2);
    setColYOffset((getH()-getColH())/2);
}




void player::initLifeIcon(int life, SDL_Surface *screen, int w, int h)
{

      playerLife[life] = new sprite;
      playerLife[life]->initSprite("data/images/items/life4.png", screen, 435+(location*25), yLoc, w, h);
      if(location<7)
      location+=1;
      else
      {
          location=0;
          yLoc+=15;
      }
}

void player::setLifeIcon(int life)
{
     if (life>=0)
     {
        for(unsigned int i=0;i<life;i++)
        {
             playerLife[i]->setImage("data/images/items/life2.png");
        }
        for(unsigned int j=life;j<tHearts;j++)
        {
             playerLife[j]->setImage("data/images/items/life4.png");
        }
     }
}


void player::move(Uint8 *keys, int &backX, int &mapX, int &xOffset, int &backY, int &mapY, int &yOffset, int screenWidth, int screenHeight, int levelWidth, int levelHeight, int tileWidth, int tileHeight, vector< vector <int> > &theMap)
{
     if (theBases[0] !=NULL)
     
     base = theBases[lastWeapon];
     
     //Prevents player from moving
     if (lampUse == true)
     {
     }   
     //Plays the sword slashing animation
     else if (slashing == true)
     {
        base=theBases[1];
        lastWeapon=3;
        
        if (this->getDirection()=='N')
        {
           if(sframe < 6)
           {
                setImage(base->getImage2(sframe/2));
                sframe++;
           }
           else if (sframe >= 6 && sframe < 8)
           {
                if (sframe == 6)
                {
                setX(getX()-4);
                setY(getY()+5);
                }
                setImage(base->getImage2(3));
                sframe++;
           }
           else if (sframe >= 8 && sframe < 10)
           {
                if (sframe == 8)
                {
                setX(getX()-8);
                setY(getY()+7);
                }
                setImage(base->getImage2(4));
                sframe++;
           }
           else if (sframe >= 10)
           {
                setY(getY()-2);
                setX(getX()+12);
                base=theBases[lastWeapon];
                setImage(base->getImage2(0));
                slashing = false;
                sframe=0;
           }            
        }
        else if (this->getDirection()=='S')
        {
           if(sframe < 10)
           {
                    setImage(base->getImage2(5+(sframe/2)));
                    sframe++;
           }
           else if (sframe == 10)
           {
                base=theBases[lastWeapon];
                setImage(base->getImage2(8));
                slashing = false;
                sframe=0;
           }
        }
        else if (this->getDirection()=='W')
        {
           if(sframe < 12)
           {
                    setImage(base->getImage2(10+(sframe/3)));
                    sframe++;
           }
           else if (sframe == 12)
           {
                setX(getX()+10);
                base=theBases[lastWeapon];
                setImage(base->getImage2(17));
                slashing = false;
                sframe=0;
           }
        }
        else if (this->getDirection()=='E')
        {
           if(sframe < 9)
           {
                    setImage(base->getImage2(14+(sframe/3)));
                    sframe++;
           }
           else if (sframe >= 9)
           {
                base=theBases[lastWeapon];
                setImage(base->getImage2(21));
                slashing = false;
                sframe=0;
           }
        }
        
     }
     
     //Plays the movement animations and moves the sprite on the screen
     else
     { 
        char direction;
        
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

        if((getY() >= 0+(screenHeight/3)) || (mapY >= 0))
        {
            int y=((mapY-getY()-getH()+1+mSpeed)/tileHeight);
            int x=((mapX-getX())/tileWidth);   
            if(collide(theMap, y, x))
            {    
               setY(getY()-mSpeed);
            }
        }
        else
        {
            yOffset=backY;
            backY=backY+mSpeed;
            mapY=mapY+mSpeed;
            yOffset=backY-yOffset;
        }
        if (lastWeapon==0)
           determineFrame(0, 15);
        else if (lastWeapon==3)
           determineFrame(0, 40);
        
        direction = this->getDirection();
        if(direction != 'N')
        {
            setDirection('N');
            setImage(base->getImage2(0));
            frame = 0;
        }
    }
     
    else if (keys[SDLK_DOWN])
    {
        setOldY(getY()-mSpeed);
        if((getY() <= (screenHeight-(screenHeight/3))) || (mapY <= (screenHeight-levelHeight)))
        {
            int y=((mapY-getY()-getH()+1-mSpeed)/tileHeight);
            int x=((mapX-getX())/tileWidth);   
            if(collide(theMap, y, x))
            {    
                 setY(getY()+mSpeed);
            }
        }
        else
        {
            yOffset=backY;
            backY=backY-mSpeed;
            mapY=mapY-mSpeed;
            yOffset=backY-yOffset;
        }
    

        if (lastWeapon==0)
        determineFrame(3, 15);
        else if (lastWeapon==3)
        determineFrame(8, 45);
        
        direction = getDirection();
        if(direction != 'S')
        {
            setDirection('S');
            setImage(base->getImage2(3));
            frame = 0;
        }
    }  
    if (keys[SDLK_LEFT])
    {
        setOldX(getX()+mSpeed);
        if((getX() >= (0+(screenWidth/3))) || (mapX > 0))
        {
            int y=((mapY-getY()-getH()+1)/tileHeight);
            int x=((mapX-getX()+mSpeed)/tileWidth);
            if(collide(theMap, y, x))
            {    
                 setX(getX()-mSpeed);
            }
        }
        else
        {
            xOffset=backX;
            backX=backX+mSpeed;
            mapX=mapX+mSpeed;
            xOffset=backX-xOffset;
        }
        if (!keys[SDLK_UP] && !keys[SDLK_DOWN])
        {
            if (lastWeapon==0)   
            determineFrame(6, 15);
            else if (lastWeapon==3)
            determineFrame(17, 20);
            
            direction = getDirection();
            if(direction != 'W')
            {
                setDirection('W');
                setImage(base->getImage2(6));
                frame = 0;
            }
        }
    }

    else if (keys[SDLK_RIGHT])
    {
        setOldX(getX()-mSpeed);
        if((getX() <= (screenWidth-(screenWidth/3))) || (mapX <= (screenWidth-levelWidth)))
        {
            int y=((mapY-getY()-getH()+1)/tileHeight);
            int x=((mapX-getX()-getW()+1-mSpeed)/tileWidth);
            if(collide(theMap, y, x))
            {    
                 setX(getX()+mSpeed);
            }
        }
        else
        {
            xOffset=backX;
            backX=backX-mSpeed;
            mapX=mapX-mSpeed;
            xOffset=backX-xOffset;
        }
        
        if (!keys[SDLK_UP] && !keys[SDLK_DOWN])
        {
            if (lastWeapon==0)
            determineFrame(9, 15);
            else if (lastWeapon==3)
            determineFrame(21, 30);
            
            direction = getDirection();
            if(direction != 'E')
            {
                setDirection('E');
                setImage(base->getImage2(9));
                frame = 0;
                
            }
        }
    }
}
    
}

void player::slash()
{
        theSlashes = NULL;
        if(theSlashes == NULL)
        {     
            theSlashes = new sprite;
            
    	    if(mDirection == 'E')
            {
                theSlashes->initSprite("data/images/items/null.png", mScreen, (getX()+(getW()/2))+10, getY()+(getH()/2), 15, 5);
    	    }
    	    else if(mDirection == 'W')
    	    {
                setX(getX()-10);
                theSlashes->initSprite("data/images/items/null.png", mScreen, (getX()+(getW()/2))-15, getY()+(getH()/2), 15, 5); 
    	    }
    	    else if(mDirection == 'N')
    	    {
                setY(getY()-10);
        		theSlashes->initSprite("data/images/items/null.png", mScreen, getX()+(getW()/2)-5, (getY()+(getH()/2))-20, 15, 5);
    	    }
    	    else if(mDirection == 'S')
    	    {
        		theSlashes->initSprite("data/images/items/null.png", mScreen, getX()+(getW()/2)-5, (getY()+(getH()/2))+10, 15, 5);
    	    }
    	    
            theSlashes->setDirection(mDirection);
            
        }
        
        slashTime=0;
        slashing = true;
        
}

void player::lamp()
{
        theLamp = NULL;
        if(theLamp == NULL)
        {     
            theLamp = new sprite;
            
    	    if(mDirection == 'E')
            {
                theLamp->initSprite("data/images/misc/flame.png", mScreen, (getX()+(getW()/2))+10, getY()+(getH()/2), 15, 5);
    	    }
    	    else if(mDirection == 'W')
    	    {
                theLamp->initSprite("data/images/misc/flame.png", mScreen, (getX()+(getW()/2))-15, getY()+(getH()/2), 15, 5); 
    	    }
    	    else if(mDirection == 'N')
    	    {
        		theLamp->initSprite("data/images/misc/flame.png", mScreen, getX()+(getW()/2)-5, (getY()+(getH()/2))-20, 15, 5);
    	    }
    	    else if(mDirection == 'S')
    	    {
        		theLamp->initSprite("data/images/misc/flame.png", mScreen, getX()+(getW()/2)-5, (getY()+(getH()/2))+10, 15, 5);
    	    }
    	    
            theLamp->setDirection(mDirection);
            mMagic=mMagic-20;
            
        }
        lampTime=0;
        lampUse = true;
        
}

void player::boomerang()
{
        if(boomHeld==true)
        {     
            theBoomerang = new sprite;
            
    	    if(mDirection == 'E')
            {
               theBoomerang->initSprite(boomerangBase, mScreen, (getX()+(getW()/2))+10, getY()+(getH()/2), 15, 5);
                theBoomerang->setImage(boomerangBase->getImage("right"));
    	    }
    	    else if(mDirection == 'W')
    	    {
            theBoomerang->initSprite(boomerangBase, mScreen, (getX()+(getW()/2))-20, getY()+(getH()/2), 15, 5);
                theBoomerang->setImage(boomerangBase->getImage("left"));
    	    }
    	    else if(mDirection == 'N')
    	    {
        	theBoomerang->initSprite(boomerangBase, mScreen, getX()+(getW()/2)-5, (getY()+(getH()/2))-20, 15, 5);
                theBoomerang->setImage(boomerangBase->getImage("up"));
    	    }
    	    else if(mDirection == 'S')
    	    {
        	theBoomerang->initSprite(boomerangBase, mScreen, getX()+(getW()/2)-5, (getY()+(getH()/2))+10, 15, 5);
                theBoomerang->setImage(boomerangBase->getImage("down"));
    	    }
    	    
            theBoomerang->setDirection(mDirection);
            
            startX=theBoomerang->getX();
            startY=theBoomerang->getY();
            
            boomHeld=false;
            boomReturn=false;
        }
}


void player::fireArrow()
{
    for(unsigned int i=0; i<theArrows.size(); i++)
    {
        if(theArrows[i] == NULL)
        {     
            theArrows[i] = new sprite;
    	    if(mDirection == 'E')
            {
    	        theArrows[i]->initSprite(arrowBase, mScreen, getX()+(getW()/2), getY()+(getH()/2), 15, 5);
                theArrows[i]->setImage(arrowBase->getImage("right"));
    	    }
    	    else if(mDirection == 'W')
    	    {
        		theArrows[i]->initSprite(arrowBase, mScreen, getX()+(getW()/2), getY()+(getH()/2), 15, 5);
                theArrows[i]->setImage(arrowBase->getImage("left"));
    	    }
    	    else if(mDirection == 'N')
    	    {
        		theArrows[i]->initSprite(arrowBase, mScreen, getX()+(getW()/2), getY()+(getH()/2), 5, 15);
                theArrows[i]->setImage(arrowBase->getImage("up"));
    	    }
    	    else if(mDirection == 'S')
    	    {
        		theArrows[i]->initSprite(arrowBase, mScreen, getX()+(getW()/2), getY()+(getH()/2), 5, 15);
                theArrows[i]->setImage(arrowBase->getImage("down"));
    	    }
    	    
            theArrows[i]->setDirection(mDirection);
            
            i=4;
            lastWeapon=0;
        }
    }
}


SDL_Surface* player::drawInventory()
{
    SDL_Surface* inv;
    inv = SDL_CreateRGBSurface(SDL_HWSURFACE, 620, 600, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);      
    SDL_SetColorKey(inv, SDL_SRCCOLORKEY, SDL_MapRGB(inv->format, 72, 152, 72));
    
    SDL_Rect srcdest;
    srcdest.x = 440;
    srcdest.y = 60;
    srcdest.w = 160;
    srcdest.h = 60;
    
    SDL_FillRect(inv, &srcdest, SDL_MapRGB(inv->format, 0, 0, 0));   
    
    //Creates a surface using the currently selected item, i is limited based on the number of selectable items
    SDL_Surface *invImage;
    for (int i=0; i<6; i++)
    {
        if (mInv[i]->getSelected())
        {
        invImage = getInvImage(i);
        srcdest.x = 500;
        srcdest.y = 70;
        srcdest.w = 160;
        srcdest.h = 60;
        SDL_BlitSurface(invImage, NULL, inv, &srcdest);
        
        }
            
    } 
    return inv;
}


void player::boomerangMove(int mapX, int mapY, int tileWidth, int tileHeight, std::vector< std::vector <int> > &theMap)
{
     int j=((mapY-theBoomerang->getY()-theBoomerang->getH()+1)/tileHeight);
     int k=((mapX-theBoomerang->getX())/tileWidth);
     
     //Animates the boomerang
     if(theBoomerang->frame < 5)
        {
            theBoomerang->setImage(boomerangBase->getImage("up"));
            theBoomerang->frame++;
        }
        else if (theBoomerang->frame >= 5 && theBoomerang->frame < 10)
        {
            theBoomerang->setImage(boomerangBase->getImage("right"));
            theBoomerang->frame++;
        }
        else if (theBoomerang->frame >= 10 && theBoomerang->frame < 15)
        {
            theBoomerang->setImage(boomerangBase->getImage("down"));
            theBoomerang->frame++;
        }
        else if (theBoomerang->frame >= 15 && theBoomerang->frame < 20)
        {
            theBoomerang->setImage(boomerangBase->getImage("left"));
            theBoomerang->frame++;
        }
        else if (theBoomerang->frame == 20)
        {
            theBoomerang->setImage(boomerangBase->getImage("up"));
            theBoomerang->frame = 0;
        }
     
     
     //Moves the boomerang away from the start position
     if (boomReturn==false)
     {
     if(theBoomerang->getDirection() == 'E')
            {
                theBoomerang->setX(theBoomerang->getX()+4);
                if((theBoomerang->getX() > startX+100)|| !collide(theMap, j, k))
                {
                   boomReturn=true;
                }
            }
            else if(theBoomerang->getDirection() == 'W')
            {
                theBoomerang->setX(theBoomerang->getX()-4);
                if((theBoomerang->getX() < startX-100) || !collide(theMap, j, k))
                {
                   boomReturn=true;
                }

            }
            else if(theBoomerang->getDirection() == 'N')
            {
                theBoomerang->setY(theBoomerang->getY()-4);
                if((theBoomerang->getY() < startY-100) || !collide(theMap, j, k))
                {
                   boomReturn=true;
                }
            }
            else if(theBoomerang->getDirection() == 'S')
            {
                theBoomerang->setY(theBoomerang->getY()+4);
                if((theBoomerang->getY() > startY+100) || !collide(theMap, j, k))
                {
                   boomReturn=true;
                }
            }           
            }
     
     //Moves the boomerang back towards the player
     if (boomReturn)
     {
    if(mX < theBoomerang->getX())
    {
        theBoomerang->setX(theBoomerang->getX()-3);

        if(mY > theBoomerang->getY())
        {
            theBoomerang->setY(theBoomerang->getY()+3);
        }

        else if(mY < theBoomerang->getY())
        {	
            theBoomerang->setY(theBoomerang->getY()-3);	  
        }
    }
    
    else if(mX > theBoomerang->getX())
    {
        theBoomerang->setX(theBoomerang->getX()+3);
        
        if(mY > theBoomerang->getY())
        {
            theBoomerang->setY(theBoomerang->getY()+3);

        }
        else if(mY < theBoomerang->getY())
        {		
            theBoomerang->setY(theBoomerang->getY()-3);	  
        }
    }

    else if(mY < theBoomerang->getY())
    {
        theBoomerang->setY(theBoomerang->getY()-3);
        if(mX > theBoomerang->getX())
        {
            theBoomerang->setX(theBoomerang->getX()+1);
            
        }
        else if(mX < theBoomerang->getX())
        {
            theBoomerang->setX(theBoomerang->getX()-1);
        }
    }
    
    else if(mY > theBoomerang->getY())
    {
        theBoomerang->setY(theBoomerang->getY()+3);
        if(mX > theBoomerang->getX())
        {
            theBoomerang->setX(theBoomerang->getX()+1);
        }
        else if(mX < theBoomerang->getX())
        {
            theBoomerang->setX(theBoomerang->getX()-3);
        }
    }

  }
}


SDL_Surface* player::drawMagic()
{
    SDL_Surface* magic;    
    
    magic = SDL_CreateRGBSurface(SDL_HWSURFACE, 22, 68, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
 
    SDL_SetColorKey(magic, SDL_SRCCOLORKEY, SDL_MapRGB(magic->format, 72, 152, 72));
 
    SDL_Rect srcdest;
    srcdest.x = 0;
    srcdest.w = 22;
    srcdest.y = 68-(mMagic / 2);
    srcdest.h = (mMagic / 2);
    
    SDL_FillRect(magic, &srcdest, SDL_MapRGB(magic->format, 0, 170, 0));
    
    return magic;
}

void player::determineFrame(int modifier, int endframe)
{
        if(frame < endframe)
        {
            setImage(base->getImage2(modifier+(frame/5)));
            frame++;
        }
        else if (frame == endframe)
        {
            frame = 0;		
            setImage(base->getImage2(modifier+(frame/5)));
        }     
}
