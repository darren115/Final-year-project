#include "orc.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265

orc::orc(int type, spriteBase *weaponBase)
{
    initArrows(weaponBase);   
    eType=type;           
    lastHit=0;
    mAction = 1;
}

orc::orc(int type)
{
    eType=type;                           
}


void orc::setDirection()
{
    if(mDirection == 'N')
    {
        if(frame < 10)
        {
            setImage(base->getImage("up"));
            frame++;
        }
        else if (frame >= 10 && frame < 20)
        {
            setImage(base->getImage("up1"));
            frame++;
        }
        else if (frame == 20)
        {
            setImage(base->getImage("up"));
            frame = 0;
        }
        
        setW(16);
        setH(28);
    }
        
    else if(mDirection == 'S')
    {
        if(frame < 10)
        {
            setImage(base->getImage("down"));
            frame++;
        }
        else if (frame >= 10 && frame < 20)
        {
            setImage(base->getImage("down1"));
            frame++;
        }
        else if (frame == 20)
        {
            setImage(base->getImage("down"));
            frame = 0;
        }

        setW(16);
        setH(28);
    }

    else if(mDirection == 'W')
    {
        if(frame < 10)
        {
            setImage(base->getImage("left"));
            frame++;
        }
        else if (frame >= 10 && frame < 20)
        {
            setImage(base->getImage("left1"));
            frame++;
        }
        else if (frame == 20)
        {
            setImage(base->getImage("left"));
            frame = 0;
        }
        
        setW(18);
        setH(28);
    }

    else if(mDirection == 'E')
    {
        if(frame < 10)
        {
            setImage(base->getImage("right"));
            frame++;
        }
        else if (frame >= 10 && frame < 20)
        {
            setImage(base->getImage("right1"));
            frame++;
        }
        else if (frame == 20)
        {
            setImage(base->getImage("right"));
            frame = 0;
        }
        
        setW(18);
        setH(28);
    }
}

int orc::loadDirections(char *filename)
{
    FILE *fp;
    char buffer[255];
    char dir;
    int dis;
    int count = 0;

    if((fp=fopen(filename, "r")) == NULL)
    {
        printf("Error opening file %s\n", filename);
        return -1;
    }
    while(!feof(fp))
    {
        fgets(buffer, 255, fp);
        sscanf(buffer, "MV: %s %d", &dir, &dis);
        mtheDirection.push_back(dir);
        mtheDistance.push_back(dis);
        count++;
    }
    mtheDirection.pop_back();
    mtheDistance.pop_back();

    mCurrentPos = 0; //Current Posistion in the array
    mDistance =0; //Distance moved so far

    return 0;
}

void orc::patrol()
{
    if (mAction == 3)
    {
        if (lastHit<80)       
           lastHit++;
        else 
        {
            mAction=2;
            lastHit=0;
        }
    }
    else
    { 
    mDirection = mtheDirection[mCurrentPos]; //Set the direction to what it should be
    setDirection();

    if(mDistance > mtheDistance[mCurrentPos]) //If the object has walked the full distance we increment the
        //position in the array
    {
        if(mCurrentPos < mtheDirection.size()-1)  //size of the array
        {
            mCurrentPos++;
        }else
        {
            mCurrentPos=0;
        }
        mDirection = mtheDirection[mCurrentPos];
        mDistance = 0;
    }
    else
    {					//Else we move the object in the correct direction
        if(mDirection == 'N')
        {
            mY--;            
        }
        else if(mDirection == 'S')
        {
            mY++;
        }
        else if(mDirection == 'W')
        {
            mX--;
        }
        else if(mDirection == 'E')
        {
            mX++;
        }
        mDistance++;  //Increment the distance the object has moved
    }
    }
}

