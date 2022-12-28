#include "MenuItem.h"
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

using std::vector;

///Class that represents a menu in the game.  It contains a vector of MenuItem that hold the 
///items in the menu.  It also has a method that draws the Menu to the screen and can draw 
///with a transparent background if required.
class Menu
{
    public:
        ///Vector of MenuItem(s).  This is used to store the MenuItem that make up the Menu.  
        vector<MenuItem *> theMenu;
        
        ///Constructor.  It sets the items of the menu using the string array for the names of
        ///the items and the size of the menu is also passed.  It sets the first item in the Menu 
        ///to  be selected.
        Menu (string items[], int size);
        
        ///Draws the menu to the surface.  It draws the Menu to a SDL_Surface with the background 
        ///colour set to the r,g,b values.  The background can also be transparent.  It draws the 
        ///menu with the specified width.
        SDL_Surface* DrawMenu(int w, int itemh, int r, int g, int b, bool transparent);
        
};
