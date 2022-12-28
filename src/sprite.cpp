#include "sprite.h"
#include <SDL/SDL_image.h>
#include <stdlib.h>
#include <stdio.h>

void sprite::initSprite(spriteBase *inBase, SDL_Surface *screen, int x, int y, int w, int h)
{
    base = inBase;
    spriteImage = base->getImage("down");
    mBackReplacement = SDL_DisplayFormat(spriteImage);
    updateBgReplacement(screen);
    mScreen = screen;
    frame = 0;

    visible = true;

    setX(x);
    setY(y);
    setW(w);
    setH(h);
    setColW((int)(getW()*0.80));
    setColH((int)(getH()*0.80));
    setColXOffset((getW()-getColW())/2);
    setColYOffset((getH()-getColH())/2);

}

void sprite::initSprite(char *filename, SDL_Surface *screen, int x, int y, int w, int h)
{

    spriteImage = IMG_Load(filename);
    if(spriteImage == NULL)
    {
        printf("Error, cannot load spriteImage %s", filename);
    }
    SDL_SetColorKey(spriteImage, SDL_SRCCOLORKEY, SDL_MapRGB(spriteImage->format, 72, 152, 72));
    mBackReplacement = SDL_DisplayFormat(spriteImage);
    updateBgReplacement(screen);
    mScreen = screen;

    visible = true;

    setX(x);
    setY(y);
    setW(w);
    setH(h);
    setColW((int)(getW()*0.70));
    setColH((int)(getH()*0.70));
    setColXOffset((getW()-getColW())/2);
    setColYOffset((getH()-getColH())/2);

}

void sprite::setImage(char *filename)
{
    spriteImage = IMG_Load(filename);
    if(spriteImage == NULL)
    {
        printf("Error, cannot load spriteImage %s", filename);
    }
    SDL_SetColorKey(spriteImage, SDL_SRCCOLORKEY, SDL_MapRGB(spriteImage->format, 72, 152, 72));
}

void sprite::setImage(SDL_Surface *image)
{
    spriteImage = image;
    SDL_SetColorKey(spriteImage, SDL_SRCCOLORKEY, SDL_MapRGB(spriteImage->format, 72, 152, 72));
}

void sprite::setX(int x)
{
    mX = x;
}
void sprite::setY(int y)
{
    mY = y;
}
void sprite::setOldX(int x)
{
    mOldX = x;
}
void sprite::setOldY(int y)
{
    mOldY = y;
}
void sprite::setW(int w)
{
    mW = w;
}
void sprite::setH(int h)
{
    mH = h;
}
int sprite::getX()
{
    return mX;
}
int sprite::getY()
{
    return mY;
}
int sprite::getOldX()
{
    return mOldX;
}
int sprite::getOldY()
{
    return mOldY;
}
int sprite::getH()
{
    return mH;
}
int sprite::getW()
{
    return mW;
}
SDL_Surface* sprite::getImage()
{
    return spriteImage;
}

void sprite::updateBgReplacement(SDL_Surface *screen)
{
    SDL_Rect srcrect;
    srcrect.x = mX;
    srcrect.y = mY;
    srcrect.w = mW;
    srcrect.h = mH;
    mOldX=mX;
    mOldY=mY;
    SDL_BlitSurface(screen, &srcrect, mBackReplacement, NULL);
}
SDL_Surface* sprite::getBG()
{
    return mBackReplacement;
}
SDL_Surface* sprite::getmScreen()
{
    return mScreen;
}