int orc::look(int objectX, int objectY)
{
    //Note the man tan, sin, and cos functions use radians rather than
    //degrees 360 degrees = 2*PI radians.
    
    if (mAction != 3)
    {
    double adj; //Adjcent or distance between orc and object
    double opp; //Opposite

    if(mDirection == 'N')
    {
        if((objectY >= (mY-mVisionLength)) && (objectY < mY))
        {
            adj=mY-objectY;
            opp=(adj/tan(mVisionRange*PI/180));

            if((objectX >= mX-opp) && (objectX <= mX+opp))
            {
                //attack attack
                mAction = 2;
            }
        }
    }
    else if(mDirection == 'S')
    {
        if((objectY <= (mY+mVisionLength)) && (objectY > mY))
        {
            adj=objectY-mY;
            opp=(adj/tan(mVisionRange*PI/180));

            if((objectX >= mX-opp) && (objectX <= mX+opp))
            {
                //attack attack
                mAction = 2;
            }
        }
    }
    else if(mDirection == 'W')
    {
        if((objectX >=(mX-mVisionLength)) && (objectX < mX))
        {
            adj=mX-objectX;
            opp=(adj/tan(mVisionRange*PI/180));

            if((objectY >= mY-opp) && (objectY <=mY+opp))
            {
                //attack attack
                mAction = 2;
            }
        }
    }
    else if(mDirection == 'E')
    {
        if((objectX <= (mX+mVisionLength)) && (objectX > mX))
        {
            adj=objectX-mX;
            opp=(adj/tan(mVisionRange*PI/180));

            if((objectY >= mY-opp) && (objectY <= mY+opp))
            {
                //attack attack
                mAction = 2;
            }
        }
    }
    }
    return 0;
    
}


void orc::attack(int objectX, int objectY, int mapX, int mapY, int tileWidth, int tileHeight, std::vector< std::vector <int> > &theMap)
{
    
    if (eType==1)
    {
        bowAttack(objectX, objectY, mapX, mapY, tileWidth, tileHeight, theMap);
    }
    else
    {
        normalAttack(objectX, objectY, mapX, mapY, tileWidth, tileHeight, theMap);
    }
    setDirection();
    
    int x;
    int y;
    
    if (objectX > mX)
    x = objectX - mX;
    else
    x = mX - objectX;
    
    if (objectY > mY)
    y = objectY - mY;
    else
    y = mY - objectY;
    
    
    if (x>200 || y>200)
        mAction = 1;

}

