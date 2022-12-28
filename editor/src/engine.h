#ifndef ENGINE_H
#define ENGINE_H
/**************************************************************************
* Copyright (C) 2005 by David Johnston                                    *
* dave@windozexp.com                                                      *
* engine() sets private variables to NULL                                 *
* ~engine() clears up the variables					                      *
* This is just a wrapper for the engine componenets			              *
***************************************************************************/
#include "display.h"
#include "cursor.h"
#include "spriteBase.h"
#include "Font.cpp"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

using namespace std;

///contains methods used for loading the map, sprites, config files, and data files. Also contains a method to check for sprite collisions and to draw the map.
class engine
{
    
public:
    
    ///constructor.
    engine();
    
    ///destructor.
    ~engine();
    
    ///loads the game.data file 
    int loadGame(char *filename, int &screenWidth, int &screenHeight, int &levelWidth, int &levelHeight, int &tileWidth, int &tileHeight, int &tilesAcross, int &tilesUp, int &colours);
    
    ///loads the map file into a 2D vector.
    int setupMap(int, int, vector< vector<int> > &, char *filename);
    
    ///loads the map file into a 2D vector.
    void newMap(int, int, vector< vector<int> > &);
    
    ///saves the map to a file
    int saveMap(int ySize, int xSize, SDL_Surface *screen, SFont *font, vector< vector<int> > &theMap, string filename);
        
    ///loads the correct section of the map to the backSurface vector
    int setupBack(int, int, int, int, vector< vector<int> > &, vector< vector<int> > &);
    
    ///draws the tiles held in backSurface to the surface
    void drawBack(int, int, int, int, engine *, vector< vector<int> > &, vector<SDL_Surface *>, SDL_Surface *);
    
    ///loads the surfaces images by loading a file containing the image filenames
    
    int loadSurfaces(char *filename, vector<SDL_Surface *> &surfaces, int &tileCount);
    
    ///loads the spriteBase images from a base file
    int loadBase(char *filename, spriteBase* &cursorBase, int tileCount);
    
    ///loads the player size and location from file
    int loadCursor(cursor* &theCursor, spriteBase* cursorBase, SDL_Surface *screen);
    
    
    ///pointer to a display object
    display *Display;
    
     
    
};
#endif //ENGINE_H
