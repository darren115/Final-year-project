#include "level.h"

void level::levelCode(vector<orc *> &badGuys, vector<sprite *> &goodGuys, vector<Item *> &theObjects, player *thePlayer, engine *theEngine, SDL_Surface *screen, SDL_Surface *back, vector< vector <int> > &theMap, vector<sprite *> &screenInfo, vector<sprite *> &theDoors, vector< vector < int> > &backSurface, vector<SDL_Surface *> &surfaces, int &mapXPos, int &mapYPos, int mapX, int mapY, int tileHeight, int tileWidth, int backX, int backY, int screenWidth, int screenHeight, int audioflag, int level, SFont *fonta, vector<spriteBase *> &itemBase, vector<Item *> &uItems, vector<bool> cheats)
{
    
    //Play low health beep
    if ((thePlayer->getLife()<=thePlayer->getHearts()/3)&&(SDL_GetTicks()-lowHealth>1500))
    {
       if (audioflag)                                                 
          theEngine->Sound->playEffect("data/sound/new_effects/LTTP_LowHealth.wav", "play", 0,0);  
          lowHealth = SDL_GetTicks();                                                                        
    }
    
    
    //Update Arrows
    vector<sprite *>& playerArrows = thePlayer->getWeapon();
    for(unsigned int i=0; i < playerArrows.size(); i++)
    {
        if(playerArrows[i] != NULL)
        {
            //Move Arrows
            if(playerArrows[i]->getDirection() == 'E')
            {
                playerArrows[i]->setX(playerArrows[i]->getX()+5);
                if(playerArrows[i]->getX() > 640)
                {
                    delete playerArrows[i];
                    playerArrows[i] = NULL;
                    break;
                }
            }
            else if(playerArrows[i]->getDirection() == 'W')
            {
                playerArrows[i]->setX(playerArrows[i]->getX()-5);
                if(playerArrows[i]->getX() < 0-playerArrows[i]->getW())
                {
                    delete playerArrows[i];
                    playerArrows[i] = NULL;
                    break;
                }

            }
            else if(playerArrows[i]->getDirection() == 'N')
            {
                playerArrows[i]->setY(playerArrows[i]->getY()-5);
                if(playerArrows[i]->getY() < 0-playerArrows[i]->getH())
                {
                    delete playerArrows[i];
                    playerArrows[i] = NULL;
                    break;
                }
            }
            else if(playerArrows[i]->getDirection() == 'S')
            {
                playerArrows[i]->setY(playerArrows[i]->getY()+5);
                if(playerArrows[i]->getY() > 480)
                {
                    delete playerArrows[i];
                    playerArrows[i] = NULL;
                    break;
                }
            }

            //Check for Collisions with Badguys
            for(unsigned int j=0; j<badGuys.size(); j++)
            {
                if(theEngine->spriteCollide(playerArrows[i], badGuys[j]) == 1)
                {
                    if (audioflag)
                        theEngine->Sound->playEffect("data/sound/effects/arrow_hit.wav", "play", 0,0);
                    
                    if(playerArrows[i]->getDirection() == 'E')
                    {
                        badGuys[j]->setX(badGuys[j]->getX()+2);
                        badGuys[j]->setAction(2);
                    }
                    else if(playerArrows[i]->getDirection() == 'W')
                    {
                        badGuys[j]->setX(badGuys[j]->getX()-2);
                        badGuys[j]->setAction(2);
                    }
                    else if(playerArrows[i]->getDirection() == 'N')
                    {
                        badGuys[j]->setY(badGuys[j]->getY()-2);
                        badGuys[j]->setAction(2);
                    }
                    else if(playerArrows[i]->getDirection() == 'S')
                    {
                        badGuys[j]->setY(badGuys[j]->getY()+2);
                        badGuys[j]->setAction(2);
                    } 
                    
                    badGuys[j]->setLife(badGuys[j]->getLife()-1);
                    delete playerArrows[i];
                    playerArrows[i] = NULL;
                    break;
                }
            }
            
            //Check for Collisions with goodguys
            if(playerArrows[i] != NULL)
            {
                for(unsigned int j=0; j<goodGuys.size(); j++)
                {
                    if(theEngine->spriteCollide(playerArrows[i], goodGuys[j]) == 1)
                    {
                        if (audioflag)
                            theEngine->Sound->playEffect("data/sound/effects/arrow_hit.wav", "play", 0,0);
                    
                        delete playerArrows[i];
                        playerArrows[i] = NULL;
                        break;
                    }
                }
            }
            
            //Check for Collisions with Background
            if(playerArrows[i] != NULL)
            {
                int j=((mapY-playerArrows[i]->getY()-playerArrows[i]->getH()+1)/tileHeight);
                int k=((mapX-playerArrows[i]->getX())/tileWidth);
                //Changed for new tiles
                if(!collide(theMap, j, k))
                {
                    delete playerArrows[i];
                    playerArrows[i] = NULL;
                    break;
                }
            }
        }
    }
    
    
    
    //Check sword collisions with enemy
    sprite* &playerSlashes = thePlayer->getSlashes();
        if(playerSlashes != NULL)
        {
            for(unsigned int j=0; j<badGuys.size(); j++)
            {
                if(theEngine->spriteCollide(playerSlashes, badGuys[j]) == 1)
                {
                    if (audioflag)
                        theEngine->Sound->playEffect("data/sound/effects/arrow_hit.wav", "play", 0,0);
                    
                    bool moved = false; 
                    int mod = 20;
                    
                    if(playerSlashes->getDirection() == 'E')
                    {
                        while ((moved == false) && (mod >=5))
                        {
                           int y=((mapY-badGuys[j]->getY()-badGuys[j]->getH()+1)/tileHeight);
                           int x=((mapX-badGuys[j]->getX()-badGuys[j]->getW()+1-mod)/tileWidth);
                           //Changed for new tiles
                           if(collide(theMap, y, x))
                           {
                               badGuys[j]->setX(badGuys[j]->getX()+mod);
                               moved=true;            
                           }
                           else
                               mod = mod/2;
                        }
                        badGuys[j]->setAction(2);
                    }
                    else if(playerSlashes->getDirection() == 'W')
                    {
                        
                        while ((moved == false) && (mod >=5))
                        {
                           int y=((mapY-badGuys[j]->getY()-badGuys[j]->getH()+1)/tileHeight);
                           int x=((mapX-badGuys[j]->getX()+mod)/tileWidth);
                           //Changed for new tiles
                           if(collide(theMap, y, x))
                           {
                               badGuys[j]->setX(badGuys[j]->getX()- mod);
                               moved=true;              
                           }
                           else
                               mod = mod/2;
                            
                        }
                        badGuys[j]->setAction(2);
                    }
                    else if(playerSlashes->getDirection() == 'N')
                    {
                        
                        while ((moved == false) && (mod >=5))
                        {
                            int y=((mapY-badGuys[j]->getY()-badGuys[j]->getH()+1+mod)/tileHeight);
                            int x=((mapX-badGuys[j]->getX())/tileWidth);
                            //Changed for new tiles
                            if(collide(theMap, y, x))
                            {
                                badGuys[j]->setY(badGuys[j]->getY()-mod);
                                moved=true;              
                            }
                            else
                               mod = mod/2;
                        }
                        badGuys[j]->setAction(2);
                    }
                    else if(playerSlashes->getDirection() == 'S')
                    {
                        
                        while ((moved == false) && (mod >=5))
                        {
                            int y=((mapY-badGuys[j]->getY()-badGuys[j]->getH()+1-mod)/tileHeight);
                            int x=((mapX-badGuys[j]->getX())/tileWidth);      
                            //Changed for new tiles
                            if(collide(theMap, y, x))
                            {
                                badGuys[j]->setY(badGuys[j]->getY()+mod);
                                moved=true;            
                                printf("%d\n",mod);
                            }
                            else
                               mod = mod/2;
                        }
                        badGuys[j]->setAction(2);
                    } 
                    
                    if (badGuys[j]->getEType()!=4)
                    badGuys[j]->setLife(badGuys[j]->getLife()-1);
                    delete playerSlashes;
                    playerSlashes = NULL;
                    break;
                }
            }
            
            if (thePlayer->getSlashTime()>10)
            {
                delete playerSlashes;
                playerSlashes = NULL;
            }
            else
               thePlayer->setSlashTime(thePlayer->getSlashTime()+1);
    }
    
    //Check sword collisions with enemy
    sprite* &playerLamp = thePlayer->getLamp();
        if(playerLamp != NULL)
        {            
            if (thePlayer->getLampTime()>6)
            {
                delete playerLamp;
                playerLamp = NULL;
                thePlayer->setLampUse(false);
            }
            else
            {
               thePlayer->setLampTime(thePlayer->getLampTime()+1);
               
              if (level == 53)
              {
                if ((theEngine->spriteCollide(playerLamp, theObjects[2]) == 1) && !thePlayer->getCollected(3)&& !theObjects[1]->getVisible())
                {
                   thePlayer->setX(thePlayer->getOldX());
        	       thePlayer->setY(thePlayer->getOldY());
    	           theObjects[2]->setImage(theObjects[2]->getBase()->getImage("down1"));
                   if (audioflag)
                       theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Secret.wav", "play", 0,0);            
    	               theObjects[1]->setVisible(true);
                }
              }                       
                             
            }
    }
    
    //Update boomerang
    sprite* &playerBoomerang = thePlayer->getBoomerang();
        if(playerBoomerang != NULL)
        {
          thePlayer->boomerangMove(mapX, mapY, tileWidth, tileHeight, theMap);           
                  if (audioflag)                                                 
                     theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Boomerang.wav", "play", 0,0);  
                           
            for(unsigned int j=0; j<badGuys.size(); j++)
            {
                if(theEngine->spriteCollide(playerBoomerang, badGuys[j]) == 1)
                {
                    if (audioflag)
                        theEngine->Sound->playEffect("data/sound/effects/arrow_hit.wav", "play", 0,0);
                    
                    bool moved = false; 
                    int mod = 20;
                    
                    if(playerBoomerang->getDirection() == 'E')
                    {
                        
                        while ((moved == false) && (mod >=5))
                        {
                           int y=((mapY-badGuys[j]->getY()-badGuys[j]->getH()+1)/tileHeight);
                           int x=((mapX-badGuys[j]->getX()-badGuys[j]->getW()+1-mod)/tileWidth);
                           //Changed for new tiles
                           if(collide(theMap, y, x))
                           {
                               badGuys[j]->setX(badGuys[j]->getX()+mod);
                               moved=true;            
                           }
                           else
                               mod = mod/2;
                        }
                        badGuys[j]->setAction(2);
                    }
                    else if(playerBoomerang->getDirection() == 'W')
                    {
                        
                        while ((moved == false) && (mod >=5))
                        {
                           int y=((mapY-badGuys[j]->getY()-badGuys[j]->getH()+1)/tileHeight);
                           int x=((mapX-badGuys[j]->getX()+mod)/tileWidth);
                           //Changed for new tiles
                           if(collide(theMap, y, x))
                           {
                               badGuys[j]->setX(badGuys[j]->getX()- mod);
                               moved=true;              
                           }
                           else
                               mod = mod/2;
                            
                        }
                        badGuys[j]->setAction(2);
                    }
                    else if(playerBoomerang->getDirection() == 'N')
                    {
                        
                        while ((moved == false) && (mod >=5))
                        {
                            int y=((mapY-badGuys[j]->getY()-badGuys[j]->getH()+1+mod)/tileHeight);
                            int x=((mapX-badGuys[j]->getX())/tileWidth);
                            //Changed for new tiles
                            if(collide(theMap, y, x))
                            {
                                badGuys[j]->setY(badGuys[j]->getY()-mod);
                                moved=true;              
                            }
                            else
                               mod = mod/2;
                        }
                        badGuys[j]->setAction(2);
                    }
                    else if(playerBoomerang->getDirection() == 'S')
                    {
                        
                        while ((moved == false) && (mod >=5))
                        {
                            int y=((mapY-badGuys[j]->getY()-badGuys[j]->getH()+1-mod)/tileHeight);
                            int x=((mapX-badGuys[j]->getX())/tileWidth);      
                            //Changed for new tiles
                            if(collide(theMap, y, x))
                            {
                                badGuys[j]->setY(badGuys[j]->getY()+mod);
                                moved=true;            
                                printf("%d\n",mod);
                            }
                            else
                               mod = mod/2;
                        }
                        badGuys[j]->setAction(2);
                    } 
                    
                    badGuys[j]->setAction(3);
                    thePlayer->setReturn();
                }
            }
            for(unsigned int j=0; j<goodGuys.size(); j++)
            {
                 if(theEngine->spriteCollide(playerBoomerang, goodGuys[j]) == 1)
                 {
                      if (audioflag)
                          theEngine->Sound->playEffect("data/sound/effects/arrow_hit.wav", "play", 0,0);
                      thePlayer->setReturn();
                 }
            }
            //Boom Return
            if(theEngine->spriteCollide(playerBoomerang, thePlayer) == 1)
            {
                    
                    thePlayer->setHeld();
                    delete playerBoomerang;
                    playerBoomerang = NULL;
            }
    }
    
    //Update Badguys
    for(unsigned int i=0; i < badGuys.size(); i++)
    {
        if(badGuys[i] != NULL)
        {
            badGuys[i]->setOldX(badGuys[i]->getX());
            badGuys[i]->setOldY(badGuys[i]->getY());
            //Check if the sprite is alive
            if(badGuys[i]->getLife() <= 0)
            {
                
                thePlayer->setScore(thePlayer->getScore()+5);
             //randomly chooses to create an item or not create an item
             int rand1;
             
             srand ( time(NULL) );
             //randomly chooses which item to create
             if (rand()%10+1>=6)
             {
            
             int randVar=rand()%100+1;
                if (randVar>80)
                {
                    uItems.push_back(new Item("Heart"));
                    uItems[uItems.size()-1]->initSprite(itemBase[0], screen, badGuys[i]->getX(), badGuys[i]->getY(), 17, 24);
                }
                else if (randVar>40)
                {
                    uItems.push_back(new Item("Rupee1"));
                    uItems[uItems.size()-1]->initSprite(itemBase[1], screen, badGuys[i]->getX(), badGuys[i]->getY(), 17, 24);
                }
                else if (randVar<=40 && randVar>30)
                {
                    uItems.push_back(new Item("SmallPot"));
                    uItems[uItems.size()-1]->initSprite(itemBase[2], screen, badGuys[i]->getX(), badGuys[i]->getY(), 17, 24);
                }
                else if (randVar>10)
                {
                    uItems.push_back(new Item("Arrow1"));
                    uItems[uItems.size()-1]->initSprite(itemBase[3], screen, badGuys[i]->getX(), badGuys[i]->getY(), 17, 24);
                }
                else if (randVar>=0)
                {
                    uItems.push_back(new Item("Arrow5"));
                    uItems[uItems.size()-1]->initSprite(itemBase[4], screen, badGuys[i]->getX(), badGuys[i]->getY(), 17, 24);
                }            
             }    
                
                badGuys.erase(badGuys.begin()+i);
                if (audioflag)
                    theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Enemy_Kill.wav", "play", 0,0);
                
                break;
            }

            //Look, Patrol and Attack
            badGuys[i]->look(thePlayer->getX(), thePlayer->getY());
            if((badGuys[i]->getAction() != 2) || (badGuys[i]->getAction() == 3 ))
            {
                badGuys[i]->patrol();
            }
            else if(badGuys[i]->getAction() == 2)
            {
                badGuys[i]->attack(thePlayer->getX(), thePlayer->getY(), mapX, mapY, tileWidth, tileHeight, theMap);
            }
            
            

            //Check for Collisions with the player
            if(theEngine->spriteCollide(badGuys[i], thePlayer) == 1)
            {

                //Kill the Player
                thePlayer->setOldX(thePlayer->getX());
                thePlayer->setOldY(thePlayer->getY());
                if((SDL_GetTicks() - thePlayer->getDeathTime()) > 1500)
                {
                    thePlayer->setDeathTime(SDL_GetTicks());
                    if (cheats[0] == 0)
                        thePlayer->setLife(thePlayer->getLife()-1);
                    
                    if (audioflag)
                        theEngine->Sound->playEffect("data/sound/effects/hurt.wav", "play", 0,0);
            
                }
                char direction = badGuys[i]->getDirection();
                bool moved = false; 
                int mod = 10;
                if(direction == 'N')
                {
                    while ((moved == false) && (mod >=2))
                    {
                        int y=((mapY-thePlayer->getY()-thePlayer->getH()+1+mod)/tileHeight);
                        int x=((mapX-thePlayer->getX())/tileWidth);
                        //Changed for new tiles
                        if(collide(theMap, y, x))
                        {
                            thePlayer->setY(thePlayer->getY()-mod);
                            moved=true;              
                        }
                        else
                            mod = mod/2;
                    }
                }
                else if(direction == 'S')
                {
                    while ((moved == false) && (mod >=2))
                        {
                        int y=((mapY-thePlayer->getY()-thePlayer->getH()+1-mod)/tileHeight);
                        int x=((mapX-thePlayer->getX())/tileWidth);      
                        //Changed for new tiles
                        if(collide(theMap, y, x))
                        {
                            thePlayer->setY(thePlayer->getY()+mod);
                            moved=true;            
                        }
                        else
                            mod = mod/2;
                    }
                } 
                else if(direction == 'E')
                {
                    while ((moved == false) && (mod >=5))
                    {
                        int y=((mapY-thePlayer->getY()-thePlayer->getH()+1)/tileHeight);
                        int x=((mapX-thePlayer->getX()-thePlayer->getW()+1-mod)/tileWidth);
                        //Changed for new tiles
                        if(collide(theMap, y, x))
                        {
                           thePlayer->setX(thePlayer->getX()+mod);
                           moved=true;            
                        }
                        else
                           mod = mod/2;
                    }
                }
                else if(direction == 'W')
                {
                    while ((moved == false) && (mod >=5))
                    {
                        int y=((mapY-thePlayer->getY()-thePlayer->getH()+1)/tileHeight);
                        int x=((mapX-thePlayer->getX()+mod)/tileWidth);
                        //Changed for new tiles
                        if(collide(theMap, y, x))
                        {
                           thePlayer->setX(thePlayer->getX()- mod);
                           moved=true;              
                        }
                        else
                           mod = mod/2;
                    }
                }
                
            }

            //Check for Collisions the other way around
            if(theEngine->spriteCollide(thePlayer, badGuys[i]) == 1)
            {
                //Kill the Player
                thePlayer->setOldX(thePlayer->getX());
                thePlayer->setOldY(thePlayer->getY());
                if (cheats[0] == 0)
                thePlayer->setLife(thePlayer->getLife()-1);

                if (audioflag)
                    theEngine->Sound->playEffect("data/sound/effects/hurt.wav", "play", 0,0);
            
                char direction = thePlayer->getDirection();
                if(direction == 'N')
                {
                    thePlayer->setY(thePlayer->getY()+10);
                    int j=((mapY-thePlayer->getY()-thePlayer->getH()+1)/tileHeight);
                    int k=((mapX-thePlayer->getX())/tileWidth);
                    //Changed for new tiles
                    if(!collide(theMap, j, k))
                    {
                        thePlayer->setY(thePlayer->getOldY()+1);
                    }
                }
                if(direction == 'S')
                {
                    thePlayer->setY(thePlayer->getY()-10);
                    int j=((mapY-thePlayer->getY()-thePlayer->getH()+1)/tileHeight);
                    int k=((mapX-thePlayer->getX())/tileWidth);
                    //Changed for new tiles
                    if(!collide(theMap, j, k))
                    {
                        thePlayer->setY(thePlayer->getOldY()-1);
                    }
                }
                if(direction == 'W')
                {
                    thePlayer->setX(thePlayer->getX()-10);
                }
                if(direction == 'E')
                {
                    thePlayer->setX(thePlayer->getX()+10);
                }
            }
            
            //Check for Collisions with Background
            int j=((mapY-badGuys[i]->getY()-badGuys[i]->getH()+1)/tileHeight);
            int k=((mapX-badGuys[i]->getX())/tileWidth);
            //Changed for new tiles
            if(!collide(theMap, j, k))
            {
                badGuys[i]->setCurrentPos(badGuys[i]->getCurrentPos()+1);
                badGuys[i]->setX(badGuys[i]->getOldX());
                badGuys[i]->setY(badGuys[i]->getOldY());
                if(badGuys[i]->getAction() == 2)
                {
                    //badGuys[i]->setX(badGuys[i]->getOldX());
                    //badGuys[i]->setY(badGuys[i]->getOldY());
                }
            }
            
            //check collisions with good guys
            for(unsigned int j=0; j < goodGuys.size(); j++)
            {
                if (theEngine->spriteCollide(badGuys[i], goodGuys[j]) == 1)
                {
                    badGuys[i]->setX(badGuys[i]->getOldX());
	                badGuys[i]->setY(badGuys[i]->getOldY());
                }
            }
            
            //check collisions with items
            for(unsigned int j=0; j < theObjects.size(); j++)
            {
                if ((theEngine->spriteCollide(badGuys[i], theObjects[j]) == 1) && (theObjects[j]->getVisible()))
                {
                    badGuys[i]->setX(badGuys[i]->getOldX());
	                badGuys[i]->setY(badGuys[i]->getOldY());
                }
            }
            
            if (badGuys[i]->getEType()==1)
            {
                badGuys[i]->setDiff(badGuys[i]->getDiff()+1);                                 

                vector<sprite *>& enemyArrows = badGuys[i]->getWeapon();
    for(unsigned int j=0; j < enemyArrows.size(); j++)
    {
        if(enemyArrows[j] != NULL)
        {
            //Move Arrows
            if(enemyArrows[j]->getDirection() == 'E')
            {
                enemyArrows[j]->setX(enemyArrows[j]->getX()+5);
                if(enemyArrows[j]->getX() > 640)
                {
                    delete enemyArrows[j];
                    enemyArrows[j] = NULL;
                    break;
                }
            }
            else if(enemyArrows[j]->getDirection() == 'W')
            {
                enemyArrows[j]->setX(enemyArrows[j]->getX()-5);
                if(enemyArrows[j]->getX() < 0-enemyArrows[j]->getW())
                {
                    delete enemyArrows[j];
                    enemyArrows[j] = NULL;
                    break;
                }

            }
            else if(enemyArrows[j]->getDirection() == 'N')
            {
                enemyArrows[j]->setY(enemyArrows[j]->getY()-5);
                if(enemyArrows[j]->getY() < 0-enemyArrows[j]->getH())
                {
                    delete enemyArrows[j];
                    enemyArrows[j] = NULL;
                    break;
                }
            }
            else if(enemyArrows[j]->getDirection() == 'S')
            {
                enemyArrows[j]->setY(enemyArrows[j]->getY()+5);
                if(enemyArrows[j]->getY() > 480)
                {
                    delete enemyArrows[j];
                    enemyArrows[j] = NULL;
                    break;
                }
            }


                if(theEngine->spriteCollide(enemyArrows[j], thePlayer) == 1)
                {
                    if (audioflag)
                        theEngine->Sound->playEffect("data/sound/effects/arrow_hit.wav", "play", 0,0);
                    
                    if(thePlayer->getDirection() == 'E')
                    {
                        thePlayer->setX(thePlayer->getX()+2);
                    }
                    else if(thePlayer->getDirection() == 'W')
                    {
                        thePlayer->setX(thePlayer->getX()-2);
                    }
                    else if(thePlayer->getDirection() == 'N')
                    {
                        thePlayer->setY(thePlayer->getY()-2);
                    }
                    else if(thePlayer->getDirection() == 'S')
                    {
                        thePlayer->setY(thePlayer->getY()+2);
                    } 
                    
                    if (cheats[0] == 0)
                    thePlayer->setLife(thePlayer->getLife()-1);
                    delete enemyArrows[j];
                    enemyArrows[j] = NULL;
                    break;
                }
            
           
            //Check for Collisions with goodguys
            if(enemyArrows[j] != NULL)
            {
                for(unsigned int l=0; l<goodGuys.size(); l++)
                {
                    if(theEngine->spriteCollide(enemyArrows[j], goodGuys[l]) == 1)
                    {
                        if (audioflag)
                            theEngine->Sound->playEffect("data/sound/effects/arrow_hit.wav", "play", 0,0);
                    
                        delete enemyArrows[j];
                        enemyArrows[j] = NULL;
                        break;
                    }
                }
            }
            
            //Check for Collisions with Background
            if(enemyArrows[j] != NULL)
            {
                int y=((mapY-enemyArrows[j]->getY()-enemyArrows[j]->getH()+1)/tileHeight);
                int x=((mapX-enemyArrows[j]->getX())/tileWidth);
                //Changed for new tiles
                if(!collide(theMap, y, x))
                {
                    delete enemyArrows[j];
                    enemyArrows[j] = NULL;
                    break;
                }
            }
        }
    }

} 
   
       
        }
    } 
       
       
    levelSpecific(badGuys, goodGuys, theObjects, thePlayer, theEngine, screen, back, theMap, screenInfo, theDoors, backSurface, surfaces, mapXPos, mapYPos, mapX, mapY, tileHeight, tileWidth, backX, backY, screenWidth, screenHeight, audioflag, level, fonta, itemBase, uItems, cheats);
    
    itemCode(screen, itemBase, uItems);
     
    
    //Collision with items
    for(unsigned int i=0; i < uItems.size(); i++)
    {
         if ((theEngine->spriteCollide(thePlayer, uItems[i]) == 1) && uItems[i]->getVisible())
         {
            if ((uItems[i]->getName().compare("Heart")== 0) &&(thePlayer->getLife()<thePlayer->getHearts()))
            {
                thePlayer->setLife(thePlayer->getLife()+1);
                uItems[i]->setVisible(false);
                if (audioflag)
                   theEngine->Sound->playEffect("data/sound/new_effects/LTTP_RefillHealth.wav", "play", 0,0);
            }
            else if ((uItems[i]->getName().compare("Rupee1")== 0) && (thePlayer->getRupees()<100))
            {
                 thePlayer->setRupees(thePlayer->getRupees()+1);
                 uItems[i]->setVisible(false);
                 if (audioflag)
                     theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Rupee1.wav", "play", 0,0);
            }
            else if ((uItems[i]->getName().compare("Arrow1")== 0) &&(thePlayer->getArrows()<50))
            {
                 thePlayer->setArrows(thePlayer->getArrows()+1);
                 uItems[i]->setVisible(false);
                 if (audioflag)
                     theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Rupee1.wav", "play", 0,0);
            }
            else if ((uItems[i]->getName().compare("Arrow5")== 0) &&(thePlayer->getArrows()<50))
            {
                 if (thePlayer->getArrows()+5>=50)
                    thePlayer->setArrows(50);
                 else 
                    thePlayer->setArrows(thePlayer->getArrows()+5);
                    uItems[i]->setVisible(false);
                    if (audioflag)
                       theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Rupee1.wav", "play", 0,0);
            }
            else if ((uItems[i]->getName().compare("SmallPot")== 0) && (thePlayer->getMagic()<136))
            {
                 if (thePlayer->getMagic()+25>=136)
                     thePlayer->setMagic(136);
                 else 
                      thePlayer->setMagic(thePlayer->getMagic()+25);
                 uItems[i]->setVisible(false);
                 if (audioflag)
                    theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Rupee1.wav", "play", 0,0);
            }
            else
            {
                if (audioflag)
                    theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Error.wav", "play", 0,0);
            }
         }
    }
    
        
}


