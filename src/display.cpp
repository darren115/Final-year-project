/***************************************************************************
 * Copyright (C) 2005 by David Johnston                                    *
 * dave@windozexp.com                                                      *
 ***************************************************************************/
#include <stdlib.h>
#include "display.h"

//
//When display object is created initialise the display. 
//
display::display()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Unable to init SDL: %s\n", SDL_GetError());
        exit(1);
    }
    atexit(SDL_Quit);
}

//
//Setup the screen
//Input: screen width, screen height, number of pixels, flags to set the video mode (see SDL documentaiton)
//Ouput: a SDL_Surface to draw on
//
SDL_Surface* display::setupScreen(int screenWidth, int screenHeight, int noColours, Uint32 theFlags)
{
    SDL_Surface *screen;
    screen = SDL_SetVideoMode(screenWidth, screenHeight,noColours,theFlags);
    if (screen == NULL)
    {
        printf("Unable to set screen %d x %d @ %d: %s\n",screenWidth, screenHeight, noColours, SDL_GetError());
        exit(1);
    }
    return screen;
}

//
//Blits a source surface onto part of a destination surface
//Input: Source Surface, x cord, y cord, width, height, destintation surface
//
void display::drawSurface(SDL_Surface *image, int x, int y, int w, int h, SDL_Surface *screen)
{
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = w;
    dest.h = h;
    //Copy image onto screen starting at dest (x,y).
    SDL_BlitSurface(image, NULL, screen, &dest);
}

//
//Blits part of a source surface onto part of a destination surface
//Input: Source Surface, the source x cord, source y cord, source width, height, dest x, dest y, dest surface.
//
void display::drawSurface(SDL_Surface *image, int srcX, int srcY, int srcW, int srcH, int destX, int destY, SDL_Surface *screen)
{
    SDL_Rect dest;
    dest.x = destX;
    dest.y = destY;
    SDL_Rect srcdest;
    srcdest.x = srcX;
    srcdest.y = srcY;
    srcdest.w = srcW;
    srcdest.h = srcH;
    SDL_BlitSurface(image, &srcdest, screen, &dest);
}
