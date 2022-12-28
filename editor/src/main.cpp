#include <cstdlib>
#include <iostream>
#include <vector>
#include "engine.h"
#include "cursor.h"
#include "Font.cpp"
#include "message.h"
#include "Menu.h"
#include <dirent.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>



using namespace std;

SFont *font;

int backX = 0;   //Location of the backround to be blitted to the screen
int xOffset = 0; //Offset to which sprites should be displayed when the background moves Offset changes

int backY = 0;
int yOffset = 0;

int mapX = 0; //Keeps track of where we are in the whole level (backX keeps track of the current screen)
int mapY = 0;

int tileWidth =0;
int tileHeight =0;

int levelWidth =0;
int levelHeight =0;

int screenWidth =0;
int screenHeight =0;

int TILES_ACROSS;
int TILES_UP;

int COLOURS;

int width=1;  //area width
int height=1; //area height
int change=0;

int tileCount = 0; //Total number of tiles

void reset(engine *theEngine, cursor *theCursor, spriteBase *cursorBase, SDL_Surface *screen)
{
    int backX = 0;   
    int xOffset = 0; 

    int backY = 0;
    int yOffset = 0;

    int mapX = 0; 
    int mapY = 0;
    
    int mapXPos = 0;  
    int mapYPos = 0;  

    theCursor = NULL;
    
    theEngine->loadCursor(theCursor, cursorBase, screen);
}
    
    


vector<string> getFilenames()
{
    vector<string> files;
    
    DIR *pdir;
    struct dirent *pent;

    pdir=opendir("data/maps/");
    string s1;

    while ((pent=readdir(pdir)))
    {
        s1 = pent->d_name;

        if (s1.find(".map", s1.length()-4) != string::npos)
            files.push_back(s1);
    }

    closedir(pdir);

    return files;
}     

string saveasFilename(SDL_Surface *screen, SFont *font)
{
    SDL_Surface* dialog;
    dialog = SDL_CreateRGBSurface(SDL_HWSURFACE, 200, 150, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
    
    SDL_FillRect(dialog, NULL, SDL_MapRGB(dialog->format, 0, 0, 0));
    
    SDL_Rect srcdest;
    srcdest.x = 1;
    srcdest.y = 1;
    srcdest.w = 198;
    srcdest.h = 148;

    SDL_FillRect(dialog, &srcdest, SDL_MapRGB(dialog->format, 129, 83, 10));
    
    srcdest.x = 4;
    srcdest.y = 4;
    srcdest.w = 192;
    srcdest.h = 142;

    SDL_FillRect(dialog, &srcdest, SDL_MapRGB(dialog->format, 0, 0, 0));
    
    font->write(dialog, "Save As:", 15);
        
    string s = "";
    
    SDL_Event event;
    
    int isdone = 0;
    
    while (isdone == 0)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_KEYDOWN:           int key = event.key.keysym.sym;
    				                        if((((key>=SDLK_a)&&(key<=SDLK_z)) || ((key>=SDLK_0)&&(key<=SDLK_9))) && (s.length() < 8))
                                            {
                                                char *s1 = SDL_GetKeyName(event.key.keysym.sym);
                                                s += s1;
                                            }
                                            if(event.key.keysym.sym == SDLK_RETURN)
                                                isdone = 1;
                                            
                                            if (event.key.keysym.sym == SDLK_BACKSPACE)
                                            {
                                                s = s.substr(0, s.length()-1);
                                            }
                                            
                                            break;
                                            
            }
        }
        
        srcdest.x = 10;
        srcdest.y = 70;
        srcdest.w = 180;
        srcdest.h = 40;
        
        SDL_FillRect(dialog, &srcdest, SDL_MapRGB(dialog->format, 129, 83, 10));
        
        srcdest.x = 13;
        srcdest.y = 73;
        srcdest.w = 174;
        srcdest.h = 34;
        
        SDL_FillRect(dialog, &srcdest, SDL_MapRGB(dialog->format, 0, 0, 0));
        
        font->write(dialog, s.c_str(), 65);
        
        srcdest.x = 120;
        srcdest.y = 250;
        srcdest.w = 400;
        srcdest.h = 150;
    
        
        SDL_BlitSurface(dialog, NULL, screen, &srcdest); 
        
        
        
        SDL_Flip(screen);
    
    
    }
    
    SDL_FreeSurface(dialog);
        
    SDL_Flip(screen);
    
    return s;
                                            
}

