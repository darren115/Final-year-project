#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include "player.h"

using namespace std;

class file
{
public:
          file();
          
          void save(player* thePlayer);
          
          void setFile(char *filename);
          
          void erase();
          
          int load(string type);
          
          void loadAll(player* &thePlayer, SDL_Surface *screen);
          
          string loadName();
          
protected:  
             
          char *savefile;
};
