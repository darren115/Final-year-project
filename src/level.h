#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include "sprite.h"
#include "player.h"
#include "orc.h"
#include "spriteBase.h"
#include "message.h"
#include "draw.h"

using std::string;
using std::vector;

class level: public collision
{
public:
       
       //Runs all of the main code that must occur for each level. Takes care of collision detection, collectable items and all character interactions.
       void levelCode(vector<orc *> &badGuys, vector<sprite *> &goodGuys, vector<Item *> &theObjects, player *thePlayer, engine *theEngine, SDL_Surface *screen, SDL_Surface *back, vector< vector <int> > &theMap, vector<sprite *> &screenInfo, vector<sprite *> &theDoors, vector< vector < int> > &backSurface, vector<SDL_Surface *> &surfaces, int &mapXPos, int &mapYPos, int mapX, int mapY, int tileHeight, int tileWidth, int backX, int backY, int screenWidth, int screenHeight, int audioflag, int level, SFont *fonta, vector<spriteBase *> &itemBase, vector<Item *> &uItems, vector<bool> cheats);
       
       //provides a method to draw a message to the screen
       int message(SDL_Surface *screen, char* filename, string name);
       
private:
       
       //runs item specific code that decrements the items life span and destroys the item        
       void itemCode(SDL_Surface *screen, vector<spriteBase *> &itemBase, vector<Item *> &uItems);
       
       void levelSpecific(vector<orc *> &badGuys, vector<sprite *> &goodGuys, vector<Item *> &theObjects, player *thePlayer, engine *theEngine, SDL_Surface *screen, SDL_Surface *back, vector< vector <int> > &theMap, vector<sprite *> &screenInfo, vector<sprite *> &theDoors, vector< vector < int> > &backSurface, vector<SDL_Surface *> &surfaces, int &mapXPos, int &mapYPos, int mapX, int mapY, int tileHeight, int tileWidth, int backX, int backY, int screenWidth, int screenHeight, int audioflag, int level, SFont *fonta, vector<spriteBase *> &itemBase, vector<Item *> &uItems, vector<bool> cheats);
       
protected:
          
         // Indicates whether to play the low health warning  
         bool lowHealthActive;
         
         //Indicates time since last warning was played
         int lowHealth;
         
         ///Creates an instance of the draw object.  This is used to reference the 
         ///functions and members of the draw class.
         draw dr;
          
                  
};