int tileNum(SDL_Surface *screen, SFont *font)
{
    SDL_Surface* dialog;
    dialog = SDL_CreateRGBSurface(SDL_HWSURFACE, 200, 150, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
    
    SDL_FillRect(dialog, NULL, SDL_MapRGB(dialog->format, 0, 0, 0));
    
    SDL_Rect srcdest;
    srcdest.x = 1;
    srcdest.y = 1;
    srcdest.w = 198;
    srcdest.h = 148;

    SDL_FillRect(dialog, &srcdest, SDL_MapRGB(dialog->format, 129, 83, 10));
    
    srcdest.x = 4;
    srcdest.y = 4;
    srcdest.w = 192;
    srcdest.h = 142;

    SDL_FillRect(dialog, &srcdest, SDL_MapRGB(dialog->format, 0, 0, 0));
    
    font->write(dialog, "Tile Num:", 15);
        
    string s = "";
    
    int val;
    
    SDL_Event event;
    
    int isdone = 0;
    
    while (isdone == 0)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_KEYDOWN:           int key = event.key.keysym.sym;
    				                        if((((key>=SDLK_a)&&(key<=SDLK_z)) || ((key>=SDLK_0)&&(key<=SDLK_9))) && (s.length() < 8))
                                            {
                                                char *s1 = SDL_GetKeyName(event.key.keysym.sym);
                                                s += s1;
                                            }
                                            if(event.key.keysym.sym == SDLK_RETURN)
                                                isdone = 1;
                                            
                                            if (event.key.keysym.sym == SDLK_BACKSPACE)
                                            {
                                                s = s.substr(0, s.length()-1);
                                            }
                                            
                                            break;
                                            
            }
        }
        
        srcdest.x = 10;
        srcdest.y = 70;
        srcdest.w = 180;
        srcdest.h = 40;
        
        SDL_FillRect(dialog, &srcdest, SDL_MapRGB(dialog->format, 129, 83, 10));
        
        srcdest.x = 13;
        srcdest.y = 73;
        srcdest.w = 174;
        srcdest.h = 34;
        
        SDL_FillRect(dialog, &srcdest, SDL_MapRGB(dialog->format, 0, 0, 0));
        
        font->write(dialog, s.c_str(), 65);
        
        srcdest.x = 120;
        srcdest.y = 250;
        srcdest.w = 400;
        srcdest.h = 150;
    
        
        SDL_BlitSurface(dialog, NULL, screen, &srcdest); 
        
        
        
        SDL_Flip(screen);
    
    
    }
    
    SDL_FreeSurface(dialog);
        
    SDL_Flip(screen);
    
    val=atoi(s.c_str());
    //return s;
    return val;
                                            
}

