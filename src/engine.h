/***************************************************************************
 * Copyright (C) 2005 by David Johnston                                    *
 * dave@windozexp.com                                                      *
 ***************************************************************************/
#include "display.h"
#include "sound.h"
#include "sprite.h"
#include "player.h"
#include "orc.h"
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>


///The engine class provides functions used to load and run the game.  It contains methods 
///used for loading map files, sprites, config files, and data files. It also contains a method 
///to check for sprite collisions and to draw the map.  It also contains member classes 
///Sound and Display, pointers to sound and display objects.  These are used by the engine to 
///access the sound and display objects. 
class engine
{
    
public:
    
    ///Constructor.  Sets the Sound and Display pointers to NULL.
    engine();
    
    ///Destructor.  Deletes the memory used for the Sound andDisplay pointers and sets them 
    ///to NULL.
    ~engine();
    
    ///Checks if the two sprites overlap and collide.  Returns 1 when there is a collision and 
    ///0 when there isn't.  Uses reduced rectangle collision detection to see if the two sprites overlap 
    ///and a collision has occured.
    int spriteCollide(sprite* object1, sprite* object2);
    
    ///Loads the map file into a 2D vector.  It opens the map file and reads the data into a 2D int vector 
    ///that represents the map.
    int setupMap(int ySize, int xSize, std::vector< std::vector<int> > &theMap, char *filename);
    
    ///Loads the correct section of the map to the backSurface vector.  Uses the map offsets (mapXPos 
    ///and mapYPos) as the starting point and copies theMap into backSurface using y and x as the values 
    ///for width and height.
    int setupBack(int y, int x, int mapYPos, int mapXPos, std::vector< std::vector <int> > &backSurface, std::vector< std::vector <int> > &theMap);
    
    ///Draws the tiles held in backSurface to the surface.  The Display object pointer is used to reference the 
    ///drawSurface(SDL_Surface *, int x, int y, int w, int h, SDL_Surface *) method to draw the tiles from backSurface 
    ///to the SDL_Surface back, by using the tile number to reference the tile surfaces held in the SDL_Surface vector surfaces.
    void drawBack(int tileHeight, int tileWidth, int y, int x, engine *theEngine, std::vector< std::vector <int> > &backSurface, std::vector<SDL_Surface *> surfaces, SDL_Surface *back);
    
    ///Loads the game.data file.  It loads the values for the following attributes into the appropriate variables.  
    ///It loads the values for screen width, screen height, level width, level height, tile width, tile height, tiles across, 
    ///tiles up and colour depth.  It loads these values from the game.data file. 
    int loadGame(char *filename, int &screenWidth, int &screenHeight, int &levelWidth, int &levelHeight, int &tileWidth, int &tileHeight, int &tilesAcross, int &tilesUp, int &colours);
    
    ///Loads the tile images.  It loads the image filenames from the level.surfaces file.  Then it uses the filenames 
    ///to load the images into the surfaces SDL_Surface vector.
    int loadSurfaces(char *filename, std::vector<SDL_Surface *> &surfaces);
    
    ///Loads the player size and location from a file.  It loads the players width, height and x and y 
    ///coordinates from the level.player file.  It then initialises the player with the playerBase and weaponBase 
    ///spritebases passed to the function.
    int loadPlayer(char *filename, player* &thePlayer,vector<spriteBase *> playerBase, SDL_Surface *screen, spriteBase* weaponBase, spriteBase* boomBase);
    
    ///Loads the spriteBase images from a file.  It loads the base file and reads the filename and colour key r,g,b information 
    ///from it.  These images are then loaded into the playerBase spriteBase with the appropriate directions.
    int loadBase(char *filename, spriteBase* &playerBase);
    
    ///Loads the spriteBase images from a file.  It loads the base file and reads the filename and colour key r,g,b information 
    ///from it.  These images are then loaded into the playerBase spriteBase vector in order.
    int loadPlayerBase(char *filename, spriteBase* &playerBase);
    
    ///Loads the music file locations from a file.  It reads the filename 
    ///from it.  These filenames are then loaded into the theMusic vector.
    int loadMusic(char *filename, std::vector< string> &theMusic);
    
    ///Loads a list of base files.  It loads the bases file that contains a list of filenames to be loaded as base files.  
    ///The loadBase function is then called for each of these base files, loading the images from the base files.
    int loadBaseList(char *filename, std::vector<spriteBase *> &base);
    
    ///Loads a list of base files.  It loads the bases file that contains a list of filenames to be loaded as base files.  
    ///The loadplayerBase function is then called for each of these base files, loading the images from the base files.
    int loadPlayerBaseList(char *filename, std::vector<spriteBase *> &base);
    
    ///Loads the position and size of a sprite.  It loads the sprites width, height, x and y 
    ///coordinates and base number from the file.  It then initialises the sprite with the appropriate base, 
    ///width, height and position.
    int loadSprites(char *filename, std::vector<sprite *> &theSprite, std::vector<spriteBase *> &spriteBase, SDL_Surface *screen);
    
    ///Loads the position and size of an orc.  It loads the orcs width, height, x and y 
    ///coordinates and base number from the file.  It also loads the filename of the file 
    ///containing the direction information.  It then initialises the orc with the appropriate base, 
    ///width, height and position.  Finally it loads the directions and sets the vision and range 
    ///values for the orc.
    int loadSprites(char *filename, std::vector<orc *> &theSprite, std::vector<spriteBase *> &spriteBase, SDL_Surface *screen, spriteBase* weaponBase);
    
    ///Loads the position and size of an Item.  It loads the Items width, height, x and y 
    ///coordinates and base number from the file.  It also loads the name of the Item and 
    ///whether or not the Item is visible.  It then initialises the sprite with the appropriate base, 
    ///width, height and position.  It also sets the name of the Item and whether the Item is visible.
    int loadSprites(char *filename, std::vector<Item *> &theItem, std::vector<spriteBase *> &spriteBase, SDL_Surface *screen);
    
    ///Loads the config file and sets audioflag.  It loads the game.cfg file and reads whether the 
    ///audio is enabled or disabled.  It then sets the audioflag to either disable or enable sound in the game.
    int loadConfig(char *filename);
    
    ///Pointer to a display object.  This is a pointer to a display object that is used to reference the 
    ///functions and members of the display class.
    display *Display;
    
    ///Pointer to a sound object.  This is a pointer to a sound object that is used to reference the 
    ///functions and members of the sound class.
    sound *Sound;
};
