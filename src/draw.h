#ifndef Draw_H
#define DRAW_H
#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL_image.h>
#include <string>
#include <vector>
#include "sprite.h"
#include "player.h"
#include "orc.h"
#include "spriteBase.h"
#include "Font.cpp"
#include "engine.h"
#include "Font.cpp"

using std::string;
class draw
{
public:

      //Draws a sprite to the screen 
      void drawSprite(sprite *spriteName, engine *engineName, SDL_Surface *screen);
      
      void drawSprite(sprite *spriteName, SDL_Surface *curs, engine *engineName, SDL_Surface *screen);    

      void drawAll(engine *theEngine, SDL_Surface *back, SDL_Surface *screen, player *thePlayer, vector<orc *> badGuys, vector<sprite *> goodGuys, vector<Item *> theObjects, vector<sprite *> screenInfo, vector<sprite *> theDoors, int backX, int backY, int screenWidth, int screenHeight, SFont *fonta, vector<Item *> uItems);
protected:
                 
      SFont *fonta; 
      SDL_Surface *j;  
};
#endif
