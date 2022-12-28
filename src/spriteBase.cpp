#include "spriteBase.h"
#include <SDL/SDL_image.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void spriteBase::loadPlayerImage(char *filename,int r, int g, int b)
{
     allImage.push_back(IMG_Load(filename));
        SDL_SetColorKey(allImage[allImage.size()-1], SDL_SRCCOLORKEY, SDL_MapRGB(allImage[allImage.size()-1]->format, r, g, b));
     
}


void spriteBase::loadImage(char *filename, char *image, int r, int g, int b)
{
    if(strcmp(image, "left") == 0)
    {
        leftImage = IMG_Load(filename);
        SDL_SetColorKey(leftImage, SDL_SRCCOLORKEY, SDL_MapRGB(leftImage->format, r, g, b));
    }
    else if(strcmp(image, "right") == 0)
    {
        rightImage = IMG_Load(filename);
        SDL_SetColorKey(rightImage, SDL_SRCCOLORKEY, SDL_MapRGB(rightImage->format, r, g, b));
    }
    else if(strcmp(image, "up") == 0)
    {
        upImage = IMG_Load(filename);
        SDL_SetColorKey(upImage, SDL_SRCCOLORKEY, SDL_MapRGB(upImage->format, r, g, b));
    }
    else if(strcmp(image, "down") == 0)
    {
        downImage = IMG_Load(filename);
        SDL_SetColorKey(downImage, SDL_SRCCOLORKEY, SDL_MapRGB(downImage->format, r, g, b));
    }
    else if(strcmp(image, "left1") == 0)
    {
        left1Image = IMG_Load(filename);
        SDL_SetColorKey(left1Image, SDL_SRCCOLORKEY, SDL_MapRGB(left1Image->format, r, g, b));
    }
    else if(strcmp(image, "right1") == 0)
    {
        right1Image = IMG_Load(filename);
        SDL_SetColorKey(right1Image, SDL_SRCCOLORKEY, SDL_MapRGB(right1Image->format, r, g, b));
    }
    else if(strcmp(image, "up1") == 0)
    {
        up1Image = IMG_Load(filename);
        SDL_SetColorKey(up1Image, SDL_SRCCOLORKEY, SDL_MapRGB(up1Image->format, r, g, b));
    }
    else if(strcmp(image, "down1") == 0)
    {
        down1Image = IMG_Load(filename);
        SDL_SetColorKey(down1Image, SDL_SRCCOLORKEY, SDL_MapRGB(down1Image->format, r, g, b));
    }

}

SDL_Surface * spriteBase::getImage(char *image)
{
    if(strcmp(image, "left") == 0)
    {
        return leftImage;
    }
    else if(strcmp(image, "right") == 0)
    {
        return rightImage;
    }
    else if(strcmp(image, "up") == 0)
    {
        return upImage;
    }
    else if(strcmp(image, "down") == 0)
    {
        return downImage;
    }
    else if(strcmp(image, "left1") == 0)
    {
        return left1Image;
    }
    else if(strcmp(image, "right1") == 0)
    {
        return right1Image;
    }
    else if(strcmp(image, "up1") == 0)
    {
        return up1Image;
    }
    else if(strcmp(image, "down1") == 0)
    {
        return down1Image;
    }
    else if(strcmp(image, "left2") == 0)
    {
        return left2Image;
    }
    else if(strcmp(image, "right2") == 0)
    {
        return right2Image;
    }
    else if(strcmp(image, "up2") == 0)
    {
        return up2Image;
    }
    else if(strcmp(image, "down2") == 0)
    {
        return down2Image;
    }

}

SDL_Surface * spriteBase::getImage2(int index)
{
     return allImage[index];

}