int area(SDL_Surface *screen, SFont *font)
{
    SDL_Surface* dialog;
    dialog = SDL_CreateRGBSurface(SDL_HWSURFACE, 200, 150, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
    
    SDL_FillRect(dialog, NULL, SDL_MapRGB(dialog->format, 0, 0, 0));
    
    SDL_Rect srcdest;
    srcdest.x = 1;
    srcdest.y = 1;
    srcdest.w = 198;
    srcdest.h = 148;

    SDL_FillRect(dialog, &srcdest, SDL_MapRGB(dialog->format, 129, 83, 10));
    
    srcdest.x = 4;
    srcdest.y = 4;
    srcdest.w = 192;
    srcdest.h = 142;

    SDL_FillRect(dialog, &srcdest, SDL_MapRGB(dialog->format, 0, 0, 0));
    
    if (change==0)
    {
    font->write(dialog, "Width:", 15);
    change=1;
    }
    else
    {
    font->write(dialog, "Height:", 15);
    change=0;
    }
        
    string s = "";
    
    int val;
    
    SDL_Event event;
    
    int isdone = 0;
    
    while (isdone == 0)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_KEYDOWN:           int key = event.key.keysym.sym;
    				                        if((((key>=SDLK_a)&&(key<=SDLK_z)) || ((key>=SDLK_0)&&(key<=SDLK_9))) && (s.length() < 8))
                                            {
                                                char *s1 = SDL_GetKeyName(event.key.keysym.sym);
                                                s += s1;
                                            }
                                            if(event.key.keysym.sym == SDLK_RETURN)
                                                isdone = 1;
                                            
                                            if (event.key.keysym.sym == SDLK_BACKSPACE)
                                            {
                                                s = s.substr(0, s.length()-1);
                                            }
                                            
                                            break;
                                            
            }
        }
        
        srcdest.x = 10;
        srcdest.y = 70;
        srcdest.w = 180;
        srcdest.h = 40;
        
        SDL_FillRect(dialog, &srcdest, SDL_MapRGB(dialog->format, 129, 83, 10));
        
        srcdest.x = 13;
        srcdest.y = 73;
        srcdest.w = 174;
        srcdest.h = 34;
        
        SDL_FillRect(dialog, &srcdest, SDL_MapRGB(dialog->format, 0, 0, 0));
        
        font->write(dialog, s.c_str(), 65);
        
        srcdest.x = 120;
        srcdest.y = 250;
        srcdest.w = 400;
        srcdest.h = 150;
    
        
        SDL_BlitSurface(dialog, NULL, screen, &srcdest); 
        
        
        SDL_Flip(screen);
    
        
    }
    
    SDL_FreeSurface(dialog);
        
    SDL_Flip(screen);
    
    val=atoi(s.c_str());
    //return s;
    return val;
                                            
}

int saveFile(SDL_Surface *screen, SFont *font)
{
    SDL_Surface* dialog;
    dialog = SDL_CreateRGBSurface(SDL_HWSURFACE, 200, 150, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
    
    SDL_FillRect(dialog, NULL, SDL_MapRGB(dialog->format, 0, 0, 0));
    
    SDL_Rect srcdest;
    srcdest.x = 1;
    srcdest.y = 1;
    srcdest.w = 198;
    srcdest.h = 148;

    SDL_FillRect(dialog, &srcdest, SDL_MapRGB(dialog->format, 129, 83, 10));
    
    srcdest.x = 4;
    srcdest.y = 4;
    srcdest.w = 192;
    srcdest.h = 142;

    SDL_FillRect(dialog, &srcdest, SDL_MapRGB(dialog->format, 0, 0, 0));
    
    font->write(dialog, "Save file?", 15);
    font->write(dialog, "Y/N", 55);
    
    srcdest.x = 120;
    srcdest.y = 250;
    srcdest.w = 400;
    srcdest.h = 150;
    
    SDL_BlitSurface(dialog, NULL, screen, &srcdest); 
        
    SDL_Flip(screen);
        
    SDL_Event event;
    
    int isdone = 0;
    int save = 0;
    
    while (isdone == 0)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_y)
                {
                    save = 1;
                    isdone = 1; 
                }               
                if (event.key.keysym.sym == SDLK_n)
                    isdone = 1;
                
            }
        }
    
    
    }
    
    SDL_FreeSurface(dialog);
        
    SDL_Flip(screen);
    
    return save;
                                            
}

string load(SDL_Surface *screen, SFont *font)
{
    vector<string> files = getFilenames();
    
    string s;
                    
    string files2[files.size()];

    for(int i = 0; i < files.size(); i++)
        files2[i] = files.at(i);

    Menu *theMenu = new Menu(files2, files.size());
    
    int load_index = 0;
    int loading = 0;
    
    while (loading == 0)
    {
        SDL_Event event;
        
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_DOWN)
                {
                    if (load_index < files.size()-1)
                    {
                        theMenu->theMenu.at(load_index)->selected = false;
                        load_index++;
                        theMenu->theMenu.at(load_index)->selected = true;
                    }
                }
                if(event.key.keysym.sym == SDLK_UP)
                {
                    if (load_index > 0)
                    {
                        theMenu->theMenu.at(load_index)->selected = false;
                        load_index--;
                        theMenu->theMenu.at(load_index)->selected = true;
                    }
                }
            
                if (event.key.keysym.sym == SDLK_RETURN)
                {
                    s = "data/maps/" + theMenu->theMenu.at(load_index)->text;
                    
                    loading = 1;
                                        
                }
            }
        }
    
        SDL_Surface *lscreen = IMG_Load("data/images/backgrounds/intro.png");

        font->write(lscreen, "Choose a file to load:", 20);

        SDL_Surface *menu = theMenu->DrawMenu(200, 30, 0, 0, 0, true);
    
        SDL_Rect dest;
        dest.x = 210;
        dest.y = 100;
        dest.w = 200;
        dest.h = 30*(files.size()+1);
    
        SDL_BlitSurface(menu, NULL, lscreen, &dest); 
    
        SDL_BlitSurface(lscreen, NULL, screen, NULL); 
    
        SDL_Flip(screen);
    
        SDL_FreeSurface(lscreen); 
    }
    
    delete theMenu;
    
    return s;                                           
}

