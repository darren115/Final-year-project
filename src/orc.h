#ifndef ORC_H
#define ORC_H

#include "boworc.h"
#include "sprite.h"
#include <stdlib.h>
#include <vector>

using std::vector;

///Class extending sprite to represent an orc/enemy.  
class orc : public sprite, boworc
{
public:
    
    
    orc(int, spriteBase*);
    
    orc(int type);
    
    ///sets mDirection
    void setDirection(char direction)
    {
        mDirection = direction;
    }
    
    ///sets mDistance
    void setDistance(int distance)
    {
        mDistance = distance;
    }
    
    ///sets mCurrentPos
    void setCurrentPos(int pos)
    {
        mCurrentPos = pos;
    }
    
    ///sets mLife
    void setLife(int life)
    {
        mLife = life;
    }
    
    ///sets the direction
    void setDirection();
    
    ///sets mVisionLength
    void setVision(int length)
    {
        mVisionLength = length;
    }
    
    ///sets mVisionRange
    void setRange(int range)
    {
        mVisionRange = range;
    }
    
    ///sets mAction
    void setAction(int action)
    {
        mAction = action;
    }

    ///returns mDirection
    char getDirection()
    {
        return mDirection;
    }
    
    ///returns mDistance
    int getDistance()
    {
        return mDistance;
    }
    
    ///returns mCurrentPos
    int getCurrentPos()
    {
        return mCurrentPos;
    }
    
    ///returns mLife
    int getLife()
    {
        return mLife;
    }
    
    ///returns mVisionLength
    int getVision()
    {
        return mVisionLength;
    }
    
    ///returns mVisionRange
    int getRange()
    {
        return mVisionRange;
    }
    
    ///returns mAction
    int getAction()
    {
        return mAction;
    }
    
    ///loads the directions from a file
    int loadDirections(char *filename);

    ///calculates the movements and directions and moves the orc ina patrol
    void patrol();
    
    ///looks for the player
    int look(int x, int y);
    
    
    ///attacks the player
    void attack(int objectX, int objectY, int mapX, int mapY, int tileWidth, int tileHeight, std::vector< std::vector <int> > &theMap);
    

    ///returns type of enemy
    int getEType()
    {
        return eType;
    }
    
    //Returns all of the arrows
    vector<sprite *>& getWeapon()
    {
        return getArrows();
    }
    
    //Sets the number of cycles since the last arrow was fired
    void setDiff(int time)
    {
         setTimeDiff(time);
    }

    int getDiff()
    {
         return getTimeDiff();
    }

    
private:
    
    ///Moves the enemy closer to the player
    void normalAttack(int objectX, int objectY, int mapX, int mapY, int tileWidth, int tileHeight, std::vector< std::vector <int> > &theMap);
    
    ///moves the enemy within a distance of the player and moves the enemy away from the player if it is too close
    void bowAttack(int objectX, int objectY, int mapX, int mapY, int tileWidth, int tileHeight, std::vector< std::vector <int> > &theMap);
    
    ///the current direction the sprite is facing
    char mDirection;
    
    ///how for the sprite has moved 
    int mDistance; 
    
    ///position to read from in array
    int mCurrentPos; 
    
    ///the number of lives the orc has
    int mLife;
    
    ///the action the orc is performing
    int mAction;
    
    ///how far can the orc see
    int mVisionLength;  
    
    ///the angle of vision
    int mVisionRange; 
    
    ///vector of directions
    vector<char> mtheDirection;
    
    ///vector of distances
    vector<int> mtheDistance;
    
    ///type of enemy
    int eType;
    
    ///time since enemy was last hit
    int lastHit;
    

};
#endif //ORC_H
