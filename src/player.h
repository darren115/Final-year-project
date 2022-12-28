#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include "sprite.h"
#include <vector>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Item.h"
#include "Font.cpp"
#include "collision.h"


using std::vector;
using std::string;

///class extending sprite to represent the player
class player : public sprite, public collision
{
public:
    
    ///constructor    
    player(vector<spriteBase *>, SDL_Surface *, int, int, int, int, spriteBase *, spriteBase *);
    
    ///sets mLife
    void setLife(int life)
    {
        mLife = life;
        setLifeIcon(life);
    }
    
    ///returns mLife
    int getLife()
    {
        return mLife;
    }
    
    ///sets total hearts
    void setHearts(int hearts, SDL_Surface *screen, int w, int h)
    {
         playerLife.resize(hearts);     
         for (unsigned int i=(tHearts); i<hearts;i++)
         {
             initLifeIcon(i, screen, w, h);
         }         
        tHearts = hearts;
        
    }
    
    ///returns total number of Hearts
    int getHearts()
    {
        return tHearts;
    }
    
    ///sets progress through the game
    void setProgress(int prog)
    {
        progress = prog;
    }
    
    ///gets progress through the game
    int getProgress()
    {
        return progress;
    }
    
    ///sets name
    void setName(string nam)
    {
        name = nam;
    }
    
    ///gets name
    string getName()
    {
        return name;
    }
    
    //sets the total number of rupees
    void setRupees(int rup)
    {
        rupees = rup;
    }
    
    ///gets the total number of rupees
    int getRupees()
    {
        return rupees;
    }
    
    //sets the total number of bombs
    void setBombs(int bom)
    {
        mbombs = bom;
    }
    
    ///gets the total number of bombs
    int getBombs()
    {
        return mbombs;
    }
    
    //sets the total number of arrows
    void setArrows(int arr)
    {
        marrows = arr;
    }
    
    ///gets the total number of arrows
    int getArrows()
    {
        return marrows;
    }
    
    //sets the number of heart pieces
    //if the number reaches 4 it increments the players life bar
    // it also then sets the number of heart pieces back to 0
    void setPieces(int piece, SDL_Surface *screen)
    {
        if (piece<4) 
        hPieces = piece;
        else
        {
            hPieces=0;
            setHearts(tHearts+1, screen, 17, 24);
            setLife(tHearts);            
        }
    }
    
    ///gets the total number of heart pieces
    int getPieces()
    {
        return hPieces;
    }
    
    ///sets mSpeed
    void setSpeed(int speed)
    {
        mSpeed = speed;
    }
    
    ///sets mSpeed
    int getSpeed()
    {
        return mSpeed;
    }
    
    ///returns theArrows
    vector<sprite *>& getWeapon()
    {
        return theArrows;
    }
    
    ///returns the sprite representing a sword slash
    sprite *& getSlashes()
    {
        return theSlashes;
    }
    
    ///returns the sprite representing a sword slash
    sprite *& getLamp()
    {
        return theLamp;
    }
    
    ///returns a vector containing the playerLife
    vector<sprite *>& getLifeIcon()
    {
        return playerLife;
    }
    
    ///automatically changes the life icons to the correct colour based on the players life
    void setLifeIcon(int life);

    
    ///moves the player
    void move(Uint8 *keys, int &backX, int &mapX, int &xOffset, int &backY, int &mapY, int &yOffset, int screenWidth, int screenHeight, int levelWidth, int levelHeight, int tileWidth, int tileHeight, vector< vector <int> > &theMap);
    
    ///fires an arrow
    void fireArrow();
    
    ///Initiates a sword slash
    void slash();
    
        ///Initiates a sword slash
    void lamp();
    
    ///sets mDeathTime
    void setDeathTime(int time)
    {
        mDeathTime = time;
    }
    
    ///returns mDeathTime
    int getDeathTime()
    {
        return mDeathTime;
    }
    
    ///sets mScore
    void setScore(int score)
    {
        mScore = score;
    }
    
    ///returns mScore
    int getScore()
    {
        return mScore;
    }
    
    ///sets mMagic
    void setMagic(int magic)
    {
        mMagic = magic;
    }
    
    ///returns mMagic
    int getMagic()
    {
        return mMagic;
    }
            
    ///adds an item to the player's inventory    
    //return 1 if error, else 0
    int addItem(int i)
    {
        if (mInv[i]->getVisible()==false)
        {
            mInv[i]->setVisible(true);
            return 0;
        }
        else
            return 1;
    }
    
    //Fills the inventory with all of the possible items
    void buildInventory(vector<Item *> theInventory)
    {
         for (int i=0; i<14; i++)
         {
             mInv.push_back(theInventory[i]);
         }
    }
    
    //Returns all of the items within the inventory
    vector<Item *> returnInventory()
    {
        return mInv;
    }
    
    //Returns all of the items within the inventory
    void selectItem(int index)
    {
        for (int i=0; i<6; i++)
        {
            mInv[i]->select(false);
        } 
        mInv[index]->select(true);
    }
    
