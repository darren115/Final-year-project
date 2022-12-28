#ifndef SPRITE_H
#define SPRITE_H

#include <stdlib.h>
#include <stdio.h>
#include "spriteBase.h"
#include <SDL/SDL.h>

///class representing a general sprite
class sprite
{
    
public:
    
    ///initialises a sprite from a spriteBase
    void initSprite(char *, SDL_Surface *, int, int, int, int);
    
    ///initialises a sprite from a file
    void initSprite(spriteBase *, SDL_Surface *, int, int, int, int);
    
    ///sets mX
    void setX(int);
    
    ///sets mY
    void setY(int);
    
    ///sets mOldX
    void setOldX(int);
    
    ///sets mOldY
    void setOldY(int);
    
    ///sets mW
    void setW(int);
    
    ///sets mH
    void setH(int);
    
    ///sets colW
    void setColW(int x)
    {
        colW = x;
    }
    
    ///sets colH
    void setColH(int x)
    {
        colH = x;
    }
    
    ///sets colXOffset
    void setColXOffset(int x)
    {
        colXOffset = x;
    }
    
    ///sets colYOffset
    void setColYOffset(int x)
    {
        colYOffset = x;
    }
    
    ///sets mTile
    void setTile(int tile)
    {
        mTile = tile;
    }
    
    ///returns mDirection
    int getTile()
    {
        return mTile;
    }
    
    ///sets spriteImage from a file
    void setImage(char* filename);
    
    ///sets spriteImage from a surface
    void setImage(SDL_Surface * image);
    
    ///returns mX
    int getX();
    
    ///returns mY
    int getY();
    
    ///returns mOldX
    int getOldX();
    
    ///returns mOldY
    int getOldY();
    
    ///returns mH
    int getH();
    
    ///returns mW
    int getW();
    
    ///returns colW
    int getColW()
    {
        return colW;
    }
    
    ///returns colH
    int getColH()
    {
        return colH;
    }
    
    ///returns colXOffset
    int getColXOffset()
    {
        return colXOffset;
    }
    
    ///returns colYOffset
    int getColYOffset()
    {
        return colYOffset;
    }
    
    ///returns spriteImage
    SDL_Surface* getImage();
    
    ///updates the background behind the sprite
    void updateBgReplacement(SDL_Surface *);
    
    ///returns mBackReplacement
    SDL_Surface* getBG();
    
    ///returns mScreen
    SDL_Surface* getmScreen();
    
    ///sets visible
    void setVisible(bool v)
    {
        visible = v;
    }
    
    ///returns visible
    bool getVisible()
    {
        return visible;
    }
    
    ///returns base
    spriteBase* getBase()
    {
        return base;
    }
    
protected:
    
    ///x position
    int mX;
    
    ///y position
    int mY;
    
    ///width
    int mW;
    
    ///height
    int mH;
    
    ///old x position
    int mOldX;
    
    ///old y position
    int mOldY;
    
    ///column width
    int colW;
    
    ///column height
    int colH;
    
    ///column x offset
    int colXOffset;
    
    ///column y offset
    int colYOffset;
    
    ///tile number
    int mTile;
    
    ///visible flag
    bool visible;
    
    ///surface representing the sprite's image
    SDL_Surface* spriteImage;
    
    ///surface containing background behind sprite
    SDL_Surface *mBackReplacement;
    
    ///surface representing the screen
    SDL_Surface *mScreen;
    
    ///spriteBase for the sprite
    spriteBase *base;
};
#endif //SPRITE_H
