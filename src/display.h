/***************************************************************************
 * Copyright (C) 2005 by David Johnston                                    *
 * dave@windozexp.com                                                      *
 ***************************************************************************/
#include <SDL/SDL.h>

///Class handling drawing to the screen.  It contains methods for initialising the video 
///subsystem (using SDL_Init(SDL_INIT_VIDEO)), setting the screen resolution and colour depth, 
///and drawing surfaces to the screen.
class display
{
    
public:
    
    ///Constructor.  When the display object is created the display is initialised.  The video 
    ///subsystem is then initialised by calling SDL_Init(SDL_INIT_VIDEO).
    display();
    
    ///Sets up the screen.  Sets hardware or software blitting, resolution and colour depth of 
    ///the screen.  It creates a SDL_Surface and uses SDL_SetVideoMode(screenWidth, screenHeight,noColours,theFlags) 
    ///to set up the screen. 
    SDL_Surface * setupScreen(int screenWidth, int screenHeight, int noColours, Uint32 theFlags);
    
    ///Draws one surface to another.  It blits an area of one surface onto the full area of 
    ///another surface.  The destination area is calculated by using the x and y coordinates 
    ///and width and height values passed to the function.
    void drawSurface(SDL_Surface *, int x, int y, int w, int h, SDL_Surface *);
    
    ///Draws one surface to another.  It blits an area of one surface onto an area of 
    ///another surface.  The areas are calculated using the source and destination 
    ///x and y coordinates and width and height values passed to the function.
    void drawSurface(SDL_Surface *, int srcX, int srcY, int srcW, int srcH, int destX, int destY, SDL_Surface *);
};
