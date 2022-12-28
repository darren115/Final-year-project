/***************************************************************************
 * Copyright (C) 2005 by David Johnston                                     *
 * dave@windozexp.com 							                            * 
 * 									                                        *    
 * display() initialises the video subsystem				                *
 * setupScreen sets up the screen, setting HW or SW blitting + size and     *
 * colours                 		                                            *
 * The first drawsurface method blits an area of one surface onto the full  *
 * area of another surface.						                            *
 * The second drawsurface method blits an area of one surface onto an area  *
 * of a second surface							                            *
 ***************************************************************************/
#include <SDL/SDL.h>

///contains methods for initialising the video subsystem and drawing to surfaces
class display
{
    
public:
    
    ///constructor
    display();
    
    ///sets up the screen, setting hardware or software blitting, resolution and colour depth  
    SDL_Surface * setupScreen(int, int, int, Uint32);
    
    ///blits an area of one surface onto the full area of another surface
    void drawSurface(SDL_Surface *, int x, int y, int w, int h, SDL_Surface *);
    
    ///blits an area of one surface onto an area of another surface
    void drawSurface(SDL_Surface *, int, int, int, int, int, int, SDL_Surface *);
    
    ///draws a grid on the map to help editing
    void drawGrid(SDL_Surface *screen, int, int, int, int, int, int);
};
