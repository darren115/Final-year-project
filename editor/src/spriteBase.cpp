#include "spriteBase.h"
#include <SDL/SDL_image.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>



void spriteBase::loadImage(char *filename, int image, int tileCount)
{
    theTiles.resize(tileCount);
    theTiles[image] = IMG_Load(filename);
     
}


SDL_Surface * spriteBase::getImage(int image)
{
    
    return theTiles[image];
 
}