void drawSprite(sprite *spriteName, SDL_Surface *curs, engine *engineName, SDL_Surface *screen)
{
    SDL_Surface *temp;
    engineName->Display->drawSurface(spriteName->getImage(), spriteName->getX(), spriteName->getY(), 0, 0, screen);
    engineName->Display->drawSurface(curs, spriteName->getX(), spriteName->getY(), 0, 0, screen);
}

void draw(engine *theEngine, SDL_Surface *back, SDL_Surface *screen, cursor *theCursor, SDL_Surface *curs)
{
    theEngine->Display->drawSurface(back, backX, backY, screenWidth, screenHeight, screen);
    
    theEngine->Display->drawGrid(screen, tileWidth, tileHeight, screenWidth, screenHeight, TILES_ACROSS, TILES_UP);
    
    drawSprite(theCursor, curs, theEngine, screen);
        
    SDL_Flip(screen);

}



int main(int argc, char *argv[])
{
    
    int COLOURS;
    
    Uint8* keys;
    
    SDL_Surface *screen;

    SDL_Surface *back;
    SDL_Surface *curs = IMG_Load("data/images/cursor.png");
    SDL_SetColorKey(curs, SDL_SRCCOLORKEY, SDL_MapRGB(curs->format, 72, 152, 72));
   
    

    engine *theEngine = new engine;
    
    theEngine->loadGame("data/game.data", screenWidth, screenHeight, levelWidth, levelHeight, tileWidth, tileHeight, TILES_ACROSS, TILES_UP, COLOURS);
    
    //Changed for new tiles
    int mapXPos = 0;  //Position of the viewpoint  Be careful may cause the app to crash
    int mapYPos = 0;  //Position of the viewpoint Be careful may cause the app to crash

    mapX = (mapXPos*(-tileWidth));
    mapY = (mapYPos*(-tileHeight));

    vector< vector <int> > theMap;
    theMap.resize((levelHeight/tileHeight)+1);
    for(unsigned int i=0; i < theMap.size(); i++)
    {
        theMap[i].resize(levelWidth/tileWidth+1);
    }

    vector< vector <int> > backSurface;
    backSurface.resize(TILES_UP);//TILE_UP
    for(unsigned int i=0; i < backSurface.size(); i++)
    {
        backSurface[i].resize(TILES_ACROSS);//TILES_ACROSS
    }

    //Pointer to the cursor
    cursor *theCursor = NULL;
    spriteBase *cursorBase = NULL;

    //Vector of tiles/surfaces
    vector<SDL_Surface *> surfaces;

    //Flags for display
    Uint32 theFlags = SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN;

    //Setup the screen
    screen = theEngine->Display->setupScreen(screenWidth, screenHeight, COLOURS, theFlags);
    back = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_SRCCOLORKEY, screenWidth+(2*tileWidth), screenHeight+(2*tileHeight), COLOURS, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
    //SDL_SetColorKey(back, SDL_SRCCOLORKEY, SDL_MapRGB(back->format, 72, 152, 72));
   
    //Load surfaces
    theEngine->loadSurfaces("data/maps/level.surfaces", surfaces, tileCount);
    
    
    
    //Player
    theEngine->loadBase("data/maps/base/cursor.base", cursorBase, tileCount);
    theEngine->loadCursor(theCursor, cursorBase, screen);

    
    SDL_ShowCursor(SDL_DISABLE);

    int finished = 0;
    
    int done = 0;
    int intro1 = 0;
    int intro2 = 0;
    int intro3 = 0;
    int intro4 = 0;
    
    int edited = 0;
    int saveas = 0;
    
    SFont *font;  
    font = new SFont(IMG_Load("data/font/font.png"));
    
    Message *m1 = new Message("data/text/intro1.data");
    
    while (intro1 == 0)
    {
        SDL_Event event;
    
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                intro1 = 1;
                done = 1;
            }
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    SDL_Quit();
                	return 0;
                }
                if(event.key.keysym.sym == SDLK_RETURN)
                {
                    intro1 = 1;
                }
            }
        
        }
    
        SDL_Surface *intro = IMG_Load("data/images/backgrounds/intro.png");
    
        SDL_Surface *msg = m1->DrawMessage(font);
            
        SDL_BlitSurface(msg, NULL, intro, NULL); 
        SDL_FreeSurface(msg);
    
        theEngine->Display->drawSurface(intro, 0, 0, 0, 0, screen);
    
        SDL_Flip(screen);
    
        SDL_FreeSurface(intro);
    
    }

    delete m1;
    Message *m2 = new Message("data/text/intro2.data");

    vector<string> files;
    Menu *theMenu;

    int load_index = 0;
   

    while (intro2 == 0)
    {
        SDL_Event event;
    
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                intro2 = 1;
                done = 1;
            }
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    	SDL_Quit();
                	return 0;
                }
                if(event.key.keysym.sym == SDLK_F1)
                {
                    theEngine->newMap((levelHeight/tileHeight), (levelWidth/tileWidth), theMap);
                    theEngine->setupBack(TILES_UP, TILES_ACROSS, mapYPos, mapXPos, backSurface, theMap);
                    theEngine->drawBack(tileHeight, tileWidth, TILES_UP, TILES_ACROSS, theEngine, backSurface, surfaces, back);
    
                    SDL_Flip(screen);
    
                    saveas = 1;
                
                    intro2 = 1;
                }
                if(event.key.keysym.sym == SDLK_F2)
                {
                    files = getFilenames();
                    
                    string files2[files.size()];

                    for(int i = 0; i < files.size(); i++)
                        files2[i] = files.at(i);
        
                    theMenu = new Menu(files2, files.size());
                
                    intro3 = 1;
                    intro2 = 1;
                }
            
            }
        
        }
    
        SDL_Surface *intro = IMG_Load("data/images/backgrounds/intro.png");
    
        SDL_Surface *msg = m2->DrawMessage(font);
            
        SDL_BlitSurface(msg, NULL, intro, NULL); 
        SDL_FreeSurface(msg);
    
        theEngine->Display->drawSurface(intro, 0, 0, 0, 0, screen);
    
        SDL_Flip(screen);
    
        SDL_FreeSurface(intro);
    
    }

    delete m2;

    while (intro3 == 1)
    {
        SDL_Event event;
    
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                intro3 = 0;
                done = 1;
            }
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    	SDL_Quit();
                	return 0;
                }
            
                if(event.key.keysym.sym == SDLK_DOWN)
                {
                    if (load_index < files.size()-1)
                    {
                        theMenu->theMenu.at(load_index)->selected = false;
                        load_index++;
                        theMenu->theMenu.at(load_index)->selected = true;
                    }
                }
                if(event.key.keysym.sym == SDLK_UP)
                {
                    if (load_index > 0)
                    {
                        theMenu->theMenu.at(load_index)->selected = false;
                        load_index--;
                        theMenu->theMenu.at(load_index)->selected = true;
                    }
                }
            
                if (event.key.keysym.sym == SDLK_RETURN)
                {
                    string s = "data/maps/" + theMenu->theMenu.at(load_index)->text;
                    theEngine->setupMap((levelHeight/tileHeight), (levelWidth/tileWidth), theMap, (char *)s.c_str());
                    theEngine->setupBack(TILES_UP, TILES_ACROSS, mapYPos, mapXPos, backSurface, theMap);
                    theEngine->drawBack(tileHeight, tileWidth, TILES_UP, TILES_ACROSS, theEngine, backSurface, surfaces, back);
            
                    SDL_Flip(screen);
                                        
                    intro3 = 0;
                }
            }
        
        }
    
        SDL_Surface *intro = IMG_Load("data/images/backgrounds/intro.png");
    
        font->write(intro, "Choose a file to load:", 20);
    
        SDL_Surface *menu = theMenu->DrawMenu(200, 30, 0, 0, 0, true);
    
        SDL_Rect dest;
        dest.x = 210;
        dest.y = 100;
        dest.w = 200;
        dest.h = 30*(files.size()+1);
    
        SDL_BlitSurface(menu, NULL, intro, &dest); 
    
        theEngine->Display->drawSurface(intro, 0, 0, 0, 0, screen);
    
        SDL_Flip(screen);
    
        SDL_FreeSurface(intro);
    
    }

    while(done == 0)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                done = 1;
            }
            if (event.type == SDL_KEYDOWN)
            {
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:       if (edited == 1)
                                            {
                                                if (saveFile(screen, font) == 1)
                                                {
                                                    string s;
                                                    
                                                    do
                                                    {
                                                        s = saveasFilename(screen, font);
                                                    }
                                                    while(theEngine->saveMap((levelHeight/tileHeight), (levelWidth/tileWidth), screen, font, theMap, s) != 0);
                                                }
                                            }
                                            SDL_Quit();
                				return 0;
                                                
                                            break;
                                        
                    case SDLK_PAGEDOWN:     if (theCursor->getTile() < tileCount-1)
                                            {
                                                theCursor->setTile(theCursor->getTile()+1);
                                                theCursor->updateTileImage();
                                            }
                                            break;
                                        
                    case SDLK_PAGEUP:       if (theCursor->getTile() > 1)
                                            {
                                                theCursor->setTile(theCursor->getTile()-1);
                                                theCursor->updateTileImage();
                                            }
                                            break;
                                            
                    case SDLK_F1:           {
                                                string s;
                                                
                                                if (edited == 1)
                                                {
                                                    if (saveFile(screen, font) == 1)
                                                    {
                                                        do
                                                        {
                                                            s = saveasFilename(screen, font);
                                                        }
                                                        while(theEngine->saveMap((levelHeight/tileHeight), (levelWidth/tileWidth), screen, font, theMap, s) != 0);
                                                    }
                                                }
                                                
                                                reset(theEngine, theCursor, cursorBase, screen);
                                                edited = 0;
                                                
                                                theEngine->newMap((levelHeight/tileHeight), (levelWidth/tileWidth), theMap);
                                                theEngine->setupBack(TILES_UP, TILES_ACROSS, mapYPos, mapXPos, backSurface, theMap);
                                                theEngine->drawBack(tileHeight, tileWidth, TILES_UP, TILES_ACROSS, theEngine, backSurface, surfaces, back);
                                
                                                SDL_Flip(screen);
                                            }
                                            break;
                                            
                    case SDLK_F2:           {
                                                string s;
                                                
                                                if (edited == 1)
                                                {
                                                    if (saveFile(screen, font) == 1)
                                                    {
                                                        do
                                                        {
                                                            s = saveasFilename(screen, font);
                                                        }
                                                        while(theEngine->saveMap((levelHeight/tileHeight), (levelWidth/tileWidth), screen, font, theMap, s) != 0);
                                                    }
                                                }
                                                
                                                s = load(screen, font);
                                                reset(theEngine, theCursor, cursorBase, screen);
                                                edited = 0;
                                                
                                                theEngine->setupMap((levelHeight/tileHeight), (levelWidth/tileWidth), theMap, (char *)s.c_str());
                                                theEngine->setupBack(TILES_UP, TILES_ACROSS, mapYPos, mapXPos, backSurface, theMap);
                                                theEngine->drawBack(tileHeight, tileWidth, TILES_UP, TILES_ACROSS, theEngine, backSurface, surfaces, back);
                                                
                                                SDL_Flip(screen);
                
                                                
                                            }
                                            break;
                                            
                    case SDLK_F3:           {
                                                string s;
                                                
                                                do
                                                {
                                                    s = saveasFilename(screen, font);
                                                }
                                                while(theEngine->saveMap((levelHeight/tileHeight), (levelWidth/tileWidth), screen, font, theMap, s) != 0);
                                                
                                                edited = 0;
                                                
                                            }
                                            break;
                                            
                    case SDLK_RETURN:       {
                                            edited = 1;
                                            
                                            for (int l=((mapY-theCursor->getY()-theCursor->getH()+1)/tileHeight);l>((mapY-theCursor->getY()-theCursor->getH()+1)/tileHeight)-height;l--)
                                            {
                                                for (int k=((mapX-theCursor->getX())/tileWidth); k>((mapX-theCursor->getX())/tileWidth)-width;k--)
                                                {
                                                    theMap[-l][-k] = theCursor->getTile()-1;
                                                }
                                            }
                                            theEngine->setupBack(TILES_UP, TILES_ACROSS, mapYPos, mapXPos, backSurface, theMap);
                                            theEngine->drawBack(tileHeight, tileWidth, TILES_UP, TILES_ACROSS, theEngine, backSurface, surfaces, back);
            
                                            SDL_Flip(screen);
                                            }
                                            break;
                                            
                  case SDLK_F4:              {
                                             int s;

                                             s = tileNum(screen, font);
                                             if ((s>=0) && (s<=tileCount-1))
                                             {
                                            theCursor->setTile(s);
                                            theCursor->updateTileImage();
                                            }
                                            }
                                            break;
                  case SDLK_F5:              {
                                             int x;
                                             int y;
                                             
                                             x = area(screen, font);
                                             y = area(screen, font);
                                             if ((x>=0) && (x<=70))
                                             {
                                              width=x;
                                              height=y;
                                            }
                                            }
                                            break;                          
                }
            }
        }
          
        //---------------------------UPDATE TILES IF REQUIRED-------------------------\\
        //Change the Tiles around.
        if((mapX <= -tileWidth) && (mapX > (tileWidth-levelWidth)))
        {	//Must be less than -640 but greater than -1280 (i.e -641 to -1279)
            if(backX <= -tileWidth*2)
            {  //-1260
                mapXPos++;
                theEngine->setupBack(TILES_UP, TILES_ACROSS, mapYPos, mapXPos, backSurface, theMap);
                theEngine->drawBack(tileHeight, tileWidth, TILES_UP, TILES_ACROSS, theEngine, backSurface, surfaces, back);
                backX=backX+tileWidth;

            }
        }
        if((mapX >= tileWidth-levelWidth) && (mapX < 0))
        {   //-2560
            if(backX >=0)
            {
                mapXPos--;
                theEngine->setupBack(TILES_UP, TILES_ACROSS, mapYPos, mapXPos, backSurface, theMap);
                theEngine->drawBack(tileHeight, tileWidth, TILES_UP, TILES_ACROSS, theEngine, backSurface, surfaces, back);
                backX=backX-tileWidth;

            }
        }
        if((mapY <= -tileHeight) && (mapY > (tileHeight-levelHeight)))
        {
            if(backY <= -tileHeight*2)
            {
                mapYPos++;
                theEngine->setupBack(TILES_UP, TILES_ACROSS, mapYPos, mapXPos, backSurface, theMap);
                theEngine->drawBack(tileHeight, tileWidth, TILES_UP, TILES_ACROSS, theEngine, backSurface, surfaces, back);
                backY=backY+tileHeight;

            }
        }
        if((mapY >= tileHeight-levelHeight) && (mapY < 0))
        {
            if(backY >=0)
            {
                mapYPos--;
                theEngine->setupBack(TILES_UP, TILES_ACROSS, mapYPos, mapXPos, backSurface, theMap);
                theEngine->drawBack(tileHeight, tileWidth, TILES_UP, TILES_ACROSS, theEngine, backSurface, surfaces, back);
                backY=backY-tileHeight;
            }
        }

        //-------------------------END UPDATE TILES-----------------------------------\\
        
        keys = SDL_GetKeyState(NULL);
        
        //Can we move the player??
        int i=((mapY-theCursor->getY()-theCursor->getH()+1)/tileHeight);
        int j=((mapX-theCursor->getX())/tileWidth);
        
        theCursor->setOldX(theCursor->getX());
        theCursor->setOldY(theCursor->getY());
        theCursor->move(keys, backX, mapX, xOffset, backY, mapY, yOffset, screenWidth, screenHeight, levelWidth, levelHeight);
                                        
        
        draw(theEngine, back, screen, theCursor, curs);
        
        SDL_Delay(50);
    }

    delete font;
    delete theMenu;
    
    
}
