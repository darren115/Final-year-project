/***************************************************************************
 * Copyright (C) 2005 by David Johnston                                    *
 * dave@windozexp.com                                                      *
 *                                                                         *
 ***************************************************************************/
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
#include "menu.h"
#include "file.h"
#include "level.h"
#include "cursor.h"

using std::string;
using std::vector;

draw dr;
level lv;

SFont *font;
SFont *fontp;
SFont *fontc;


vector <bool> cheats(5, 0);


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

int audioflag;

file current;

SDL_Surface *curs = IMG_Load("data/images/cursor.png");

void loadLevel(engine *theEngine, vector< vector<int> > &theMap, vector<SDL_Surface *> &surfaces, int &mapXPos, int &mapYPos, int inMapXPos, int inMapYPos, char *filename)
{
       //Try to load a new level
       //Load the Map
       surfaces.clear();
       theEngine->loadSurfaces("data/maps/level.surfaces", surfaces);
       theEngine->setupMap((levelHeight/tileHeight), (levelWidth/tileWidth), theMap, filename);
       mapXPos=inMapXPos;
       mapYPos=inMapYPos;
       mapY=(-inMapYPos*tileHeight);
       mapX=(-inMapXPos*tileWidth);
       backX=0;
       backY=0;
       xOffset=0;
       yOffset=0;

}

int endGame(SDL_Surface *screen)
{
    //Create message to tell Blink
    int ok = 1;
    SDL_Event event;
    SDL_PollEvent(&event);
    int value = 0;
    SFont *fontd;  
    fontd = new SFont(IMG_Load("data/font/fontd.png")); 
        
    Message *m = new Message("data/text/end.data");
    
    SDL_Rect dest;
    dest.x = 120;
    dest.y = 250;
    dest.w = 400;
    dest.h = 150;
    
    SDL_Surface *msg = m->DrawMessage(fontd);
    SDL_BlitSurface(msg, NULL, screen, &dest); 
    SDL_FreeSurface(msg);
        
    SDL_Flip(screen);
    while(ok > 0)
    {
        SDL_PollEvent(&event);
        if(event.key.keysym.sym == SDLK_y)
        {
            ok =0;
            value =0;
        }
        else if(event.key.keysym.sym == SDLK_n)
        {
            ok=0;
            value = 1;
        }
    }
    delete m;
    delete fontd;
    m = NULL;
    fontd = NULL;
    
    return value;
}

void helpText(SDL_Surface *screen, player *thePlayer)
{
    //Create message to tell Blink
    int ok = 1;
    SDL_Event event;
    SDL_PollEvent(&event);
    SFont *fontd;  
    fontd = new SFont(IMG_Load("data/font/fontd.png")); 
        
    Message *m = new Message("data/text/f1.data", thePlayer->getName());
    
    SDL_Rect dest;
    dest.x = 120;
    dest.y = 100;
    dest.w = 400;
    dest.h = 400;
    
    SDL_Surface *msg = m->DrawMessage(fontd, 400, 250);
    SDL_BlitSurface(msg, NULL, screen, &dest); 
    SDL_FreeSurface(msg);
        
    SDL_Flip(screen);
    
    while(ok > 0)
    {
        SDL_PollEvent(&event);
        if(event.key.keysym.sym == SDLK_F1)
        {
            ok =0;
        }
    }
    
    delete m;
    delete fontd;
    m = NULL;
    fontd = NULL;
    
}

string profileName(SDL_Surface *screen, SFont *font)
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
    
    font->write(dialog, "Name:", 15);
        
    string s = "";
    
    int val;
    
    SDL_Event event;
    
    int isdone = 0;
    SDL_EnableUNICODE(1);
    while (isdone == 0)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_KEYDOWN:           int key = event.key.keysym.unicode;
    				                        if((((key>=(Uint16)'a')&&(key<=(Uint16)'z')) || ((key>=(Uint16)'A')&&(key<=(Uint16)'Z')) || ((key>=SDLK_0)&&(key<=SDLK_9))) && (s.length() < 5))
                                            {
                                                s += (char)event.key.keysym.unicode;
                                            }
                                            if((event.key.keysym.sym == SDLK_RETURN) && (s.length()!=0))
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





string enterCheat(SDL_Surface *screen, SFont *font)
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
    
    font->write(dialog, "Code:", 15);
        
    string s = "";
    
    int val;
    
    SDL_Event event;
    
    int isdone = 0;
    SDL_EnableUNICODE(1);
    while (isdone == 0)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_KEYDOWN:           int key = event.key.keysym.unicode;
    				                        if((((key>=(Uint16)'a')&&(key<=(Uint16)'z')) || ((key>=(Uint16)'A')&&(key<=(Uint16)'Z')) || ((key>=SDLK_0)&&(key<=SDLK_9))) && (s.length() < 5))
                                            {
                                                s += (char)event.key.keysym.unicode;
                                            }
                                            if((event.key.keysym.sym == SDLK_RETURN) && (s.length()!=0))
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