void level::levelSpecific(vector<orc *> &badGuys, vector<sprite *> &goodGuys, vector<Item *> &theObjects, player *thePlayer, engine *theEngine, SDL_Surface *screen, SDL_Surface *back, vector< vector <int> > &theMap, vector<sprite *> &screenInfo, vector<sprite *> &theDoors, vector< vector < int> > &backSurface, vector<SDL_Surface *> &surfaces, int &mapXPos, int &mapYPos, int mapX, int mapY, int tileHeight, int tileWidth, int backX, int backY, int screenWidth, int screenHeight, int audioflag, int level, SFont *fonta, vector<spriteBase *> &itemBase, vector<Item *> &uItems, vector<bool> cheats)
{
    if (level == 0)
    {
    if (!goodGuys.empty())
    {
        //Update Collisions between player and goodguys
        //Collision detection for Fleeing Woman
        if (theEngine->spriteCollide(thePlayer, goodGuys[0]) == 1)
        {
            //Create message to tell Blink
            thePlayer->setX(thePlayer->getOldX());
    	    thePlayer->setY(thePlayer->getOldY());
    	    message(screen, "data/text/help.data", thePlayer->getName());
    	    if (audioflag)
               theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Text_Done.wav", "play", 0,0);
    	
            int location = goodGuys[0]->getY();
            int location2 = goodGuys[0]->getX();
            
            goodGuys[0]->frame = 0;
            
            while(goodGuys[0]->getX() > (location2-63))
            {
                goodGuys[0]->setX(goodGuys[0]->getX()-2);
                
                if(goodGuys[0]->frame < 5)
                {
                    goodGuys[0]->setImage(goodGuys[0]->getBase()->getImage("left"));
                    goodGuys[0]->frame++;
                }
                else if (goodGuys[0]->frame >= 5 && goodGuys[0]->frame < 10)
                {
                    goodGuys[0]->setImage(goodGuys[0]->getBase()->getImage("left1"));
                    goodGuys[0]->frame++;
                }
                else if (goodGuys[0]->frame == 10)
                    goodGuys[0]->frame = 0;
            
               dr.drawAll(theEngine, back, screen, thePlayer, badGuys, goodGuys, theObjects, screenInfo, theDoors, backX, backY, screenWidth, screenHeight, fonta, uItems);
            }
            while(goodGuys[0]->getY() < (103+location))
            {        
                goodGuys[0]->setY(goodGuys[0]->getY()+2);
                
                if(goodGuys[0]->frame < 5)
                {
                    goodGuys[0]->setImage(goodGuys[0]->getBase()->getImage("down"));
                    goodGuys[0]->frame++;
                }
                else if (goodGuys[0]->frame >= 5 && goodGuys[0]->frame < 10)
                {
                    goodGuys[0]->setImage(goodGuys[0]->getBase()->getImage("down1"));
                    goodGuys[0]->frame++;
                }
                else if (goodGuys[0]->frame == 10)
                    goodGuys[0]->frame = 0;
                    
                dr.drawAll(theEngine, back, screen, thePlayer, badGuys, goodGuys, theObjects, screenInfo, theDoors, backX, backY, screenWidth, screenHeight, fonta, uItems);
            }
            goodGuys.clear();       
            thePlayer->setProgress(thePlayer->getProgress()+1);
            
            char direction = thePlayer->getDirection();
            if(direction == 'N')
            {
                thePlayer->setY(thePlayer->getY()+1);
            }
            if(direction == 'S')
            {
                thePlayer->setY(thePlayer->getY()-1);
            }
            if(direction == 'W')
            {
                thePlayer->setX(thePlayer->getX()+1);
            }
            if(direction == 'E')
            {
                thePlayer->setX(thePlayer->getX()-1);
            }
        }
     }
     if ((theEngine->spriteCollide(thePlayer, theObjects[0]) == 1) && theObjects[0]->getVisible())
     {
           thePlayer->setX(thePlayer->getOldX());
    	   thePlayer->setY(thePlayer->getOldY());
    	
    	      if (audioflag)
                    theEngine->Sound->playEffect("data/sound/new_effects/LTTP_ItemFanfare_Stereo.wav", "play", 0,0);
            
               message(screen, "data/text/lamp.data", thePlayer->getName());
               theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Text_Done.wav", "play", 0,0);
	           theObjects[0]->setVisible(false);
               thePlayer->setProgress(thePlayer->getProgress()+1);	
               thePlayer->addItem(4);
            
     }
   }
   else if (level == 2)
   {
    //Cave Guard collision detection
    if (!goodGuys.empty())
    {
        if (theEngine->spriteCollide(thePlayer, goodGuys[0]) == 1)
        {
            thePlayer->setX(thePlayer->getOldX());
    	    thePlayer->setY(thePlayer->getOldY());
    	    if (!thePlayer->returnInventory()[13]->getVisible())
    	    {
    	        message(screen, "data/text/guard.data", thePlayer->getName());
    	        if (audioflag)
    	           theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Text_Done.wav", "play", 0,0);
             }
        } 
    
    
        //Witch collision detection
        if((theEngine->spriteCollide(thePlayer, goodGuys[1]) == 1))
        {
            thePlayer->setX(thePlayer->getOldX());
        	thePlayer->setY(thePlayer->getOldY());
            if (!thePlayer->returnInventory()[13]->getVisible())
            {
                message(screen, "data/text/witch1.data", thePlayer->getName());
                if (audioflag)
                   theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Text_Done.wav", "play", 0,0);
            }
            
            else if (!thePlayer->returnInventory()[0]->getVisible())
            {
                if (audioflag)
                    theEngine->Sound->playEffect("data/sound/effects/mushroom.wav", "play", 0,0);
            
                message(screen, "data/text/witch2.data", thePlayer->getName());
                theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Text_Done.wav", "play", 0,0);
                theObjects[1]->setVisible(true);
            }            
    	}
    
        //Update Collisions between player and goodguys
        
        //Collision detection for Fleeing Woman
        if ((theEngine->spriteCollide(thePlayer, goodGuys[2]) == 1) && (goodGuys[2]->getVisible()))
        {
            //Create message to tell Blink
            thePlayer->setX(thePlayer->getOldX());
    	    thePlayer->setY(thePlayer->getOldY());
    	    message(screen, "data/text/help1.data", thePlayer->getName());
    	    if (audioflag)
    	       theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Text_Done.wav", "play", 0,0);
    	
            int location = goodGuys[2]->getY();
            goodGuys[2]->frame = 0;
            
            while(goodGuys[2]->getY() < (100+location))
            {        
                goodGuys[2]->setY(goodGuys[2]->getY()+2);
                
                if(goodGuys[2]->frame < 5)
                {
                    goodGuys[2]->setImage(goodGuys[2]->getBase()->getImage("down"));
                    goodGuys[2]->frame++;
                }
                else if (goodGuys[2]->frame >= 5 && goodGuys[2]->frame < 10)
                {
                    goodGuys[2]->setImage(goodGuys[2]->getBase()->getImage("down1"));
                    goodGuys[2]->frame++;
                }
                else if (goodGuys[2]->frame == 10)
                    goodGuys[2]->frame = 0;
                    
                dr.drawAll(theEngine, back, screen, thePlayer, badGuys, goodGuys, theObjects, screenInfo, theDoors, backX, backY, screenWidth, screenHeight, fonta, uItems);
            
            }
            
            //goodGuys[2]->setImage(goodGuys[2]->getBase()->getImage("left"));
            
            while(goodGuys[2]->getX() > (-10-goodGuys[2]->getW()))
            {
                goodGuys[2]->setX(goodGuys[2]->getX()-2);
                
                if(goodGuys[2]->frame < 5)
                {
                    goodGuys[2]->setImage(goodGuys[2]->getBase()->getImage("left"));
                    goodGuys[2]->frame++;
                }
                else if (goodGuys[2]->frame >= 5 && goodGuys[2]->frame < 10)
                {
                    goodGuys[2]->setImage(goodGuys[2]->getBase()->getImage("left1"));
                    goodGuys[2]->frame++;
                }
                else if (goodGuys[2]->frame == 10)
                    goodGuys[2]->frame = 0;
            
                dr.drawAll(theEngine, back, screen, thePlayer, badGuys, goodGuys, theObjects, screenInfo, theDoors, backX, backY, screenWidth, screenHeight, fonta, uItems);
            
            }
            goodGuys[2]->setVisible(false);
            
            char direction = thePlayer->getDirection();
            if(direction == 'N')
            {
                thePlayer->setY(thePlayer->getY()+1);
            }
            if(direction == 'S')
            {
                thePlayer->setY(thePlayer->getY()-1);
            }
            if(direction == 'W')
            {
                thePlayer->setX(thePlayer->getX()+1);
            }
            if(direction == 'E')
            {
                thePlayer->setX(thePlayer->getX()-1);
            }
    
        }
 
        if(goodGuys[1]->frame < 30)
        {
            goodGuys[1]->setImage(goodGuys[1]->getBase()->getImage("left"));
            goodGuys[1]->frame++;
        }
        else if (goodGuys[1]->frame >= 30 && goodGuys[1]->frame < 60)
        {
            goodGuys[1]->setImage(goodGuys[1]->getBase()->getImage("right"));
            goodGuys[1]->frame++;
        }
        else if (goodGuys[1]->frame >= 60 && goodGuys[1]->frame < 90)
        {
            goodGuys[1]->setImage(goodGuys[1]->getBase()->getImage("up"));
            goodGuys[1]->frame++;
        }
        else if (goodGuys[1]->frame >= 90 && goodGuys[1]->frame < 120)
        {
            goodGuys[1]->setImage(goodGuys[1]->getBase()->getImage("down"));
            goodGuys[1]->frame++;
        }
        else if (goodGuys[1]->frame >= 120 && goodGuys[1]->frame < 150)
        {
            goodGuys[1]->setImage(goodGuys[1]->getBase()->getImage("left1"));
            goodGuys[1]->frame++;
        }
        else if (goodGuys[1]->frame >= 150 && goodGuys[1]->frame < 180)
        {
            goodGuys[1]->setImage(goodGuys[1]->getBase()->getImage("right1"));
            goodGuys[1]->frame++;
        }
        else if (goodGuys[1]->frame == 180)
        {
            goodGuys[1]->frame = 0;
        }
        
        //animate cave guard

            if(goodGuys[0]->frame < 100)
            {
                goodGuys[0]->setImage(goodGuys[0]->getBase()->getImage("left"));
                goodGuys[0]->frame++;
            }
            else if (goodGuys[0]->frame >= 100 && goodGuys[0]->frame < 120)
            {
                goodGuys[0]->setImage(goodGuys[0]->getBase()->getImage("right"));
                goodGuys[0]->frame++;
            }
            else if (goodGuys[0]->frame >= 120 && goodGuys[0]->frame < 140)
            {
                goodGuys[0]->setImage(goodGuys[0]->getBase()->getImage("up"));
                goodGuys[0]->frame++;
            }
            else if (goodGuys[0]->frame >= 140 && goodGuys[0]->frame < 160)
            {
                goodGuys[0]->setImage(goodGuys[0]->getBase()->getImage("right"));
                goodGuys[0]->frame++;
            }
            else if (goodGuys[0]->frame >= 160 && goodGuys[0]->frame < 180)
            {
                goodGuys[0]->setImage(goodGuys[0]->getBase()->getImage("up"));
                goodGuys[0]->frame++;
            }
            else if (goodGuys[0]->frame == 180)
            {
                goodGuys[0]->frame = 0;
            }
        }
        //Object collision detection
    
        if ((theEngine->spriteCollide(thePlayer, theObjects[0]) == 1) && theObjects[0]->getVisible())
        {
           thePlayer->setX(thePlayer->getOldX());
    	   thePlayer->setY(thePlayer->getOldY());
    	   
                if (audioflag)
                    theEngine->Sound->playEffect("data/sound/effects/mushroom.wav", "play", 0,0);
            
                    message(screen, "data/text/mushroom.data", thePlayer->getName());
                    theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Text_Done.wav", "play", 0,0);
    	            theObjects[0]->setVisible(false);
    	            thePlayer->addItem(13);
           
        }
        if ((theEngine->spriteCollide(thePlayer, theObjects[1]) == 1) && theObjects[1]->getVisible())
        {
           thePlayer->setX(thePlayer->getOldX());
    	   thePlayer->setY(thePlayer->getOldY());
    	
    	      if (audioflag)
                    theEngine->Sound->playEffect("data/sound/new_effects/LTTP_ItemFanfare_Stereo.wav", "play", 0,0);
            
               message(screen, "data/text/bow.data", thePlayer->getName());
               theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Text_Done.wav", "play", 0,0);
	           theObjects[1]->setVisible(false);
	           thePlayer->addItem(0);
	           thePlayer->setArrows(thePlayer->getArrows()+20);
        }
   }
   else if (level == 3)
   {
        
        if (!goodGuys.empty())
        {
             //Collision detection for Fleeing Woman
             if ((theEngine->spriteCollide(thePlayer, goodGuys[0]) == 1) && (goodGuys[0]->getVisible()))
             {
                  //Create message to tell Blink
                  thePlayer->setX(thePlayer->getOldX());
    	          thePlayer->setY(thePlayer->getOldY());
    	          message(screen, "data/text/woods.data", thePlayer->getName());
    	          if (audioflag)
    	              theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Text_Done.wav", "play", 0,0);
    	          theObjects[0]->setVisible(true);
    	
                  int location = goodGuys[0]->getY();
                  int location2 = goodGuys[0]->getX();
                  goodGuys[0]->frame = 0;
            
                  while(goodGuys[0]->getX() < location2+60)
                  {
                        goodGuys[0]->setX(goodGuys[0]->getX()+2);
                
                        if(goodGuys[0]->frame < 5)
                        {
                            goodGuys[0]->setImage(goodGuys[0]->getBase()->getImage("right"));
                            goodGuys[0]->frame++;
                        }
                        else if (goodGuys[0]->frame >= 5 && goodGuys[0]->frame < 10)
                        {
                             goodGuys[0]->setImage(goodGuys[0]->getBase()->getImage("right1"));
                             goodGuys[0]->frame++;
                        }
                        else if (goodGuys[0]->frame == 10)
                             goodGuys[0]->frame = 0;
            
                        dr.drawAll(theEngine, back, screen, thePlayer, badGuys, goodGuys, theObjects, screenInfo, theDoors, backX, backY, screenWidth, screenHeight, fonta, uItems);
                  }
                  location2 = goodGuys[0]->getX();
                  while(goodGuys[0]->getY() < (200+location))
                  {        
                      goodGuys[0]->setY(goodGuys[0]->getY()+2);
                
                      if(goodGuys[0]->frame < 5)
                      {
                          goodGuys[0]->setImage(goodGuys[0]->getBase()->getImage("down"));
                          goodGuys[0]->frame++;
                      }
                      else if (goodGuys[0]->frame >= 5 && goodGuys[0]->frame < 10)
                      {
                          goodGuys[0]->setImage(goodGuys[0]->getBase()->getImage("down1"));
                          goodGuys[0]->frame++;
                      }
                      else if (goodGuys[0]->frame == 10)
                          goodGuys[0]->frame = 0;
                    
                      dr.drawAll(theEngine, back, screen, thePlayer, badGuys, goodGuys, theObjects, screenInfo, theDoors, backX, backY, screenWidth, screenHeight, fonta, uItems);
            
                  }
                  location = goodGuys[0]->getY();
                  while(goodGuys[0]->getX() > location2-150)
                  {
                        goodGuys[0]->setX(goodGuys[0]->getX()-2);
                
                        if(goodGuys[0]->frame < 5)
                        {
                            goodGuys[0]->setImage(goodGuys[0]->getBase()->getImage("left"));
                            goodGuys[0]->frame++;
                        }
                        else if (goodGuys[0]->frame >= 5 && goodGuys[0]->frame < 10)
                        {
                             goodGuys[0]->setImage(goodGuys[0]->getBase()->getImage("left1"));
                             goodGuys[0]->frame++;
                        }
                        else if (goodGuys[0]->frame == 10)
                             goodGuys[0]->frame = 0;
            
                        dr.drawAll(theEngine, back, screen, thePlayer, badGuys, goodGuys, theObjects, screenInfo, theDoors, backX, backY, screenWidth, screenHeight, fonta, uItems);
                  }
                  location2 = goodGuys[0]->getX();
                  while(goodGuys[0]->getY() > (location-40))
                  {        
                      goodGuys[0]->setY(goodGuys[0]->getY()-2);
                
                      if(goodGuys[0]->frame < 5)
                      {
                          goodGuys[0]->setImage(goodGuys[0]->getBase()->getImage("up"));
                          goodGuys[0]->frame++;
                      }
                      else if (goodGuys[0]->frame >= 5 && goodGuys[0]->frame < 10)
                      {
                          goodGuys[0]->setImage(goodGuys[0]->getBase()->getImage("up1"));
                          goodGuys[0]->frame++;
                      }
                      else if (goodGuys[0]->frame == 10)
                          goodGuys[0]->frame = 0;
                    
                      dr.drawAll(theEngine, back, screen, thePlayer, badGuys, goodGuys, theObjects, screenInfo, theDoors, backX, backY, screenWidth, screenHeight, fonta, uItems);
            
                  }
                  while(goodGuys[0]->getX() > location2-350)
                  {
                        goodGuys[0]->setX(goodGuys[0]->getX()-2);
                
                        if(goodGuys[0]->frame < 5)
                        {
                            goodGuys[0]->setImage(goodGuys[0]->getBase()->getImage("left"));
                            goodGuys[0]->frame++;
                        }
                        else if (goodGuys[0]->frame >= 5 && goodGuys[0]->frame < 10)
                        {
                             goodGuys[0]->setImage(goodGuys[0]->getBase()->getImage("left1"));
                             goodGuys[0]->frame++;
                        }
                        else if (goodGuys[0]->frame == 10)
                             goodGuys[0]->frame = 0;
            
                        dr.drawAll(theEngine, back, screen, thePlayer, badGuys, goodGuys, theObjects, screenInfo, theDoors, backX, backY, screenWidth, screenHeight, fonta, uItems);
                  }
                  goodGuys.clear();
        
                  char direction = thePlayer->getDirection();
                  if(direction == 'N')
                  {
                       thePlayer->setY(thePlayer->getY()+1);
                  }
                  if(direction == 'S')
                  {
                       thePlayer->setY(thePlayer->getY()-1);
                  }
                  if(direction == 'W')
                  {
                      thePlayer->setX(thePlayer->getX()+1);
                  }
                  if(direction == 'E')
                  {
                      thePlayer->setX(thePlayer->getX()-1);
                  }
             }
        }
        
        if ((theEngine->spriteCollide(thePlayer, theObjects[0]) == 1) && theObjects[0]->getVisible())
        {
           thePlayer->setX(thePlayer->getOldX());
    	   thePlayer->setY(thePlayer->getOldY());
    	
                if (audioflag)
                    theEngine->Sound->playEffect("data/sound/effects/moonstone.wav", "play", 0,0);
            
                    message(screen, "data/text/courage.data", thePlayer->getName());
                    if (audioflag)
                         theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Text_Done.wav", "play", 0,0);
    	            theObjects[0]->setVisible(false);
    	            thePlayer->addItem(10);
        }
        if ((theEngine->spriteCollide(thePlayer, theObjects[1]) == 1) && theObjects[1]->getVisible())
        {
           thePlayer->setX(thePlayer->getOldX());
    	   thePlayer->setY(thePlayer->getOldY());
    	
                if (audioflag)
                    theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Get_HeartPiece.wav", "play", 0,0);
            
                    message(screen, "data/text/heartpiece.data", thePlayer->getName());
                    if (audioflag)
                        theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Text_Done.wav", "play", 0,0);
    	            theObjects[1]->setVisible(false);
    	            thePlayer->setPieces(thePlayer->getPieces()+1, screen);
    	            thePlayer->setCollected(1);
        }
   }
   else if (level == 53)
   {
        
        if (!goodGuys.empty())
        {
             if ((theEngine->spriteCollide(thePlayer, goodGuys[0]) == 1) && (goodGuys[0]->getVisible())&& (!theObjects[0]->getVisible()) && (!thePlayer->returnInventory()[11]->getVisible()))
             {
                  //Create message to tell Blink
                  thePlayer->setX(thePlayer->getOldX());
    	          thePlayer->setY(thePlayer->getOldY());
    	          message(screen, "data/text/fairy.data", thePlayer->getName());
    	          if (audioflag)
    	              theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Text_Done.wav", "play", 0,0);
    	          theObjects[0]->setVisible(true);  
             }             
   
        
        //animate fairy
            if(goodGuys[0]->frame < 100)
            {
                goodGuys[0]->setImage(goodGuys[0]->getBase()->getImage("down"));
                goodGuys[0]->frame++;
            }
            else if (goodGuys[0]->frame >= 100 && goodGuys[0]->frame < 120)
            {
                goodGuys[0]->setImage(goodGuys[0]->getBase()->getImage("down1"));
                goodGuys[0]->frame++;
            }
            else if (goodGuys[0]->frame == 120)
            {
                goodGuys[0]->frame = 0;
            }
        
        
        
        if ((theEngine->spriteCollide(thePlayer, theObjects[0]) == 1) && theObjects[0]->getVisible())
        {
           thePlayer->setX(thePlayer->getOldX());
    	   thePlayer->setY(thePlayer->getOldY());
    	
                if (audioflag)
                    theEngine->Sound->playEffect("data/sound/effects/moonstone.wav", "play", 0,0);
            
                    message(screen, "data/text/wisdom.data", thePlayer->getName());
                    theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Text_Done.wav", "play", 0,0);
    	            theObjects[0]->setVisible(false);
    	            thePlayer->addItem(11);
        }
        if ((theEngine->spriteCollide(thePlayer, theObjects[1]) == 1) && theObjects[1]->getVisible())
        {
           thePlayer->setX(thePlayer->getOldX());
    	   thePlayer->setY(thePlayer->getOldY());
    	
                if (audioflag)
                    theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Get_HeartPiece.wav", "play", 0,0);
            
                    message(screen, "data/text/heartpiece.data", thePlayer->getName());
                    if (audioflag)
                        theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Text_Done.wav", "play", 0,0);
    	            theObjects[1]->setVisible(false);
    	            thePlayer->setPieces(thePlayer->getPieces()+1, screen);
    	            thePlayer->setCollected(3);
        }
        if ((theEngine->spriteCollide(thePlayer, theObjects[2]) == 1))
        {
           thePlayer->setX(thePlayer->getOldX());
    	   thePlayer->setY(thePlayer->getOldY());
        }
     }
   }
   else if (level == 42)
   {
        
        if (!goodGuys.empty())
        {
             if ((theEngine->spriteCollide(thePlayer, goodGuys[0]) == 1) && (goodGuys[0]->getVisible()))
             {
                  //Create message to tell Blink
                  thePlayer->setX(thePlayer->getOldX());
    	          thePlayer->setY(thePlayer->getOldY());
    	          if((!theObjects[0]->getVisible()) && (!thePlayer->returnInventory()[1]->getVisible()))
    	          {
    	          message(screen, "data/text/uncle.data", thePlayer->getName());
    	          if (audioflag)
    	              theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Text_Done.wav", "play", 0,0);
    	          message(screen, "data/text/uncle1.data", thePlayer->getName());
    	          if (audioflag)
    	              theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Text_Done.wav", "play", 0,0);
    	          theObjects[0]->setVisible(true);  
                  }
             }             
        
        if ((theEngine->spriteCollide(thePlayer, theObjects[0]) == 1) && theObjects[0]->getVisible())
        {
           thePlayer->setX(thePlayer->getOldX());
    	   thePlayer->setY(thePlayer->getOldY());
    	
                if (audioflag)
                    theEngine->Sound->playEffect("data/sound/effects/moonstone.wav", "play", 0,0);
            
                    message(screen, "data/text/boomerang.data", thePlayer->getName());
                    if (audioflag)
                        theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Text_Done.wav", "play", 0,0);
    	            theObjects[0]->setVisible(false);
    	            thePlayer->addItem(1);
        }
     }
   }
   else if (level == 43)
   {        
        if (!goodGuys.empty())
        {
             if ((theEngine->spriteCollide(thePlayer, goodGuys[0]) == 1) && (goodGuys[0]->getVisible()))
             {
                  //Create message to tell Blink
                  thePlayer->setX(thePlayer->getOldX());
    	          thePlayer->setY(thePlayer->getOldY());
    	          if((!theObjects[0]->getVisible()) && (!thePlayer->returnInventory()[12]->getVisible()))
    	          {                
    	          message(screen, "data/text/king.data", thePlayer->getName());
    	          if (audioflag)
    	              theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Text_Done.wav", "play", 0,0);

    	          message(screen, "data/text/king1.data", thePlayer->getName());
    	          if (audioflag)
    	              theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Text_Done.wav", "play", 0,0);
    	          theObjects[0]->setVisible(true);  
    	          
                  
                  }
                  else if (goodGuys[2]->getVisible())
                  {
                     message(screen, "data/text/king2.data", thePlayer->getName());
                     if (audioflag)
    	                theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Text_Done.wav", "play", 0,0);  
    	             
    	             
    	             
    	             message(screen, "data/text/king3.data", thePlayer->getName());
    	             if (audioflag)
    	                  theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Text_Done.wav", "play", 0,0);  
                  }
             }        
             if ((theEngine->spriteCollide(thePlayer, goodGuys[2]) == 1) && (goodGuys[2]->getVisible()))
             {
                  //Create message to tell Blink
                  thePlayer->setX(thePlayer->getOldX());
    	          thePlayer->setY(thePlayer->getOldY());
    	          
    	          message(screen, "data/text/thanks.data", thePlayer->getName());
    	          if (audioflag)
    	               theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Text_Done.wav", "play", 0,0);
             }         
        
        if ((theEngine->spriteCollide(thePlayer, theObjects[0]) == 1) && theObjects[0]->getVisible())
        {
           thePlayer->setX(thePlayer->getOldX());
    	   thePlayer->setY(thePlayer->getOldY());
    	
                if (audioflag)
                    theEngine->Sound->playEffect("data/sound/effects/moonstone.wav", "play", 0,0);
            
                    message(screen, "data/text/power.data", thePlayer->getName());
                    if (audioflag)
                         theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Text_Done.wav", "play", 0,0);
    	            theObjects[0]->setVisible(false);
    	            thePlayer->addItem(12);
        }
     }
   }
   else if (level == 6)
   {
        if (!goodGuys.empty())
        {

        
        if ((theEngine->spriteCollide(thePlayer, goodGuys[0]) == 1) && (goodGuys[0]->getVisible()))
        {
            //Create message to tell Blink
            thePlayer->setX(thePlayer->getOldX());
    	    thePlayer->setY(thePlayer->getOldY());
    	    message(screen, "data/text/princess.data", thePlayer->getName());
    	    if (audioflag)
    	         theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Text_Done.wav", "play", 0,0);
    	
            int location = goodGuys[0]->getY();
            goodGuys[0]->frame = 0;
            
            while(goodGuys[0]->getY() < (500+location))
            {        
                goodGuys[0]->setY(goodGuys[0]->getY()+2);
                
                if(goodGuys[0]->frame < 5)
                {
                    goodGuys[0]->setImage(goodGuys[0]->getBase()->getImage("down"));
                    goodGuys[0]->frame++;
                }
                else if (goodGuys[0]->frame >= 5 && goodGuys[0]->frame < 10)
                {
                    goodGuys[0]->setImage(goodGuys[0]->getBase()->getImage("down1"));
                    goodGuys[0]->frame++;
                }
                else if (goodGuys[0]->frame == 10)
                    goodGuys[0]->frame = 0;
                    
                dr.drawAll(theEngine, back, screen, thePlayer, badGuys, goodGuys, theObjects, screenInfo, theDoors, backX, backY, screenWidth, screenHeight, fonta, uItems);
            
            }
            
            goodGuys[0]->setVisible(false);
            thePlayer->setProgress(100);
            
            char direction = thePlayer->getDirection();
            if(direction == 'N')
            {
                thePlayer->setY(thePlayer->getY()+1);
            }
            if(direction == 'S')
            {
                thePlayer->setY(thePlayer->getY()-1);
            }
            if(direction == 'W')
            {
                thePlayer->setX(thePlayer->getX()+1);
            }
            if(direction == 'E')
            {
                thePlayer->setX(thePlayer->getX()-1);
            }
    
        }         
        }
         
        if ((theEngine->spriteCollide(thePlayer, theObjects[0]) == 1) && theObjects[0]->getVisible())
        {
           thePlayer->setX(thePlayer->getOldX());
    	   thePlayer->setY(thePlayer->getOldY());
    	
                if (audioflag)
                    theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Get_HeartPiece.wav", "play", 0,0);
            
                    message(screen, "data/text/heartpiece.data", thePlayer->getName());
                if (audioflag)
                    theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Text_Done.wav", "play", 0,0);
                    
    	            theObjects[0]->setVisible(false);
    	            thePlayer->setPieces(thePlayer->getPieces()+1, screen);
    	            thePlayer->setCollected(2);
        }
   }
   else if (level == 52)
   {
      
        if ((theEngine->spriteCollide(thePlayer, theObjects[0]) == 1) && theObjects[0]->getVisible())
        {
           thePlayer->setX(thePlayer->getOldX());
    	   thePlayer->setY(thePlayer->getOldY());
    	
                if (audioflag)
                    theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Get_HeartPiece.wav", "play", 0,0);
            
                    message(screen, "data/text/heartpiece.data", thePlayer->getName());
                if (audioflag)
                    theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Text_Done.wav", "play", 0,0);
    	            theObjects[0]->setVisible(false);
    	            thePlayer->setPieces(thePlayer->getPieces()+1, screen);
    	            thePlayer->setCollected(0);
        }
   }
}