    ///returns the image for the item in the inventory at i
    SDL_Surface* getInvImage (int i)
    {
        return mInv[i]->getImage();
    }

    ///Draws the inventory to a surface.  It draws the inventory to a surface and reads the inventory 
    ///items form the player class.  It retrieves the items name and image and displays this information 
    ///inside the Inventory.  
    SDL_Surface* drawInventory(); 
    
    //returns the amount of cycles since the last slash
    int getSlashTime()
    {
        return slashTime;
    }  
    
    //sets the amount of cycles since the last slash
    void setSlashTime(int time)
    {
         slashTime=time;
    }  
    
    //returns the amount of cycles since the last slash
    int getLampTime()
    {
        return lampTime;
    }  
    
    //sets the amount of cycles since the last slash
    void setLampTime(int time)
    {
         lampTime=time;
    } 
    
    //creates a new boomerang in the direction of the player
    //also sets the start location of and changes the value of boomHeld
    void boomerang();
    
    ///returns the sprite for the boomerang
    sprite *& getBoomerang()
    {
        return theBoomerang;
    }
    
    //deletes the boomerang and changes boomHeld to true
    void setHeld()
    {
         delete theBoomerang;
         theBoomerang = NULL;
         boomHeld=true;
    }
    
    //returnes the value of boomHeld
    bool getHeld()
    {
         return boomHeld;
    }
    
    //changes the value of boomReturn to true
    void setReturn()
    {
        boomReturn=true;
    }
    
    //returns the vale of slashing which indicates wether the sword is in use
    bool getSlashing()
    {
         return slashing;
    }
    
    //returns the vale of slashing which indicates wether the sword is in use
    bool getLampUse()
    {
         return lampUse;
    }
    
    //returns the vale of slashing which indicates wether the sword is in use
    void setLampUse(bool val)
    {
         lampUse = val;
    }
    //Moves the position of the boomerang closer to the player
    void boomerangMove(int mapX, int mapY, int tileWidth, int tileHeight, std::vector< std::vector <int> > &theMap);
     
    //Draws the current magic level to the screen 
    SDL_Surface* drawMagic();
    
    //Calculates which animation frame to display for the player 
    void determineFrame(int modifier, int endframe);
    
    //Sets which heart has been collected
    void setCollected(int level)
    {
         colHearts[level] = true;
    }
    
    //Returns wether or not a heart has been collected on a specific level
    bool getCollected(int level)
    {
         return colHearts[level];
    }

protected:
                  
    //Initialises a life icon to a specific position
    // used when increasing the total number of hearts
    void initLifeIcon(int life, SDL_Surface *screen, int w, int h);      
                   
    ///player's inventory
    vector<Item *> mInv;      
          
    ///player's name
    string name;
    
    ///player's amount of magic
    int mMagic;
    
    ///player's number of heart pieces
    int hPieces;
          
    ///player's number of rupees
    int rupees;
    
    ///player's number of arrows
    int marrows;
    
    ///player's players number of bombs
    int mbombs;
    
    ///player's current progress through the game
    int progress;
    
    ///player's total number of possible life hearts
    int tHearts;
    
    ///The current row that hearts have been drawn on (is used when adding additional hearts)
    int row;
    
    ///The location of the hearts on a row
    int location;
    
    ///The yLocation of the hearts on a row
    int yLoc;
    
    ///player's life
    int mLife;

    ///player's speed
    int mSpeed;
    
    ///player's score
    int mScore;
    
    ///player's arrows
    vector<sprite *> theArrows;
    
    ///player's life images
    vector<sprite *> playerLife;
        
    ///spriteBase for the arrows 
    spriteBase *arrowBase;
    
    ///spriteBase for the boomerang 
    spriteBase *boomerangBase;
    
    ///player's deathtime
    int mDeathTime;
    
    //Time since last slash of the sword, used to time out the null sprite used for collision
    int slashTime; 
    
    //Time since last slash of the sword, used to time out the null sprite used for collision
    int lampTime; 
    
    //Boolean used to determine whether the player is holding the boomerang 
    bool boomHeld;
    
    //Boolean used to determine whether the boomerang is moving away or returning to the player
    bool boomReturn;
    
    //Start position of the boomerang used to determine distance it has travelled
    int startX;
    
    //Start position of the boomerang used to determine distance it has travelled
    int startY;
    
    //The current boomerang image, used to draw
    sprite * theBoomerang;
        
    //The null sword slash image used for collision detection    
    sprite * theSlashes;
    
    //The null sword slash image used for collision detection    
    sprite * theLamp;
        
    //Vector of all of the possible sets of player images
    vector<spriteBase *> theBases;
    
    //Booleane used to determine wether the player is moving or slashing their sword
    bool slashing;
    
    //Booleane used to determine wether the player is moving or slashing their sword
    bool lampUse;
    
    //Used to determine which frame of a sword slash to draw
    int sframe;
    
    //Used to determine which sprite base to use (weapon specific collection of sprites)
    int lastWeapon;
    
    //Vector of all of the heart pieces that the player has collected
    vector<bool > colHearts;
};
#endif //PLAYER_H
