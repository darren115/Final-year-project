#include "MenuItem.h"
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

using std::vector;

///used to represent menus in the game
class Menu
{
    public:
        ///a vector of MenuItem(s)
        vector<MenuItem *> theMenu;
        
        ///constructor that sets the items of the menu
        Menu (string items[], int size);
        
        ///draws the menu to the surface
        SDL_Surface* DrawMenu(int w, int itemh, int r, int g, int b, bool transparent);
        
};