void orc::normalAttack(int objectX, int objectY, int mapX, int mapY, int tileWidth, int tileHeight, std::vector< std::vector <int> > &theMap)
{
    if(objectX < mX)
    {
        mX--;
        int j=((mapY-getY()-getH()+1)/tileHeight);
        int k=((mapX-getX())/tileWidth);
        //Changed for new tiles
        if(!((theMap[-j][-k] == 0) || (theMap[-j][-k] == 10) || (theMap[-j][-k] == 19) || (theMap[-j][-k] == 77) || (theMap[-j][-k] == 158) || (theMap[-j][-k] == 260) || (theMap[-j][-k] == 261) || (theMap[-j][-k] == 264) || (theMap[-j][-k] == 265) || (theMap[-j][-k] == 338) || ((theMap[-j][-k] >= 215) && (theMap[-j][-k] <= 219)) || ((theMap[-j][-k] >= 297) && (theMap[-j][-k] <= 303))))
        {
            mX++;
        }

        if(objectY > mY)
        {
            //Test For Collision
            mY++;
            int j=((mapY-getY()-getH()+1)/tileHeight);
            int k=((mapX-getX())/tileWidth);
            //Changed for new tiles
            if(!((theMap[-j][-k] == 0) || (theMap[-j][-k] == 10) || (theMap[-j][-k] == 19) || (theMap[-j][-k] == 77) || (theMap[-j][-k] == 158) || (theMap[-j][-k] == 260) || (theMap[-j][-k] == 261) || (theMap[-j][-k] == 264) || (theMap[-j][-k] == 265) || (theMap[-j][-k] == 338) || ((theMap[-j][-k] >= 215) && (theMap[-j][-k] <= 219)) || ((theMap[-j][-k] >= 297) && (theMap[-j][-k] <= 303))))
            {
                mY--;	
            }
            else
            {
                mDirection='S';
            }
        }

        else if(objectY < mY)
        {
            //Test for Collision		
            mY--;	  
            int j=((mapY-getY()-getH()+1)/tileHeight);
            int k=((mapX-getX())/tileWidth);
            //Changed for new tiles
            if(!((theMap[-j][-k] == 0) || (theMap[-j][-k] == 10) || (theMap[-j][-k] == 19) || (theMap[-j][-k] == 77) || (theMap[-j][-k] == 158) || (theMap[-j][-k] == 260) || (theMap[-j][-k] == 261) || (theMap[-j][-k] == 264) || (theMap[-j][-k] == 265) || (theMap[-j][-k] == 338) || ((theMap[-j][-k] >= 215) && (theMap[-j][-k] <= 219)) || ((theMap[-j][-k] >= 297) && (theMap[-j][-k] <= 303))))
            {
                mY++;	
            }
            else
            {
                mDirection='N';
            }  
        }
        
        mDirection='W';
    }
    
    else if(objectX > mX)
    {
        mX++;
        int j=((mapY-getY()-getH()+1)/tileHeight);
        int k=((mapX-getX())/tileWidth);
        //Changed for new tiles
        if(!((theMap[-j][-k] == 0) || (theMap[-j][-k] == 10) || (theMap[-j][-k] == 19) || (theMap[-j][-k] == 77) || (theMap[-j][-k] == 158) || (theMap[-j][-k] == 260) || (theMap[-j][-k] == 261) || (theMap[-j][-k] == 264) || (theMap[-j][-k] == 265) || (theMap[-j][-k] == 338) || ((theMap[-j][-k] >= 215) && (theMap[-j][-k] <= 219)) || ((theMap[-j][-k] >= 297) && (theMap[-j][-k] <= 303))))
        {
            mX--;
        }
        if(objectY > mY)
        {
            //Test For Collision
            mY++;
            int j=((mapY-getY()-getH()+1)/tileHeight);
            int k=((mapX-getX())/tileWidth);
            //Changed for new tiles
            if(!((theMap[-j][-k] == 0) || (theMap[-j][-k] == 10) || (theMap[-j][-k] == 19) || (theMap[-j][-k] == 77) || (theMap[-j][-k] == 158) || (theMap[-j][-k] == 260) || (theMap[-j][-k] == 261) || (theMap[-j][-k] == 264) || (theMap[-j][-k] == 265) || (theMap[-j][-k] == 338) || ((theMap[-j][-k] >= 215) && (theMap[-j][-k] <= 219)) || ((theMap[-j][-k] >= 297) && (theMap[-j][-k] <= 303))))
            {
                mY--;	
            }
            else
            {
                mDirection='S';
            }
        }
        else if(objectY < mY)
        {
            //Test for Collision		
            mY--;	  
            int j=((mapY-getY()-getH()+1)/tileHeight);
            int k=((mapX-getX())/tileWidth);
            //Changed for new tiles
            if(!((theMap[-j][-k] == 0) || (theMap[-j][-k] == 10) || (theMap[-j][-k] == 19) || (theMap[-j][-k] == 77) || (theMap[-j][-k] == 158) || (theMap[-j][-k] == 260) || (theMap[-j][-k] == 261) || (theMap[-j][-k] == 264) || (theMap[-j][-k] == 265) || (theMap[-j][-k] == 338) || ((theMap[-j][-k] >= 215) && (theMap[-j][-k] <= 219)) || ((theMap[-j][-k] >= 297) && (theMap[-j][-k] <= 303))))
            {
                mY++;	
            }
            else
            {
                mDirection='N';
            }  
        }
    
        mDirection='E';
    }

    else if(objectY < mY)
    {
        mY--;
        if(objectX > mX)
        {
            mX++;
            int j=((mapY-getY()-getH()+1)/tileHeight);
            int k=((mapX-getX())/tileWidth);
            //Changed for new tiles
            if(!((theMap[-j][-k] == 0) || (theMap[-j][-k] == 10) || (theMap[-j][-k] == 19) || (theMap[-j][-k] == 77) || (theMap[-j][-k] == 158) || (theMap[-j][-k] == 260) || (theMap[-j][-k] == 261) || (theMap[-j][-k] == 264) || (theMap[-j][-k] == 265) || (theMap[-j][-k] == 338) || ((theMap[-j][-k] >= 215) && (theMap[-j][-k] <= 219)) || ((theMap[-j][-k] >= 297) && (theMap[-j][-k] <= 303))))
            {
                mX--;
            }
            else
            {
                mDirection='E';
            }
            
        }
        else if(objectX < mX)
        {
            mX--;
            int j=((mapY-getY()-getH()+1)/tileHeight);
            int k=((mapX-getX())/tileWidth);
            //Changed for new tiles
            if(!((theMap[-j][-k] == 0) || (theMap[-j][-k] == 10) || (theMap[-j][-k] == 19) || (theMap[-j][-k] == 77) || (theMap[-j][-k] == 158) || (theMap[-j][-k] == 260) || (theMap[-j][-k] == 261) || (theMap[-j][-k] == 264) || (theMap[-j][-k] == 265) || (theMap[-j][-k] == 338) || ((theMap[-j][-k] >= 215) && (theMap[-j][-k] <= 219)) || ((theMap[-j][-k] >= 297) && (theMap[-j][-k] <= 303))))
            {
            mX++;
            }
            else
            {
                mDirection='W';
            }
        }
        
        mDirection='N';
    }
    
    else if(objectY > mY)
    {
        mY++;
        if(objectX > mX)
        {
            mX++;
            int j=((mapY-getY()-getH()+1)/tileHeight);
            int k=((mapX-getX())/tileWidth);
            //Changed for new tiles
            if(!((theMap[-j][-k] == 0) || (theMap[-j][-k] == 10) || (theMap[-j][-k] == 19) || (theMap[-j][-k] == 77) || (theMap[-j][-k] == 158) || (theMap[-j][-k] == 260) || (theMap[-j][-k] == 261) || (theMap[-j][-k] == 264) || (theMap[-j][-k] == 265) || (theMap[-j][-k] == 338) || ((theMap[-j][-k] >= 215) && (theMap[-j][-k] <= 219)) || ((theMap[-j][-k] >= 297) && (theMap[-j][-k] <= 303))))
            {
                mX--;
            }
            else
            {
                mDirection='E';
            }
        }
        else if(objectX < mX)
        {
            mX--;
            int j=((mapY-getY()-getH()+1)/tileHeight);
            int k=((mapX-getX())/tileWidth);
            //Changed for new tiles
            if(!((theMap[-j][-k] == 0) || (theMap[-j][-k] == 10) || (theMap[-j][-k] == 19) || (theMap[-j][-k] == 77) || (theMap[-j][-k] == 158) || (theMap[-j][-k] == 260) || (theMap[-j][-k] == 261) || (theMap[-j][-k] == 264) || (theMap[-j][-k] == 265) || (theMap[-j][-k] == 338) || ((theMap[-j][-k] >= 215) && (theMap[-j][-k] <= 219)) || ((theMap[-j][-k] >= 297) && (theMap[-j][-k] <= 303))))
            {
                mX++;
            }
            else
            {
                mDirection='W';
            }
        }
        
        mDirection='S';
    }
}