//Main Game
int main(int argc, char *argv[])
{
    int TILES_ACROSS;
    int TILES_UP;

    int COLOURS;

    SDL_Surface *screen;

    SDL_Surface *back;

    engine *theEngine = new engine;
    
    int level = 0;
    
    int input_delay = 10;
    
    //Setups up the cursor
    cursor *theCursor = NULL;
    theCursor = new cursor(screen, 88, 70, 40, 40);
    SDL_SetColorKey(curs, SDL_SRCCOLORKEY, SDL_MapRGB(curs->format, 72, 152, 72));
    
    theEngine->loadGame("data/game.data", screenWidth, screenHeight, levelWidth, levelHeight, tileWidth, tileHeight, TILES_ACROSS, TILES_UP, COLOURS);

    //Changed for new tiles
    int mapXPos = 3;  //Position of the viewpoint  Be careful may cause the app to crash if player is drawn on tile they cant move on
    int mapYPos = 2;
    
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

    //Vector of BadGuys
    vector<orc *> badGuys;
    vector<spriteBase *> badBase;

    //Vector of Objects
    vector<Item *> theObjects;
    vector<spriteBase *> objectBase;

//Vector of Objects
    vector<spriteBase *> doorBase;
    vector<sprite *> theDoors;
    
    //Vector of inventory items
    vector<Item *> theInventory;
    vector<spriteBase *> invBase;
    
    //Vector of collectable items
    vector<spriteBase *> itemBase;
    vector<Item *> uItems;  
    
    
    //Vector of GoodGuys
    vector<sprite *> goodGuys;
    vector<spriteBase *> goodBase;

    //Vector of screen Info
    vector<sprite *> screenInfo;
    vector<spriteBase *> screenBase;

    //Pointer to the Player
   // player *thePlayer = NULL;
  //  spriteBase *playerBase = NULL;
    player *thePlayer = NULL;
    vector<spriteBase *>playerBase;

    //Array of Pointers to Sprites "The Arrows"
    spriteBase *arrowBase = NULL;
    
    //Array of Pointers to Sprites "The Arrows"
    spriteBase *boomerangBase = NULL;

    //Vector of tiles/surfaces
    vector<SDL_Surface *> surfaces;
    
    vector<string> theMusic;

    //Flags for display
    Uint32 theFlags = SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN;

    //Setup the screen
    screen = theEngine->Display->setupScreen(screenWidth, screenHeight, COLOURS, theFlags);
    back = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_SRCCOLORKEY, screenWidth+(2*tileWidth), screenHeight+(2*tileHeight), COLOURS, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
    SDL_SetColorKey(back, SDL_SRCCOLORKEY, SDL_MapRGB(back->format, 72, 152, 72));
    

    //Load the Map
    theEngine->setupMap((levelHeight/tileHeight), (levelWidth/tileWidth), theMap, "data/maps/level0/level0.map");
    theEngine->setupBack(TILES_UP, TILES_ACROSS, mapYPos, mapXPos, backSurface, theMap);
    theEngine->loadSurfaces("data/maps/level.surfaces", surfaces);
    theEngine->drawBack(tileHeight, tileWidth, TILES_UP, TILES_ACROSS, theEngine, backSurface, surfaces, back);

    
    Uint8* keys;
    unsigned int gTimer = 0;
    unsigned int gTimer2 = 0;
    const int FRAME_RATE = 2;
    
    /*--------------------SETUP SPRITES-----------------------------------*/
    //Arrows
    theEngine->loadBase("data/maps/base/arrow.base", arrowBase);
    
     //Arrows
    theEngine->loadBase("data/maps/base/boomerang.base", boomerangBase);
    
    //Items displayer in the inventory
    theEngine->loadBaseList("data/maps/base/inventory.bases", invBase);
    theEngine->loadSprites("data/maps/level0.inventory", theInventory, invBase, screen);
    
    //Items the player collects
    theEngine->loadBaseList("data/maps/base/items.bases", itemBase);

    //Player
    theEngine->loadPlayerBaseList("data/maps/base/player.bases", playerBase);
    theEngine->loadPlayer("data/maps/level0/level0.player", thePlayer, playerBase, screen, arrowBase, boomerangBase);

    //Good Guy Sprites
    theEngine->loadBaseList("data/maps/base/goodguy.bases", goodBase);

    //Screen Sprites
    theEngine->loadBaseList("data/maps/base/screen.bases", screenBase);
    theEngine->loadSprites("data/maps/level0.screen", screenInfo, screenBase, screen);

    //Bad Guy Sprites
    theEngine->loadBaseList("data/maps/base/badguy.bases", badBase);
    theEngine->loadSprites("data/maps/level0/level0.badguy", badGuys, badBase, screen, arrowBase);

    //Object Sprites
    theEngine->loadBaseList("data/maps/base/object.bases", objectBase);
    theEngine->loadSprites("data/maps/level0/level0.objects", theObjects, objectBase, screen);
    
    theEngine->loadBaseList("data/maps/base/doors.bases", doorBase);
    
    theEngine->loadMusic("data/maps/base/music.bases", *&theMusic);
    
    
	//Setup the new start map
	level = 0;
    badGuys.clear();
    loadLevel(theEngine, theMap, surfaces, mapXPos, mapYPos, 3, 2, "data/maps/level0/level0.map"); 
    theEngine->loadSprites("data/maps/level0/level0.doors", theDoors, doorBase, screen);
    //Good Guy Sprites
    theEngine->loadSprites("data/maps/level0/level0.goodguy", goodGuys, goodBase, screen);


    //Sets up the inventory items, background and transparency
    thePlayer->buildInventory(theInventory);   
    SDL_Surface *invback = IMG_Load("data/images/backgrounds/inventory.png");;
    SDL_Surface *mBackReplacement = SDL_DisplayFormat(invback);
    SDL_SetColorKey(invback, SDL_SRCCOLORKEY, SDL_MapRGB(invback->format, 72, 152, 72));
    mBackReplacement = SDL_DisplayFormat(invback);

    //Load config file for audio settings
    audioflag = theEngine->loadConfig("data/game.cfg");
    
    /*---------------------------Game Background Music---------------------*/

    //0 = music is not paused 1 = paused.
    int musicPaused = 0;
    int paused = 0;
    int inventory = 0;
    int inventoryRun =0;
    
    if (audioflag)
    {
        //Setup the Sound
        theEngine->Sound->initSound(22050, AUDIO_S16, 2, 4096, 222);
    
        //Play the music
        theEngine->Sound->playMusic(theMusic[0].c_str(), 1, 10000, 0, 0);
        /*---------------------------------------------------------------------*/
    }
    
    SDL_Surface *f = IMG_Load("data/font/fonta.png"); 
    font = new SFont(f);
    
    SDL_Surface *fp = IMG_Load("data/font/fontb.png"); 
    fontp = new SFont(fp);
    
    SDL_Surface *fc = IMG_Load("data/font/fontc.png"); 
    fontc = new SFont(fc);
    
    /*==============================GAME LOOP=====================================*/
    SDL_ShowCursor(SDL_DISABLE);
    int intro=0;
    int done=0;
        
    string items[3] = {"Play", "Quit"};
    Menu *theMenu = new Menu(items, 2);
    
    //paused menu
    string item[4] = {"PAUSED", "Continue and Don't Save", "Save and Continue", "Save and Quit"};
    Menu *pMenu = new Menu(item, 4); 
    
    //Profile Menu
    string profileitem[5] = {"1.", "2.", "3.", "Erase Player", "Quit"};
    Menu *theMenu2 = new Menu(profileitem, 5); 
    
    //Profile Erase Menu
    string eraseitem[4] = {"1.", "2.", "3.", "Cancel"};
    Menu *theMenu3 = new Menu(eraseitem, 4); 
    
    int load_index = 0;
    
            
    SDL_Surface *introimage;
                        
    SDL_Surface *menuimage;
        
    
    
    while(intro == 0)
    {
        SDL_Event event;
        
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                intro = 3;
                done =1;
            }
            
        
        if (event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_F2)
                {
                    if (audioflag)
                        musicPaused=!musicPaused;
                }
                
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    	SDL_Quit();
                	return 0;
                }
                
                if(event.key.keysym.sym == SDLK_DOWN)
                {
                    if (load_index < 1)
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
            }
                
            if(event.key.keysym.sym == SDLK_RETURN)
            {
                if(theMenu->theMenu.at(0)->selected)
                {
                    input_delay =0;
                    intro = 1;
                     if (audioflag)
                     {
                     //Change the music
                     theEngine->Sound->playMusic(theMusic[1].c_str(), -1, 10000, 0, 0);
                     /*---------------------------------------------------------------------*/
                     }
                    
                }
                else if (theMenu->theMenu.at(1)->selected)
                {
                    done = 1;
                    intro = 3;
                }    
            }
        }
        
        if (audioflag)
        {                
            if(musicPaused)
            {
                theEngine->Sound->music("pause", 0 ,0);
            }
            if(!musicPaused)
            {
                theEngine->Sound->music("resume", 0, 0);
            }
        }
        
        introimage = IMG_Load("data/images/backgrounds/intro.png");
                        
        menuimage = theMenu->DrawMenu(120, 40, 0, 0, 0, false);
        
        SDL_Rect src;
        src.x = 0;
        src.y = 0;
        src.w = 120;
        src.h = 200;
        
        SDL_Rect dest;
        dest.x = 270;
        dest.y = 360;
        dest.w = 120;
        dest.h = 80;
        
        SDL_BlitSurface(menuimage, &src, introimage, &dest); 
        SDL_FreeSurface(menuimage);
        theEngine->Display->drawSurface(introimage, 0,0, 0, 0, screen);
        
        SDL_Flip(screen);
        
        SDL_FreeSurface(introimage);
    }
    
 //mine   
    while((intro == 1) ||(intro==2))
    {
        gTimer2 = SDL_GetTicks();
        ++input_delay;
        SDL_Event event;
        
        if(intro==1)
        {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                intro = 1;
                done =1;
            }
            
        if (event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_F2)
                {
                    if (audioflag)
                        musicPaused=!musicPaused;
                }
                
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    	SDL_Quit();
                	return 0;
                }
                
                if(event.key.keysym.sym == SDLK_DOWN)
                {
                    if (load_index < 4)
                    {
                        theMenu2->theMenu.at(load_index)->selected = false;
                        load_index++;
                        theMenu2->theMenu.at(load_index)->selected = true;
                    }
                }
                if(event.key.keysym.sym == SDLK_UP)
                {
                    if (load_index > 0)
                    {
                        theMenu2->theMenu.at(load_index)->selected = false;
                        load_index--;
                        theMenu2->theMenu.at(load_index)->selected = true;
                    }
                }
            }
                
            if((event.key.keysym.sym == SDLK_RETURN) && (input_delay > 10))
            {
                if(theMenu2->theMenu.at(0)->selected)
                {
                     current.setFile("save/Profile1.txt");
                     if (current.load("Hearts")!=9999)
                     {
                        current.loadAll(thePlayer, screen);
                        if (((thePlayer->getProgress()==1) && (current.load("Lamp")==0)) || (thePlayer->getProgress()>1))
                           goodGuys.clear();     
                        if (current.load("Lamp")>0)
                           theObjects[0]->setVisible(false);
                     }
                     else
                     {
                         string s;

                         s = profileName(screen, font);
                         thePlayer->setName(s);
                     }
                     if (audioflag)
                     {
                     //Change the music
                     theEngine->Sound->stopMusic(1, 0);
                     /*---------------------------------------------------------------------*/
                     }
                     
                     intro=3;
                }
                else if (theMenu2->theMenu.at(1)->selected)
                {
                     current.setFile("save/Profile2.txt");
                     if (current.load("Hearts")!=9999)
                     {
                        current.loadAll(thePlayer, screen);
                        if (((thePlayer->getProgress()==1) && (current.load("Lamp")==0)) || (thePlayer->getProgress()>1))
                           goodGuys.clear();     
                        if (current.load("Lamp")>0)
                           theObjects[0]->setVisible(false);  
                     }
                     
                     else
                     {
                         string s;

                         s = profileName(screen, font);
                         thePlayer->setName(s);
                     }
                     if (audioflag)
                     {
                     //Change the music
                     theEngine->Sound->stopMusic(1, 0);
                     /*---------------------------------------------------------------------*/
                     }
                     intro=3;
                }    
                else if (theMenu2->theMenu.at(2)->selected)
                {
                     current.setFile("save/Profile3.txt");
                     if (current.load("Hearts")!=9999)
                     {
                        current.loadAll(thePlayer, screen);
                        if (((thePlayer->getProgress()==1) && (current.load("Lamp")==0)) || (thePlayer->getProgress()>1))
                           goodGuys.clear();  
                        if (current.load("Lamp")>0)
                           theObjects[0]->setVisible(false);
                            
                     }
                     else
                     {
                         string s;

                         s = profileName(screen, font);
                         thePlayer->setName(s);
                     }
                     if (audioflag)
                     {
                     //Change the music
                     theEngine->Sound->stopMusic(1, 0);
                     /*---------------------------------------------------------------------*/
                     }
                     
                     intro=3;
                }    
                else if (theMenu2->theMenu.at(3)->selected)
                {
                     theMenu3->theMenu.at(0)->selected = true;
                     theMenu3->theMenu.at(1)->selected = false;
                     theMenu3->theMenu.at(2)->selected = false;
                     theMenu3->theMenu.at(3)->selected = false;
                     input_delay=0;
                     load_index=0;
                     intro = 2;
                }  
                else if (theMenu2->theMenu.at(4)->selected)
                {
                     intro = 3;
                     done =1;
                }  
            }
        }

        
        introimage = IMG_Load("data/images/backgrounds/intro2.png");
                        
        menuimage = theMenu2->DrawMenu(250, 50, 0, 0, 0, false);
        
        SDL_Rect src;
        src.x = 0;
        src.y = 0;
        src.w = 300;
        src.h = 400;
        
        SDL_Rect dest;
        dest.x = 100;
        dest.y = 150;
        dest.w = 300;
        dest.h = 400;
        
        
        file temp;
        char*  templist[] = {"save/Profile1.txt", "save/Profile2.txt", "save/Profile3.txt"};   
        string tempnames[3];
        vector <vector<sprite *> > profiles;
        profiles.resize(3);
        int templocations[]= {160, 210, 262}; 
        
        for (int m=0; m<3; m++)
        {
        temp.setFile(templist[m]);
        if (temp.load("Hearts")!=9999)
        {
               int y=templocations[m];
               int life = 0;
               profiles[m].resize(temp.load("Hearts"));   
               for (int k=0; k<= temp.load("Hearts")/10 ; k++)
               { 
                   for(unsigned int i=0;i<10;i++)
                   {            if (life<profiles[m].size())
                                {
                                    profiles[m][life] = new sprite;
	                                profiles[m][life]->initSprite("data/images/items/life2.png", menuimage, 250+(i*25), y, 17, 24);
	                                life++;
                                 }
                   }
                   y+=25;
               }
        }
        
        tempnames[m] = temp.loadName();
        }
        
	    SDL_BlitSurface(menuimage, &src, introimage, &dest); 
        SDL_FreeSurface(menuimage);
        theEngine->Display->drawSurface(introimage, 0,0, 0, 0, screen);


        for (int m=0; m<3; m++)
        {
            if ( profiles[m].size() != 0)
            {
	           for (int j=0; j< profiles[m].size(); j++)
               { 
                  dr.drawSprite(profiles[m][j], theEngine, screen);
               }
            }
        }
        
        for (int m=0; m<3; m++)
        {
            if (tempnames[m].compare( "0" )!=0)
            {
               int fw = (fontc->getTextWidth(tempnames[m]))/2;
               fontc->write(screen,tempnames[m],180-fw,templocations[m]-10);
            }
        }
                
        SDL_Flip(screen);
        
        SDL_FreeSurface(introimage);
        
        }
        if(intro==2)
        {
                    
         while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                intro = 1;
                done =1;
            }
            
        if (event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_F2)
                {
                    if (audioflag)
                        musicPaused=!musicPaused;
                }
                
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    	SDL_Quit();
                	return 0;
                }
                
                if(event.key.keysym.sym == SDLK_DOWN)
                {
                    if (load_index < 3)
                    {
                        theMenu3->theMenu.at(load_index)->selected = false;
                        load_index++;
                        theMenu3->theMenu.at(load_index)->selected = true;
                    }
                }
                if(event.key.keysym.sym == SDLK_UP)
                {
                    if (load_index > 0)
                    {
                        theMenu3->theMenu.at(load_index)->selected = false;
                        load_index--;
                        theMenu3->theMenu.at(load_index)->selected = true;
                    }
                }
            }
                
           if((event.key.keysym.sym == SDLK_RETURN) && (input_delay > 10))
            {
                if(theMenu3->theMenu.at(0)->selected)
                {
                     current.setFile("save/Profile1.txt");
                     current.erase();
                     theMenu2->theMenu.at(0)->selected = true;
                     theMenu2->theMenu.at(1)->selected = false;
                     theMenu2->theMenu.at(2)->selected = false;
                     theMenu2->theMenu.at(3)->selected = false;
                     load_index=0;
                     intro=1;
                     input_delay=0;
                }
                else if (theMenu3->theMenu.at(1)->selected)
                {
                     current.setFile("save/Profile2.txt");
                     current.erase();
                     theMenu2->theMenu.at(0)->selected = true;
                     theMenu2->theMenu.at(1)->selected = false;
                     theMenu2->theMenu.at(2)->selected = false;
                     theMenu2->theMenu.at(3)->selected = false;
                     load_index=0;
                     intro=1;
                     input_delay=0;
                }    
                else if (theMenu3->theMenu.at(2)->selected)
                {
                     current.setFile("save/Profile3.txt");
                     current.erase();
                     theMenu2->theMenu.at(0)->selected = true;
                     theMenu2->theMenu.at(1)->selected = false;
                     theMenu2->theMenu.at(2)->selected = false;
                     theMenu2->theMenu.at(3)->selected = false;
                     load_index=0;
                     intro=1;
                     input_delay=0;
                }    
                else if (theMenu3->theMenu.at(3)->selected)
                {
                     theMenu2->theMenu.at(0)->selected = true;
                     theMenu2->theMenu.at(1)->selected = false;
                     theMenu2->theMenu.at(2)->selected = false;
                     theMenu2->theMenu.at(3)->selected = false;
                     load_index=0;
                     intro = 1;
                     input_delay=0;
                }  
            }
        }

        
        introimage = IMG_Load("data/images/backgrounds/intro2.png");
                        
        menuimage = theMenu3->DrawMenu(180, 50, 0, 0, 0, false);
        
        SDL_Rect src;
        src.x = 0;
        src.y = 0;
        src.w = 300;
        src.h = 400;
        
        SDL_Rect dest;
        dest.x = 100;
        dest.y = 150;
        dest.w = 300;
        dest.h = 400;
        
        file temp;
        char*  templist[] = {"save/Profile1.txt", "save/Profile2.txt", "save/Profile3.txt"};   
        string tempnames[3];
        vector <vector<sprite *> > profiles;
        profiles.resize(3);
        int templocations[]= {160, 210, 262}; 
        
        for (int m=0; m<3; m++)
        {
         temp.setFile(templist[m]);
         if (temp.load("Hearts")!=9999)
         {
               int y=templocations[m];
               int life = 0;
               profiles[m].resize(temp.load("Hearts"));   
               for (int k=0; k<= temp.load("Hearts")/10 ; k++)
               { 
                   for(unsigned int i=0;i<10;i++)
                   {            if (life<profiles[m].size())
                                {
                                    profiles[m][life] = new sprite;
	                                profiles[m][life]->initSprite("data/images/items/life2.png", menuimage, 250+(i*25), y, 17, 24);
	                                life++;
                                 }
                   }
                   y+=25;
               }
         }
        
         tempnames[m] = temp.loadName();
        }
        
	    SDL_BlitSurface(menuimage, &src, introimage, &dest); 
        SDL_FreeSurface(menuimage);
        theEngine->Display->drawSurface(introimage, 0,0, 0, 0, screen);


        for (int m=0; m<3; m++)
        {
            if ( profiles[m].size() != 0)
            {
	           for (int j=0; j< profiles[m].size(); j++)
               { 
                  dr.drawSprite(profiles[m][j], theEngine, screen);
               }
            }
        }
        
        for (int m=0; m<3; m++)
        {
            if (tempnames[m].compare( "0" )!=0)
            {
               int fw = (fontc->getTextWidth(tempnames[m]))/2;
               fontc->write(screen,tempnames[m],180-fw,templocations[m]-10);
            }
        }
        
        SDL_Flip(screen);
        
        SDL_FreeSurface(introimage);           
                    
        }
        if (audioflag)
        {                
            if(musicPaused)
            {
                theEngine->Sound->music("pause", 0 ,0);
            }
            if(!musicPaused)
            {
                theEngine->Sound->music("resume", 0, 0);
            }
        }
    }
    
    
    while((done == 0)&&(intro==3))
    {
                
        if(thePlayer->getLife() <= 0)
        {
                                
            if (audioflag)
                theEngine->Sound->playEffect("data/sound/effects/dying.wav", "play", 0,0);
            

            int action = endGame(screen);
          
            if(action == 1)
	        {
	            //Free up memory...
                delete theEngine;
                delete thePlayer;
                delete font;
                delete fontp;
                delete pMenu;
                
                theEngine = NULL;
                thePlayer = NULL;
                font = NULL;
                fontp = NULL;
                pMenu = NULL;
                
                SDL_Quit();
                return 0;
	        }
	        else if(action == 0)
	        { 
	            level = 0;
                string s;                
                s=thePlayer->getName();
		        badGuys.clear();
		        goodGuys.clear();
		        theObjects.clear();
		        theDoors.clear();
		        delete thePlayer;
                thePlayer = NULL;
		        loadLevel(theEngine, theMap, surfaces, mapXPos, mapYPos, 3, 2, "data/maps/level0/level0.map"); 
		        theEngine->loadSprites("data/maps/level0/level0.doors", theDoors, doorBase, screen);
		        //Good Guy Sprites
                theEngine->loadSprites("data/maps/level0/level0.goodguy", goodGuys, goodBase, screen); 
		        //Player
		        theEngine->loadPlayer("data/maps/level0/level0.player", thePlayer, playerBase, screen, arrowBase, boomerangBase);
                //Object Sprites
                theEngine->loadSprites("data/maps/level0/level0.objects", theObjects, objectBase, screen); 
                

                thePlayer->setName(s);
                
                theInventory.clear();
                theEngine->loadSprites("data/maps/level0.inventory", theInventory, invBase, screen);
                
		        thePlayer->buildInventory(theInventory);   
		        
                if (current.load("Hearts")!=9999)
                {
                        current.loadAll(thePlayer, screen);
                         
                        if (((thePlayer->getProgress()==1) && (current.load("Lamp")==0)) || (thePlayer->getProgress()>1))
                           goodGuys.clear();  
                        if (current.load("Lamp")>0)
                           theObjects[0]->setVisible(false);
                }
                
                if (audioflag)
                     {
                     //Change the music
                     theEngine->Sound->stopMusic(1, 0);
                     /*---------------------------------------------------------------------*/
                     }
                
	        }
        }
        
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                done = 1;
            }
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    done = 1;
                }
                if(event.key.keysym.sym == SDLK_F2)
                {
                    musicPaused=!musicPaused;
                }
                if(event.key.keysym.sym == SDLK_F12)
                {
                   
                    string cheatcodes[] = {"god", "speed", "unlim", "gimme", "magic", "bow", "boom", "bomb", "bottl", "shovl", "hpce", "whrt", "kill", "cou", "pow", "wis"};   
                    string s;
                    s = enterCheat(screen, font);
                    if (cheatcodes[0].compare(s)==0)
                    {
                        if (cheats[0]==0)
                           cheats[0]=1;
                        else
                            cheats[0]=0;
                    }
                    else if (cheatcodes[1].compare(s)==0)
                    {
                        if (thePlayer->getSpeed()==12)
                           thePlayer->setSpeed(2);
                        else
                            thePlayer->setSpeed(12);
                    }
                    else if (cheatcodes[2].compare(s)==0)
                        cheats[1]=1;
                    else if (cheatcodes[3].compare(s)==0)
                    {
                         thePlayer->setArrows(thePlayer->getArrows()+20);
                         thePlayer->setBombs(thePlayer->getBombs()+20);
                         thePlayer->setRupees(thePlayer->getRupees()+20);
                    }
                    else if (cheatcodes[4].compare(s)==0)
                    {
                         thePlayer->setMagic(thePlayer->getMagic()+25);
                    }
                    else if (cheatcodes[5].compare(s)==0)
                    {
                         thePlayer->addItem(0);
                    }
                    else if (cheatcodes[6].compare(s)==0)
                    {
                         thePlayer->addItem(1);
                    }
                    else if (cheatcodes[7].compare(s)==0)
                    {
                         thePlayer->addItem(2);
                    }
                    else if (cheatcodes[8].compare(s)==0)
                    {
                         thePlayer->addItem(3);
                    }
                    else if (cheatcodes[9].compare(s)==0)
                    {
                         thePlayer->addItem(5);
                    }
                    else if (cheatcodes[10].compare(s)==0)
                    {
                         thePlayer->setPieces(thePlayer->getPieces()+1, screen);
                    }
                    else if (cheatcodes[11].compare(s)==0)
                    {
                         thePlayer->setPieces(4, screen);
                    }
                    else if (cheatcodes[12].compare(s)==0)
                    {
                         thePlayer->setLife(0);
                    }
                    else if (cheatcodes[13].compare(s)==0)
                    {
                         thePlayer->addItem(10);
                    }
                    else if (cheatcodes[14].compare(s)==0)
                    {
                         thePlayer->addItem(12);
                    }
                    else if (cheatcodes[15].compare(s)==0)
                    {
                         thePlayer->addItem(11);
                    }
                }
                if(event.key.keysym.sym == SDLK_F1)
                {
                         helpText(screen, thePlayer);               
                }
                if(event.key.keysym.sym == SDLK_p)
                {
                    if(!inventory)
                    {
                        paused=!paused;
                        musicPaused=!musicPaused;
                                    pMenu->theMenu.at(0)->selected = false;
                                    pMenu->theMenu.at(1)->selected = true;
                                    pMenu->theMenu.at(2)->selected = false;
                                    pMenu->theMenu.at(3)->selected = false;
                                    load_index=1;
                    }                
                }
                if(event.key.keysym.sym == SDLK_DOWN)
                {
                    if ((load_index < 3)&&(paused))
                   {
                        pMenu->theMenu.at(load_index)->selected = false;
                        load_index++;
                        pMenu->theMenu.at(load_index)->selected = true;
                    }
                }
                if(event.key.keysym.sym == SDLK_UP)
                {
                    if ((load_index > 1)&&(paused))
                    {
                        pMenu->theMenu.at(load_index)->selected = false;
                        load_index--;
                        pMenu->theMenu.at(load_index)->selected = true;
                    }
                }
                if(event.key.keysym.sym == SDLK_i)
                {
                    if(!paused)
                        inventory=!inventory;
                }
                if((event.key.keysym.sym == SDLK_x) && (input_delay > 10))
                {
                    //Only lets the player shoot arrows when the bow is selected and the player has some arrows                     
                    if ((thePlayer->getArrows()!=0 || (cheats[1]==1))&&(thePlayer->returnInventory()[0]->getSelected())&&(thePlayer->getHeld()))
                    {             
                    if (audioflag)
                        theEngine->Sound->playEffect("data/sound/effects/arrow_shoot.wav", "play", 0,0);
                    thePlayer->fireArrow();
                    if (cheats[1]==0)
                    thePlayer->setArrows(thePlayer->getArrows()-1);
                    }  
                    else if (thePlayer->returnInventory()[1]->getSelected())
                    {             
                    if (audioflag)
                        theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Boomerang.wav", "play", 0,0);
                        thePlayer->boomerang();
                    }   
                    else if ((thePlayer->returnInventory()[4]->getSelected()) && (thePlayer->getMagic()>=20))
                    {             
                    if (audioflag)
                        theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Lamp.wav", "play", 0,0);
                        thePlayer->lamp();
                    }                      
     
		            input_delay =0;
                }
                if((event.key.keysym.sym == SDLK_SPACE) && (input_delay > 10))
                {
                    if (thePlayer->getSlashing()== false)
                    {
                        if (audioflag)
                            theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Sword1.wav", "play", 0,0);
                        thePlayer->slash();
                    }
     
		            input_delay = 0;
                }
                if((event.key.keysym.sym == SDLK_RETURN)&&(paused))
                {
                    if(pMenu->theMenu.at(1)->selected)
                    {                        
                         paused=!paused;
                         musicPaused=!musicPaused;
                    }
                    else if (pMenu->theMenu.at(2)->selected)
                    {
                         current.save(thePlayer);
                         paused=!paused;
                         musicPaused=!musicPaused;
                    }    
                    else if (pMenu->theMenu.at(3)->selected)
                    {
                         current.save(thePlayer);
                         intro = 3;
                         done =1;
                    }    
                }  
                if((event.key.keysym.sym == SDLK_RETURN)&&(inventory)) 
                {
                     if (thePlayer->returnInventory()[theCursor->getIndex()]->getVisible())
                     {                       
                     if (audioflag)                        
                     theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Menu_Select.wav", "play", 0,0);
                     thePlayer->selectItem(theCursor->getIndex());
                     }
                }            
            }
        }
        
        if (audioflag)
        {                        
            if(musicPaused)
            {
                theEngine->Sound->music("pause", 0 ,0);
            }
            if(!musicPaused)
            {
                theEngine->Sound->music("resume", 0, 0);
            }
        }
        
        if(inventory)
        {
            input_delay++; 
            SDL_Rect src;
            src.x = 0;
            src.y = 0;
            src.w = 640;
            src.h = 480;
        
            SDL_Rect dest;
            dest.x = 0;
            dest.y = 0;
            dest.w = 640;
            dest.h = 480;  

            SDL_BlitSurface(screen, &src, mBackReplacement, NULL);
            SDL_BlitSurface(invback, &src, screen, &dest);  
            SDL_Surface *i = thePlayer->drawInventory();

            SDL_BlitSurface(i, &src, screen, &dest); 
            
            //Draws all of the items for the main inventory area
            for (int i=0; i<6;i++)
            {
                 if (thePlayer->returnInventory()[i]->getVisible())
                 dr.drawSprite(thePlayer->returnInventory()[i], theEngine, screen);
            }
            
            //Draws the icon for the current number of heartpieces
            dr.drawSprite(thePlayer->returnInventory()[6+thePlayer->getPieces()], theEngine, screen);
            
            
            for (int i=10; i<14;i++)
            {
                 if (thePlayer->returnInventory()[i]->getVisible())
                 dr.drawSprite(thePlayer->returnInventory()[i], theEngine, screen);
            }
                      
            //Handles the cursor movement
            if (input_delay > 5)
            {
            bool playSound = theCursor->move(keys, thePlayer);
            if (audioflag && playSound)
              theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Menu_Cursor.wav", "play", 0,0);
            input_delay=0;
            }
            //Draws the cursor
            dr.drawSprite(theCursor, curs, theEngine, screen);
            
            SDL_FreeSurface(i);
            
            SDL_Flip(screen);
            
        }

        if(paused)
        {
            SDL_Surface *menu = pMenu->DrawMenu(420, 40, 72, 152, 72, true);
            
            SDL_Rect src;
            src.x = 0;
            src.y = 0;
            src.w = 420;
            src.h = 200;
        
            SDL_Rect dest;
            dest.x = 110;
            dest.y = 215;
            dest.w = 420;
            dest.h = 200;
                
            
            SDL_BlitSurface(menu, &src, screen, &dest); 
            
            SDL_FreeSurface(menu);
            
            SDL_Flip(screen);
        }   
        if (!paused && !inventory)
        {
            //Control the rate at which the game is drawn
            if((SDL_GetTicks() - gTimer) >= FRAME_RATE)
            {

                //---------------------CHECK FOR PLAYER COLLISIONS-----------------------------------\\

                //RUN LEVEL SPECIFIC CODE HERE???
                lv.levelCode(badGuys, goodGuys, theObjects, thePlayer, theEngine, screen, back, theMap, screenInfo, theDoors, backSurface, surfaces, mapXPos, mapYPos, mapX, mapY, tileHeight, tileWidth, backX, backY, screenWidth, screenHeight, audioflag, level, font, itemBase, uItems, cheats);

                //---------------------END CHECK FOR COLLISIONS-------------------------------\\


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

                //-------------------------------MOVE PLAYER AND STUFF---------------------------------\\

                if (audioflag)
                {        
                    if(event.key.keysym.sym == SDLK_PAGEDOWN)
                    {
                        theEngine->Sound->music("setVolume", 0, theEngine->Sound->music("getVolume", 0, 0)-1);
                    }
                    if(event.key.keysym.sym == SDLK_PAGEUP)
                    {
                        theEngine->Sound->music("setVolume", 0, theEngine->Sound->music("getVolume", 0, 0)+1);
                    }
                }
                 
                keys = SDL_GetKeyState(NULL);
                

                int i;
                int j;
                //Can we move the player??
                //fixes problems from certain directions
                if ((thePlayer->getDirection()=='E') ||  (thePlayer->getDirection()=='N') || (thePlayer->getDirection()=='S') )
                    j=((mapX-thePlayer->getX()-12)/tileWidth);
                else
                    j=((mapX-thePlayer->getX()-10)/tileWidth);
                i=((mapY-thePlayer->getY()-thePlayer->getH()+1)/tileHeight);
                //Changed for new tiles
                if((theMap[-i][-j] == 0) || (theMap[-i][-j] == 10) || (theMap[-i][-j] == 19) || (theMap[-i][-j] == 77) || (theMap[-i][-j] == 158) || (theMap[-i][-j] == 260) || (theMap[-i][-j] == 261) || (theMap[-i][-j] == 264) || (theMap[-i][-j] == 265) || (theMap[-i][-j] == 338) || ((theMap[-i][-j] >= 215) && (theMap[-i][-j] <= 219)) || ((theMap[-i][-j] >= 297) && (theMap[-i][-j] <= 303)))
                {
                    thePlayer->setOldX(thePlayer->getX());
                    thePlayer->setOldY(thePlayer->getY());
                    thePlayer->move(keys, backX, mapX, xOffset, backY, mapY, yOffset, screenWidth, screenHeight, levelWidth, levelHeight, tileWidth, tileHeight, theMap);
                }
                else
                {
                    thePlayer->setX(thePlayer->getOldX());
                    thePlayer->setY(thePlayer->getOldY());
                }
		
		
		//Has the player reached a gate???
        //Check to see if the Player has entered a door to the other world!
         
         for (int i=0; i<theDoors.size(); i++)
         {
    		if((theEngine->spriteCollide(thePlayer, theDoors[i]) == 1))
    		{
                if((level == 0) &&  (thePlayer->getProgress()>1))
                {
                    level = 1;
    			    badGuys.clear();
    		        goodGuys.clear();
    		        theObjects.clear();
    		        theDoors.clear();
    		        uItems.clear();
    		        loadLevel(theEngine, theMap, surfaces, mapXPos, mapYPos, 13, 16, "data/maps/level1/level1.map"); 
		            theEngine->loadSprites("data/maps/level1/level0.doors", theDoors, doorBase, screen);
    			    //Bad Guy Sprites
                    theEngine->loadSprites("data/maps/level1/level0.badguy", badGuys, badBase, screen, arrowBase);
		            thePlayer->setX(390);
		            thePlayer->setY(250);
		            thePlayer->setHeld();
                     if (audioflag)
                     {
                     //Change the music
                     theEngine->Sound->playMusic(theMusic[2].c_str(), -1, 10000, 0, 0);
                     /*---------------------------------------------------------------------*/
                     }
    		    }	
    		    else if((level == 1) && (i==0))
                {
                    level = 0;
		            badGuys.clear();
		            goodGuys.clear();
		            theObjects.clear();
		            theDoors.clear();
		            uItems.clear();
		            loadLevel(theEngine, theMap, surfaces, mapXPos, mapYPos, 3, 2, "data/maps/level0/level0.map"); 
		            theEngine->loadSprites("data/maps/level0/level0.doors", theDoors, doorBase, screen);
	                //Good Guy Sprites
                    theEngine->loadSprites("data/maps/level0/level0.goodguy", goodGuys, goodBase, screen);
		            thePlayer->setX(385);
		            thePlayer->setY(320);
		            thePlayer->setDirection('N');
		            thePlayer->setHeld();
                
                    if (thePlayer->getProgress()>0)
                        goodGuys.clear(); 
                   
                   if (audioflag)
                     {
                     //Change the music
                     theEngine->Sound->stopMusic(1, 0);
                     /*---------------------------------------------------------------------*/
                     }
               }
               else if((level == 1) && (i==1))
               {
                    level = 4;
    			    badGuys.clear();
    		        goodGuys.clear();
    		        theObjects.clear();
    		        theDoors.clear();
    		        uItems.clear();
     	            loadLevel(theEngine, theMap, surfaces, mapXPos, mapYPos, 15, 29, "data/maps/castle/castle.map"); 
     	            theEngine->loadSprites("data/maps/castle/level0.doors", theDoors, doorBase, screen);
    			    //Bad Guy Sprites
                    theEngine->loadSprites("data/maps/castle/level0.badguy", badGuys, badBase, screen, arrowBase);
                    thePlayer->setX(420);
                    thePlayer->setY(480);
                    thePlayer->setHeld();
                    if (audioflag)
                     {
                     //Change the music
                     theEngine->Sound->playMusic(theMusic[4].c_str(), -1, 10000, 0, 0);
                     /*---------------------------------------------------------------------*/
                     }
               }
   		       else if((level == 1) && (i==2))
               {
                    level = 2;
    			    badGuys.clear();
    		        goodGuys.clear();
    		        theObjects.clear();
    		        theDoors.clear();
    		        uItems.clear();
     	            loadLevel(theEngine, theMap, surfaces, mapXPos, mapYPos, 0, 11, "data/maps/level2/level.map"); 
    		        theEngine->loadSprites("data/maps/level2/level.doors", theDoors, doorBase, screen);
                    //Good Guy Sprites
                    theEngine->loadSprites("data/maps/level2/level.goodguy", goodGuys, goodBase, screen);
                    //Bad Guy Sprites
                    theEngine->loadSprites("data/maps/level2/level.badguy", badGuys, badBase, screen, arrowBase);
                    //Object Sprites
                    theEngine->loadSprites("data/maps/level2/level.objects", theObjects, objectBase, screen);  
                    if (thePlayer->returnInventory()[13]->getVisible())
                    {
                         theObjects[0]->setVisible(false);
                         goodGuys[2]->setVisible(false);
                    }
                    thePlayer->setX(65);
                    thePlayer->setY(260);
                    thePlayer->setHeld();
               }
  		       else if((level == 1) && (i==3))
               {
                    //Change this
                    level = 5;
    			    badGuys.clear();
    		        goodGuys.clear();
    		        theObjects.clear();
    		        theDoors.clear();
    		        uItems.clear();
     	            loadLevel(theEngine, theMap, surfaces, mapXPos, mapYPos, 28, 0, "data/maps/desert1/desert1.map"); 
    		        theEngine->loadSprites("data/maps/desert1/level.doors", theDoors, doorBase, screen);
                    //Bad Guy Sprites
                    theEngine->loadSprites("data/maps/desert1/level.badguy", badGuys, badBase, screen, arrowBase);
    			    thePlayer->setX(300);
    		        thePlayer->setY(50);
    		        thePlayer->setHeld();
               } 
  		       else if((level == 1) && (i==4))
               {
                    level = 6;
    			    badGuys.clear();
    		        goodGuys.clear();
    		        theObjects.clear();
    		        theDoors.clear();
    		        uItems.clear();
     	            loadLevel(theEngine, theMap, surfaces, mapXPos, mapYPos, 39, 29, "data/maps/forest/forest.map"); 
    		        theEngine->loadSprites("data/maps/forest/level.doors", theDoors, doorBase, screen);
                    //Good Guy Sprites
                    theEngine->loadSprites("data/maps/forest/level.goodguy", goodGuys, goodBase, screen);
                    if (thePlayer->getProgress()==100)
                       goodGuys[0]->setVisible(false);
    			    thePlayer->setX(500);
    		        thePlayer->setY(400);
    		        thePlayer->setHeld();
                    if (audioflag)
                     {
                     //Change the music
                     theEngine->Sound->playMusic(theMusic[5].c_str(), -1, 10000, 0, 0);
                     /*---------------------------------------------------------------------*/
                     }
               } 
                else if((level == 2) && (i==0) && (thePlayer->returnInventory()[0]->getVisible()))
                {
    		        level = 3;
    			    badGuys.clear();
    		        goodGuys.clear();
    		        theObjects.clear();
    		        theDoors.clear();
    		        uItems.clear();
     	            loadLevel(theEngine, theMap, surfaces, mapXPos, mapYPos, 20, 29, "data/maps/level3/level.map"); 
    		        theEngine->loadSprites("data/maps/level3/level.doors", theDoors, doorBase, screen);
                    //Good Guy Sprites
                    theEngine->loadSprites("data/maps/level3/level.goodguy", goodGuys, goodBase, screen);
                    //Bad Guy Sprites
                    theEngine->loadSprites("data/maps/level3/level.badguy", badGuys, badBase, screen, arrowBase);
                    //Object Sprites
                    theEngine->loadSprites("data/maps/level3/level.objects", theObjects, objectBase, screen);  
                    if (thePlayer->returnInventory()[10]->getVisible())
                    {
                         theObjects[0]->setVisible(false);
                         goodGuys[0]->setVisible(false);
                    }
                    if (thePlayer->getCollected(1))
                    {
                         theObjects[1]->setVisible(false);
                    }  
    			    thePlayer->setX(270);
    		        thePlayer->setY(400);
    		        thePlayer->setHeld();
    		    }
                else if((level == 2) && (i==1))
                {
                    level = 1;
    			    badGuys.clear();
    		        goodGuys.clear();
    		        theObjects.clear();
    		        theDoors.clear();
    		        uItems.clear();
    		        loadLevel(theEngine, theMap, surfaces, mapXPos, mapYPos, 39, 20, "data/maps/level1/level1.map"); 
		            theEngine->loadSprites("data/maps/level1/level2.doors", theDoors, doorBase, screen);
    			    //Bad Guy Sprites
                    theEngine->loadSprites("data/maps/level1/level2.badguy", badGuys, badBase, screen, arrowBase);
		            thePlayer->setX(550);
		            thePlayer->setY(300);
		            thePlayer->setHeld();
    		    }	
                else if((level == 3)&& (i==0))
                {
    		        level = 2;
    			    badGuys.clear();
    		        goodGuys.clear();
    		        theObjects.clear();
    		        theDoors.clear();
    		        uItems.clear();
    		        loadLevel(theEngine, theMap, surfaces, mapXPos, mapYPos, 20, 0, "data/maps/level2/level.map"); 
    		        theEngine->loadSprites("data/maps/level2/level1.doors", theDoors, doorBase, screen);
    			    //Bad Guy Sprites
                    theEngine->loadSprites("data/maps/level2/level1.badguy", badGuys, badBase, screen, arrowBase);
                    theEngine->loadSprites("data/maps/level2/level1.goodguy", goodGuys, goodBase, screen);
    			    thePlayer->setX(400);
    		        thePlayer->setY(42);
                    thePlayer->setHeld(); 
    		    }	
               else if((level == 4) && (i==0))
               {
                    level = 1;
    			    badGuys.clear();
    		        goodGuys.clear();
    		        theObjects.clear();
    		        theDoors.clear();
    		        uItems.clear();
    		        loadLevel(theEngine, theMap, surfaces, mapXPos, mapYPos, 13, 0, "data/maps/level1/level1.map"); 
		            theEngine->loadSprites("data/maps/level1/level1.doors", theDoors, doorBase, screen);
       			    //Bad Guy Sprites
                    theEngine->loadSprites("data/maps/level1/level1.badguy", badGuys, badBase, screen, arrowBase);
		            thePlayer->setX(350);
		            thePlayer->setY(50);
		            thePlayer->setHeld();
                    if (audioflag)
                     {
                     //Change the music
                     theEngine->Sound->playMusic(theMusic[2].c_str(), -1, 10000, 0, 0);
                     /*---------------------------------------------------------------------*/
                     }
               }
               else if((level == 4) && (i==1))
               {
                    level = 42;
    			    badGuys.clear();
    		        goodGuys.clear();
    		        theObjects.clear();
    		        theDoors.clear();
    		        uItems.clear();
    		        loadLevel(theEngine, theMap, surfaces, mapXPos, mapYPos, 37, 13, "data/maps/dungeon1/dungeon1.map"); 
		            theEngine->loadSprites("data/maps/dungeon1/level.doors", theDoors, doorBase, screen);
                    //Good Guy Sprites
                    theEngine->loadSprites("data/maps/dungeon1/level.goodguy", goodGuys, goodBase, screen);
                    //Object Sprites
                    theEngine->loadSprites("data/maps/dungeon1/level.objects", theObjects, objectBase, screen);  
    			    //Bad Guy Sprites
                    theEngine->loadSprites("data/maps/dungeon1/level.badguy", badGuys, badBase, screen, arrowBase);
		            thePlayer->setX(500);
		            thePlayer->setY(200);
		            thePlayer->setHeld();
                    if (audioflag)
                     {
                     //Change the music
                     theEngine->Sound->playMusic(theMusic[6].c_str(), -1, 10000, 0, 0);
                     /*---------------------------------------------------------------------*/
                     }
               }
               else if((level == 4) && (i==2))
               {
                    level = 6;
    			    badGuys.clear();
    		        goodGuys.clear();
    		        theObjects.clear();
    		        theDoors.clear();
    		        uItems.clear();
    		        loadLevel(theEngine, theMap, surfaces, mapXPos, mapYPos, 39, 16, "data/maps/forest/forest.map"); 
    		        theEngine->loadSprites("data/maps/forest/level1.doors", theDoors, doorBase, screen);
                    //Object Sprites
                    theEngine->loadSprites("data/maps/forest/level.objects", theObjects, objectBase, screen); 
                    if (thePlayer->getCollected(3))
                    {
                         theObjects[0]->setVisible(false);
                    }                               
		            thePlayer->setX(480);
		            thePlayer->setY(300);
		            thePlayer->setHeld();
                    if (audioflag)
                     {
                     //Change the music
                     theEngine->Sound->playMusic(theMusic[5].c_str(), -1, 10000, 0, 0);
                     /*---------------------------------------------------------------------*/
                     }
               }
               else if((level == 4) && (i==3))
               {
                    level = 43;
    			    badGuys.clear();
    		        goodGuys.clear();
    		        theObjects.clear();
    		        theDoors.clear();
    		        uItems.clear();
    		        loadLevel(theEngine, theMap, surfaces, mapXPos, mapYPos, 25, 29, "data/maps/dungeon2/dungeon2.map"); 
		            theEngine->loadSprites("data/maps/dungeon2/level1.doors", theDoors, doorBase, screen);
                    //Good Guy Sprites
                    theEngine->loadSprites("data/maps/dungeon2/level1.goodguy", goodGuys, goodBase, screen);
    			    //Bad Guy Sprites
                    theEngine->loadSprites("data/maps/dungeon2/level1.badguy", badGuys, badBase, screen, arrowBase);
		            thePlayer->setX(200);
		            thePlayer->setY(220);
		            thePlayer->setHeld();
                    if (thePlayer->getProgress()!=100)
                       goodGuys[2]->setVisible(false);
                    if (audioflag)
                     {
                     //Change the music
                     theEngine->Sound->playMusic(theMusic[6].c_str(), -1, 10000, 0, 0);
                     /*---------------------------------------------------------------------*/
                     }
               }
               else if((level == 4) && (i==4))
               {
                    thePlayer->setY(600);
               }
               else if((level == 4) && (i==5) && (thePlayer->returnInventory()[12]->getVisible()))
               {
                    thePlayer->setY(30);
               }
               else if((level == 42) && (i==0) &&(thePlayer->returnInventory()[1]->getVisible()))
               {
                    level = 43;
    			    badGuys.clear();
    		        goodGuys.clear();
    		        theObjects.clear();
    		        theDoors.clear();
    		        uItems.clear();
    		        loadLevel(theEngine, theMap, surfaces, mapXPos, mapYPos, 2, 0, "data/maps/dungeon2/dungeon2.map"); 
		            theEngine->loadSprites("data/maps/dungeon2/level.doors", theDoors, doorBase, screen);
                    //Good Guy Sprites
                    theEngine->loadSprites("data/maps/dungeon2/level.goodguy", goodGuys, goodBase, screen);
                    //Object Sprites
                    theEngine->loadSprites("data/maps/dungeon2/level.objects", theObjects, objectBase, screen);  
    			    //Bad Guy Sprites
                    theEngine->loadSprites("data/maps/dungeon2/level.badguy", badGuys, badBase, screen, arrowBase);
                    if (thePlayer->getProgress()!=100)
                       goodGuys[2]->setVisible(false);
		            thePlayer->setX(200);
		            thePlayer->setY(180);
		            thePlayer->setHeld();
               }
               else if((level == 43) && (i==0) && (thePlayer->returnInventory()[12]->getVisible()))
               {
                    level = 4;
    			    badGuys.clear();
    		        goodGuys.clear();
    		        theObjects.clear();
    		        theDoors.clear();
    		        uItems.clear();
    		        loadLevel(theEngine, theMap, surfaces, mapXPos, mapYPos, 18, 1, "data/maps/castle/castle.map"); 
		            theEngine->loadSprites("data/maps/castle/level2.doors", theDoors, doorBase, screen);
    			    //Bad Guy Sprites
                    theEngine->loadSprites("data/maps/castle/level2.badguy", badGuys, badBase, screen, arrowBase);
		            thePlayer->setX(320);
		            thePlayer->setY(330);
		            thePlayer->setHeld();
                    if (audioflag)
                     {
                     //Change the music
                     theEngine->Sound->playMusic(theMusic[4].c_str(), -1, 10000, 0, 0);
                     /*---------------------------------------------------------------------*/
                     }
               }
               else if((level == 43) && (i==1))
               {
                    level = 42;
    			    badGuys.clear();
    		        goodGuys.clear();
    		        theObjects.clear();
    		        theDoors.clear();
    		        uItems.clear();
    		        loadLevel(theEngine, theMap, surfaces, mapXPos, mapYPos, 12, 29, "data/maps/dungeon1/dungeon1.map"); 
		            theEngine->loadSprites("data/maps/dungeon1/level1.doors", theDoors, doorBase, screen);
                    //Good Guy Sprites
                    theEngine->loadSprites("data/maps/dungeon1/level1.goodguy", goodGuys, goodBase, screen);
    			    //Bad Guy Sprites
                    theEngine->loadSprites("data/maps/dungeon1/level1.badguy", badGuys, badBase, screen, arrowBase);
		            thePlayer->setX(220);
		            thePlayer->setY(320);
		            thePlayer->setHeld();
               }
               else if((level == 5) && (i==0))
               {
                    //Change this
                    level = 1;
    			    badGuys.clear();
    		        goodGuys.clear();
    		        theObjects.clear();
    		        theDoors.clear();
    		        uItems.clear();
    		        loadLevel(theEngine, theMap, surfaces, mapXPos, mapYPos, 28, 29, "data/maps/level1/level1.map"); 
		            theEngine->loadSprites("data/maps/level1/level4.doors", theDoors, doorBase, screen);
		            //Bad Guy Sprites
                    theEngine->loadSprites("data/maps/level1/level4.badguy", badGuys, badBase, screen, arrowBase);
		            thePlayer->setX(300);
		            thePlayer->setY(300);
    		        thePlayer->setHeld();
               } 
               else if((level == 5) && (i==1))
               {
                    //Change this
                    level = 52;
    			    badGuys.clear();
    		        goodGuys.clear();
    		        theObjects.clear();
    		        theDoors.clear();
    		        uItems.clear();
     	            loadLevel(theEngine, theMap, surfaces, mapXPos, mapYPos, 28, 0, "data/maps/desert2/desert2.map"); 
    		        theEngine->loadSprites("data/maps/desert2/level.doors", theDoors, doorBase, screen);
                    //Object Sprites
                    theEngine->loadSprites("data/maps/desert2/level.objects", theObjects, objectBase, screen);
                    //Bad Guy Sprites
                    theEngine->loadSprites("data/maps/desert2/level.badguy", badGuys, badBase, screen, arrowBase);
                    if (thePlayer->getCollected(0))
                    {
                         theObjects[0]->setVisible(false);
                    }  
    			    thePlayer->setX(300);
    		        thePlayer->setY(50);
    		        thePlayer->setHeld();
               } 
               else if((level == 52) && (i==0))
               {
                    //Change this
                    level = 5;
    			    badGuys.clear();
    		        goodGuys.clear();
    		        theObjects.clear();
    		        theDoors.clear();
    		        uItems.clear();
     	            loadLevel(theEngine, theMap, surfaces, mapXPos, mapYPos, 2, 29, "data/maps/desert1/desert1.map"); 
    		        theEngine->loadSprites("data/maps/desert1/level1.doors", theDoors, doorBase, screen);
                    //Bad Guy Sprites
                    theEngine->loadSprites("data/maps/desert1/level1.badguy", badGuys, badBase, screen, arrowBase);
    			    thePlayer->setX(200);
    		        thePlayer->setY(400);
    		        thePlayer->setHeld();
               } 
               else if((level == 52) && (i==1))
               {
                    //Change this
                    level = 53;
    			    badGuys.clear();
    		        goodGuys.clear();
    		        theObjects.clear();
    		        theDoors.clear();
    		        uItems.clear();
     	            loadLevel(theEngine, theMap, surfaces, mapXPos, mapYPos, 39, 21, "data/maps/cave/cave.map"); 
    		        theEngine->loadSprites("data/maps/cave/level.doors", theDoors, doorBase, screen);
                    //Good Guy Sprites
                    theEngine->loadSprites("data/maps/cave/level.goodguy", goodGuys, goodBase, screen);
                    //Object Sprites
                    theEngine->loadSprites("data/maps/cave/level.objects", theObjects, objectBase, screen);  
                    theObjects[1]->setVisible(false);
                    if (thePlayer->getCollected(3))
                       theObjects[2]->setImage(theObjects[2]->getBase()->getImage("down1"));
                       
    			    thePlayer->setX(360);
    		        thePlayer->setY(220);
    		        thePlayer->setHeld();
                    if (audioflag)
                     {
                     //Change the music
                     theEngine->Sound->playMusic(theMusic[3].c_str(), -1, 10000, 0, 0);
                     /*---------------------------------------------------------------------*/
                     }
               } 
               else if((level == 53) && (i==0))
               {
                    //Change this
                    level = 52;
    			    badGuys.clear();
    		        goodGuys.clear();
    		        theObjects.clear();
    		        theDoors.clear();
    		        uItems.clear();
     	            loadLevel(theEngine, theMap, surfaces, mapXPos, mapYPos, 0, 29, "data/maps/desert2/desert2.map"); 
    		        theEngine->loadSprites("data/maps/desert2/level1.doors", theDoors, doorBase, screen);
                    //Object Sprites
                    theEngine->loadSprites("data/maps/desert2/level1.objects", theObjects, objectBase, screen);
                    //Bad Guy Sprites
                    theEngine->loadSprites("data/maps/desert2/level1.badguy", badGuys, badBase, screen, arrowBase);
                    if (thePlayer->getCollected(0))
                    {
                         theObjects[0]->setVisible(false);
                    }  
    			    thePlayer->setX(90);
    		        thePlayer->setY(420);
    		        thePlayer->setHeld();
                    if (audioflag)
                     {
                     //Change the music
                     theEngine->Sound->playMusic(theMusic[2].c_str(), -1, 10000, 0, 0);
                     /*---------------------------------------------------------------------*/
                     }
    		        
               } 
               else if((level == 6) && (i==0))
               {
                    level = 1;
    			    badGuys.clear();
    		        goodGuys.clear();
    		        theObjects.clear();
    		        theDoors.clear();
    		        uItems.clear();
    		        loadLevel(theEngine, theMap, surfaces, mapXPos, mapYPos, 2, 0, "data/maps/level1/level1.map"); 
		            theEngine->loadSprites("data/maps/level1/level3.doors", theDoors, doorBase, screen);
		            //Bad Guy Sprites
                    theEngine->loadSprites("data/maps/level1/level3.badguy", badGuys, badBase, screen, arrowBase);
		            thePlayer->setX(80);
		            thePlayer->setY(200);
		            thePlayer->setHeld();
                    if (audioflag)
                     {
                     //Change the music
                     theEngine->Sound->playMusic(theMusic[2].c_str(), -1, 10000, 0, 0);
                     /*---------------------------------------------------------------------*/
                     }
               }
               else if((level == 6) && (i==1))
               {
                    if (thePlayer->returnInventory()[10]->getVisible() &&  thePlayer->returnInventory()[11]->getVisible()  &&  thePlayer->returnInventory()[12]->getVisible())
                    {
                    //let player pass through                                     
                    }
                    else
                    {
                        theEngine->Sound->playEffect("data/sound/new_effects/LTTP_Bounce.wav", "play", 0,0);  
                        thePlayer->setX(thePlayer->getOldX());
                        thePlayer->setY(thePlayer->getOldY());
                        lv.message(screen, "data/text/barrier.data", thePlayer->getName());
                    }
               }
               else if((level == 6) && (i==2))
               {
                    level = 4;
    			    badGuys.clear();
    		        goodGuys.clear();
    		        theObjects.clear();
    		        theDoors.clear();
    		        uItems.clear();
     	            loadLevel(theEngine, theMap, surfaces, mapXPos, mapYPos, 0, 5, "data/maps/castle/castle.map"); 
     	            theEngine->loadSprites("data/maps/castle/level1.doors", theDoors, doorBase, screen);
    			    //Bad Guy Sprites
                    theEngine->loadSprites("data/maps/castle/level1.badguy", badGuys, badBase, screen, arrowBase);
                    thePlayer->setX(100);
                    thePlayer->setY(200);
                    thePlayer->setHeld();
                    if (audioflag)
                     {
                     //Change the music
                     theEngine->Sound->playMusic(theMusic[4].c_str(), -1, 10000, 0, 0);
                     /*---------------------------------------------------------------------*/
                     }
               }
		       else
                {
                    thePlayer->setX(thePlayer->getOldX());
                    thePlayer->setY(thePlayer->getOldY());
                }
                	    
        	    theEngine->setupBack(TILES_UP, TILES_ACROSS, mapYPos, mapXPos, backSurface, theMap);
        	    theEngine->drawBack(tileHeight, tileWidth, TILES_UP, TILES_ACROSS, theEngine, backSurface, surfaces, back);  
    		}
        }
                //--------------------------------END MOVE PLAYER AND STUFF--------------------------------\\

                //-------------------------UPDATE EVERYTHINGS POS------------------------------\\

             vector<sprite *>& playerArrows = thePlayer->getWeapon();
             for(unsigned int i=0; i < playerArrows.size(); i++)
             {
                 if(playerArrows[i] != NULL)
		         {
                      playerArrows[i]->setX(playerArrows[i]->getX()+xOffset);
		              playerArrows[i]->setY(playerArrows[i]->getY()+yOffset);
                 }
             }		
             for(unsigned int i=0; i < goodGuys.size(); i++)
             {
                 goodGuys[i]->setX(goodGuys[i]->getX()+xOffset);
                 goodGuys[i]->setY(goodGuys[i]->getY()+yOffset);
             }
             
             sprite *&playerBoom = thePlayer->getBoomerang();
             if ( playerBoom!= NULL)
             {
                 playerBoom->setX(playerBoom->getX()+xOffset);
                 playerBoom->setY(playerBoom->getY()+yOffset);
             }

             for(unsigned int i=0; i < badGuys.size(); i++)
             {
                 badGuys[i]->setX(badGuys[i]->getX()+xOffset);
                 badGuys[i]->setY(badGuys[i]->getY()+yOffset);
                 
                 if (badGuys[i]->getEType()==1)
                 {    
                 vector<sprite *>& enemyArrows = badGuys[i]->getWeapon();
                 for(unsigned int j=0; j < enemyArrows.size(); j++)
                 {
                     if(enemyArrows[j] != NULL)
                     {
                         enemyArrows[j]->setX(enemyArrows[j]->getX()+xOffset);
                         enemyArrows[j]->setY(enemyArrows[j]->getY()+yOffset);
                     }
                 }
                 }
                 
             }
             
             
             
             for(unsigned int i=0; i < theObjects.size(); i++)
             {
                 theObjects[i]->setX(theObjects[i]->getX()+xOffset);
                 theObjects[i]->setY(theObjects[i]->getY()+yOffset);
             }
		     for(unsigned int i=0; i < theDoors.size(); i++)
		     {
		         theDoors[i]->setX(theDoors[i]->getX()+xOffset);
		         theDoors[i]->setY(theDoors[i]->getY()+yOffset);
		     }
		     if (!uItems.empty())
             {
             for(unsigned int i=0; i < uItems.size(); i++)
		     {
		         uItems[i]->setX(uItems[i]->getX()+xOffset);
		         uItems[i]->setY(uItems[i]->getY()+yOffset);
		     }
             }

                xOffset=0;
                yOffset=0;

                //-------------------------END UPDATE TILES-----------------------------------\\


                //-------------------------DRAW EVERYTHING-----------------------------------\\
                
		        ++input_delay;
                dr.drawAll(theEngine, back, screen, thePlayer, badGuys, goodGuys, theObjects, screenInfo, theDoors, backX, backY, screenWidth, screenHeight, font, uItems);
                gTimer = SDL_GetTicks();
            }//End Get Ticks
            
        }//End if! paused
        
        
        //-------------------------END DRAW EVERYTHING--------------------------------\\

    }//While not exit loop

    //Free up memory...
    delete theEngine;
    delete thePlayer;
    delete font;
    delete fontp;
    delete pMenu;
    
    theEngine = NULL;
    thePlayer = NULL;
    font = NULL;
    fontp = NULL;
    pMenu = NULL;
    
    SDL_Quit();
    return 0;
}

