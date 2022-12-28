#include "Menu.h"
#include "Font.cpp"

Menu::Menu (string items[], int size)
{
    for( int i = 0; i < size; i++)
    {
        MenuItem *m = new MenuItem(items[i]);
        theMenu.push_back(m);         
    }
          
    MenuItem *m = theMenu.at(0); 
       
    m->selected = true;
    
    theMenu.at(0) = m;
    
}

SDL_Surface* Menu::DrawMenu (int w, int itemh, int r, int g, int b, bool transparent)
{
    SFont *font1;  
    font1 = new SFont(IMG_Load("data/font/fontb.png"));  
    
    SFont *font2;  
    font2 = new SFont(IMG_Load("data/font/fontc.png"));  
    
    SDL_Surface* menu;
    menu = SDL_CreateRGBSurface(SDL_HWSURFACE, w, (itemh*(theMenu.size())), 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);

    SDL_Rect srcdest;
    srcdest.x = 0;
    srcdest.y = 0;
    srcdest.w = w;
    srcdest.h = itemh*(theMenu.size());

    SDL_FillRect(menu, &srcdest, SDL_MapRGB(menu->format, r, g, b));
    
 
    SDL_SetColorKey(menu, SDL_SRCCOLORKEY, SDL_MapRGB(menu->format, r, g, b));   
    
    for(unsigned int i = 0; i < theMenu.size(); i++)
    {
        string str = theMenu.at(i)->text;
        
        if (theMenu.at(i)->selected)
        {
            font1->write(menu,str.c_str(),20,itemh*(i));
        }
        else
        {
            font2->write(menu,str.c_str(),20,itemh*(i));
        }
    }
    
    delete font1;
    delete font2;
    
    font1 = NULL;
    font2 = NULL;
    
    return menu;
    
}