void orc::bowAttack(int objectX, int objectY, int mapX, int mapY, int tileWidth, int tileHeight, std::vector< std::vector <int> > &theMap)
{
    if(objectX+60 < mX)
    {
        mX--;
        int j=((mapY-getY()-getH()+1)/tileHeight);
        int k=((mapX-getX())/tileWidth);
        //Changed for new tiles
        if(!((theMap[-j][-k] == 0) || (theMap[-j][-k] == 10) || (theMap[-j][-k] == 19) || (theMap[-j][-k] == 77) || (theMap[-j][-k] == 158) || (theMap[-j][-k] == 260) || (theMap[-j][-k] == 261) || (theMap[-j][-k] == 264) || (theMap[-j][-k] == 265) || (theMap[-j][-k] == 338) || ((theMap[-j][-k] >= 215) && (theMap[-j][-k] <= 219)) || ((theMap[-j][-k] >= 297) && (theMap[-j][-k] <= 303))))
        {
            mX++;
        } 
    }  
    else if((objectX+60 > mX) && (objectX < mX) && ((mDirection=='E') || (mDirection=='W')))
    {
        mX++;
        int j=((mapY-getY()-getH()+1)/tileHeight);
        int k=((mapX-getX()+30)/tileWidth);
        //Changed for new tiles
        if(!((theMap[-j][-k] == 0) || (theMap[-j][-k] == 10) || (theMap[-j][-k] == 19) || (theMap[-j][-k] == 77) || (theMap[-j][-k] == 158) || (theMap[-j][-k] == 260) || (theMap[-j][-k] == 261) || (theMap[-j][-k] == 264) || (theMap[-j][-k] == 265) || (theMap[-j][-k] == 338) || ((theMap[-j][-k] >= 215) && (theMap[-j][-k] <= 219)) || ((theMap[-j][-k] >= 297) && (theMap[-j][-k] <= 303))))
        {
            mX--;
        } 
    }    
    else if(objectX-60 > mX)
    {
        mX++;
        int j=((mapY-getY()-getH()+1)/tileHeight);
        int k=((mapX-getX()+30)/tileWidth);
        //Changed for new tiles
        if(!((theMap[-j][-k] == 0) || (theMap[-j][-k] == 10) || (theMap[-j][-k] == 19) || (theMap[-j][-k] == 77) || (theMap[-j][-k] == 158) || (theMap[-j][-k] == 260) || (theMap[-j][-k] == 261) || (theMap[-j][-k] == 264) || (theMap[-j][-k] == 265) || (theMap[-j][-k] == 338) || ((theMap[-j][-k] >= 215) && (theMap[-j][-k] <= 219)) || ((theMap[-j][-k] >= 297) && (theMap[-j][-k] <= 303))))
        {
            mX--;
        }
    }
    else if((objectX-60 < mX) && (objectX > mX) && ((mDirection=='E') || (mDirection=='W')))
    {
        mX--;
        int j=(((mapY-getY()-getH()+1)/tileHeight));
        int k=((mapX-getX()-30)/tileWidth);
        //Changed for new tiles
        if(!((theMap[-j][-k] == 0) || (theMap[-j][-k] == 10) || (theMap[-j][-k] == 19) || (theMap[-j][-k] == 77) || (theMap[-j][-k] == 158) || (theMap[-j][-k] == 260) || (theMap[-j][-k] == 261) || (theMap[-j][-k] == 264) || (theMap[-j][-k] == 265) || (theMap[-j][-k] == 338) || ((theMap[-j][-k] >= 215) && (theMap[-j][-k] <= 219)) || ((theMap[-j][-k] >= 297) && (theMap[-j][-k] <= 303))))
        {
            mX++;
        }
    }
    else if(objectY+60 < mY)
    {
        mY--;  
        int j=(((mapY-getY()-getH()+1)/tileHeight));
        int k=((mapX-getX())/tileWidth);
        //Changed for new tiles
        if(!((theMap[-j][-k] == 0) || (theMap[-j][-k] == 10) || (theMap[-j][-k] == 19) || (theMap[-j][-k] == 77) || (theMap[-j][-k] == 158) || (theMap[-j][-k] == 260) || (theMap[-j][-k] == 261) || (theMap[-j][-k] == 264) || (theMap[-j][-k] == 265) || (theMap[-j][-k] == 338) || ((theMap[-j][-k] >= 215) && (theMap[-j][-k] <= 219)) || ((theMap[-j][-k] >= 297) && (theMap[-j][-k] <= 303))))
        {
            mY++;
        }
    }
    else if((objectY+60 > mY) && (objectY < mY) && ((mDirection=='N') || (mDirection=='S')))
    {
        mY++;  
        int j=(((mapY-getY()-getH()+1)/tileHeight));
        int k=((mapX-getX())/tileWidth);
        //Changed for new tiles
        if(!((theMap[-j][-k] == 0) || (theMap[-j][-k] == 10) || (theMap[-j][-k] == 19) || (theMap[-j][-k] == 77) || (theMap[-j][-k] == 158) || (theMap[-j][-k] == 260) || (theMap[-j][-k] == 261) || (theMap[-j][-k] == 264) || (theMap[-j][-k] == 265) || (theMap[-j][-k] == 338) || ((theMap[-j][-k] >= 215) && (theMap[-j][-k] <= 219)) || ((theMap[-j][-k] >= 297) && (theMap[-j][-k] <= 303))))
        {
            mY--;
        }
    }  
    else if(objectY-60 > mY)
    {
        mY++;
        int j=(((mapY-getY()-getH()+1)/tileHeight));
        int k=((mapX-getX())/tileWidth);
        //Changed for new tiles
        if(!((theMap[-j][-k] == 0) || (theMap[-j][-k] == 10) || (theMap[-j][-k] == 19) || (theMap[-j][-k] == 77) || (theMap[-j][-k] == 158) || (theMap[-j][-k] == 260) || (theMap[-j][-k] == 261) || (theMap[-j][-k] == 264) || (theMap[-j][-k] == 265) || (theMap[-j][-k] == 338) || ((theMap[-j][-k] >= 215) && (theMap[-j][-k] <= 219)) || ((theMap[-j][-k] >= 297) && (theMap[-j][-k] <= 303))))
        {
            mY--;
        }
    }
    else if((objectY-60 < mY) && (objectY > mY) && ((mDirection=='N') || (mDirection=='S')))
    {
        mY--;
        int j=(((mapY-getY()-getH()+1)/tileHeight));
        int k=((mapX-getX())/tileWidth);
        //Changed for new tiles
        if(!((theMap[-j][-k] == 0) || (theMap[-j][-k] == 10) || (theMap[-j][-k] == 19) || (theMap[-j][-k] == 77) || (theMap[-j][-k] == 158) || (theMap[-j][-k] == 260) || (theMap[-j][-k] == 261) || (theMap[-j][-k] == 264) || (theMap[-j][-k] == 265) || (theMap[-j][-k] == 338) || ((theMap[-j][-k] >= 215) && (theMap[-j][-k] <= 219)) || ((theMap[-j][-k] >= 297) && (theMap[-j][-k] <= 303))))
        {
            mY++;
        }
    }

    
    if (((objectX > mX) && (objectX <= mX+mW)) && (objectY>=mY))
    {
         mDirection='S';
    }
    else if (((objectX > mX)&& (objectX <= mX+mW)) && (objectY<=mY))
    {
         mDirection='N';
    }
    else if (((objectY > mY)&& (objectY <= mY+mH)) && (objectX>=mX))
    {
         mDirection='E';
    }
    else if (((objectY > mY)&& (objectY <= mY+mH)) && (objectX<=mX))
    {
         mDirection='W';
    }   
    
    
    
        if (((mDirection=='S') && ((objectX > mX)&& (objectX < mX+mW)) && (objectY>mY))
        || ((mDirection=='N') && ((objectX > mX)&& (objectX < mX+mW)) && (objectY<mY))
        || ((mDirection=='E') && ((objectY > mY)&& (objectY < mY+mH)) && (objectX>mX))
        || ((mDirection=='W') && ((objectY > mY) && (objectY < mY+mH)) && (objectX<mX)))
        
        fireArrow(mScreen, mX, mY, mW, mH, mDirection);
    }