int level::message(SDL_Surface *screen, char* filename, string name)
{
    //Create message to tell Blink
    int ok = 1;
    SDL_Event event;
    SDL_PollEvent(&event);
    ok=1;
    
    
    SFont *font;  
    font = new SFont(IMG_Load("data/font/fontd.png")); 
        
    Message *m = new Message(filename, name);
    
    SDL_Rect dest;
    dest.x = 120;
    dest.y = 250;
    dest.w = 400;
    dest.h = 150;
    
    SDL_Surface *msg = m->DrawMessage(font);
    SDL_BlitSurface(msg, NULL, screen, &dest); 
    SDL_FreeSurface(msg);
        
    SDL_Flip(screen);

    while(ok > 0)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                   case SDL_KEYDOWN: 
                                           if((event.key.keysym.sym == SDLK_SPACE))
                                           {       
                                               ok =0;
                                           }
                                           break;
                                           
            }
        }
    }

    
    delete m;
    delete font;
    m = NULL;
    font = NULL;
    
    return 0;
}


void level::itemCode(SDL_Surface *screen, vector<spriteBase *> &itemBase, vector<Item *> &uItems)
{ 
     if (!uItems.empty())
             {
             for(unsigned int i=0; i < uItems.size(); i++)
		     {
		        
		        if (uItems[i]->getVisible())
		        {
		        uItems[i]->setIlife(uItems[i]->getIlife()+1);
		        
		        if (uItems[i]->getIlife() >400)
		        {
                        uItems[i]->setVisible(false);
                        uItems.erase(uItems.begin()+i);
                }
                }
		     }
       }     
}
