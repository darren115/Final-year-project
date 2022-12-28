#include "engine.h"


engine::engine()
{
    Display = NULL;
}

engine::~engine()
{
    if(Display != NULL)
    {
        delete Display;
        Display = NULL;
    }

}


int engine::setupMap(int ySize, int xSize, vector< vector<int> > &theMap, char *filename)
{

    FILE *fp;
    int numberarray[2700];

    if((fp=fopen(filename, "r")) == NULL)
    {
        printf("Error opening file %s\n", filename);
        return -1;
    }

    int index = 0;
    while ( fscanf (fp, " %d", &numberarray[index++]) > 0 )
    {}
    ;
    fclose (fp);

    int index2 = 0;
    for(int i=0;i< (ySize); i++)
    {
        for(int j=0;j<(xSize); j++)
        {
            theMap[i][j]=numberarray[index2];
            index2++;
        }
    }

    
    return 0;

}

void engine::newMap(int ySize, int xSize, vector< vector<int> > &theMap)
{
    for(int i=0;i< (ySize); i++)
    {
        for(int j=0;j<(xSize); j++)
        {
            theMap[i][j] = 0;
        }
    }
}

int engine::saveMap(int ySize, int xSize, SDL_Surface *screen, SFont *font, vector< vector<int> > &theMap, string filename)
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

    int overwrite = 0;
    
    filename += ".map";


    for(int i = 0; i < files.size(); i++)
    {
        if (filename == files.at(i))
            overwrite = 1;
    }
    
    //unique name save file
    while (overwrite == 1)
    {
        font->write(dialog, "Overwrite?", 15);
        font->write(dialog, "Y/N", 55);
    
        srcdest.x = 120;
        srcdest.y = 250;
        srcdest.w = 400;
        srcdest.h = 150;
    
        SDL_BlitSurface(dialog, NULL, screen, &srcdest); 
        
        SDL_Flip(screen);
           
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_y)
                {
                    overwrite = 0;
                    break;
                }
                
                if (event.key.keysym.sym == SDLK_n)
                    return 1;
                
            }
        }
        
    }
    
    ofstream myfile;
    filename = "data/maps/" + filename;

    myfile.open (filename.c_str());
  
    for(int i = 0; i < (ySize); i++)
    {
        for(int j = 0;j < (xSize); j++)
        {
            myfile << theMap[i][j] << " ";            
        }
        
        myfile << endl;
    }

    myfile.close();
    
    srcdest.x = 4;
    srcdest.y = 4;
    srcdest.w = 192;
    srcdest.h = 142;

    SDL_FillRect(dialog, &srcdest, SDL_MapRGB(dialog->format, 0, 0, 0));
    font->write(dialog, "File saved.", 15);
    font->write(dialog, "Press", 55);
    font->write(dialog, "return.", 95);
    
    srcdest.x = 120;
    srcdest.y = 250;
    srcdest.w = 400;
    srcdest.h = 150;

    
    SDL_BlitSurface(dialog, NULL, screen, &srcdest); 
    
    SDL_Flip(screen);
    

    int finished = 0;
    
    while (finished == 0)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_RETURN)
                {
                    finished = 1;
                }
            }
        }
    }
        
  
    return 0;
    
    
        
}

//Copies the correct tiles from map to backSurface
int engine::setupBack(int y, int x, int mapYPos, int mapXPos, vector< vector<int> > &backSurface, vector< vector<int> > &theMap)
{
    for(int i=0; i<y; i++)
    {
        for(int j=0; j<x; j++)
        {
            backSurface[i][j]=theMap[i+mapYPos][j+mapXPos];
        }
    }

    return 0;
}

void engine::drawBack(int tileHeight, int tileWidth, int y, int x, engine *theEngine, vector< vector<int> > &backSurface, vector<SDL_Surface *> surfaces, SDL_Surface *back)
{
    //Draw the whole backsurface array onto the background surface
    for(int i=0; i<y; i++)
    {
        for(int j=0; j<x; j++)
        {
            Display->drawSurface(surfaces[backSurface[i][j]], (tileWidth*j), (tileHeight*i), tileWidth, tileHeight, back);
        }
    }
}

int engine::loadGame(char *filename, int &screenWidth, int &screenHeight, int &levelWidth, int &levelHeight, int &tileWidth, int &tileHeight, int &tilesAcross, int &tilesUp, int &colours)
{
    FILE *fp;
    char buffer[255];

    //LEVELS DATA FILE

    if((fp=fopen(filename, "r")) == NULL)
    {
        printf("Error opening file %s\n", filename);
        return -1;
    }
    while(!feof(fp))
    {
        fgets(buffer, 255, fp);
        sscanf(buffer, "SCREEN_WIDTH: %d",&screenWidth);
        sscanf(buffer, "SCREEN_HEIGHT: %d",&screenHeight);
        sscanf(buffer, "LEVEL_WIDTH: %d",&levelWidth);
        sscanf(buffer, "LEVEL_HEIGHT: %d",&levelHeight);
        sscanf(buffer, "TILE_WIDTH: %d",&tileWidth);
        sscanf(buffer, "TILE_HEIGHT: %d",&tileHeight);
        sscanf(buffer, "TILES_ACROSS: %d",&tilesAcross);
        sscanf(buffer, "TILES_UP: %d",&tilesUp);
        sscanf(buffer, "COLOURS: %d", &colours);
    }

    return 0;
}


int engine::loadSurfaces(char *filename, vector<SDL_Surface *> &surfaces, int &tileCount)
{
    FILE *fp;
    char buffer[255];
    char file[255];

    //LEVELS DATA FILE
    if((fp=fopen(filename, "r")) == NULL)
    {
        printf("Error opening file %s\n", filename);
        return -1;
    }
    while(!feof(fp))
    {
        fgets(buffer, 255, fp);
        sscanf(buffer, ": %s",&file);
        surfaces.push_back(IMG_Load(file));
        tileCount++;
    }
    return 0;
}

int engine::loadBase(char *filename, spriteBase* &cursorBase, int tileCount)
{
    cursorBase = new spriteBase;
    int i = 1;
    ifstream ad (filename);
    string line;
    string sub1;
    char line2[255];
    char *line3;
    while(!ad.getline(line2, 254).eof())
    {
               line = line2;
               sub1=line.substr(line.find(':')+2, line.length());
               line3 = const_cast<char*>(sub1.c_str());
               cursorBase->loadImage(line3, i, tileCount);
               i++;
               
    }
    ad.close();

    return 0;
}

int engine::loadCursor(cursor* &theCursor, spriteBase* cursorBase, SDL_Surface *screen)
{
    theCursor = new cursor(cursorBase, screen, 0, 0, 32, 32);
    theCursor->setTile(1);
    
    return 0;
}
