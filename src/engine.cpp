#include "engine.h"
#include <string.h>

engine::engine()
{
    Display = NULL;
    Sound   = NULL;
}

engine::~engine()
{
    if(Display != NULL)
    {
        delete Display;
        Display = NULL;
    }

    if(Sound != NULL)
    {
        delete Sound;
        Sound = NULL;
    }
}

int engine::spriteCollide(sprite* object1, sprite* object2)
{
    int left1, left2;
    int right1, right2;
    int top1, top2;
    int bottom1, bottom2;

    left1 = object1->getX() + object1->getColXOffset();
    left2 = object2->getX() + object2->getColXOffset();
    right1 = left1 + object1->getColW();
    right2 = left2 + object2->getColW();
    top1 = object1->getY() + object1->getColYOffset();
    top2 = object2->getY() + object2->getColYOffset();
    bottom1 = top1 + object1->getColH();
    bottom2 = top2 + object2->getColH();

    if (bottom1 <= top2)
        return(0);
    if (top1 >= bottom2)
        return(0);
    if (right1 <= left2)
        return(0);
    if (left1 >= right2)
        return(0);

    return 1;
};

int engine::setupMap(int ySize, int xSize, std::vector< std::vector <int> > &theMap, char *filename)
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

//Copies the correct tiles from map to backSurface
int engine::setupBack(int y, int x, int mapYPos, int mapXPos, std::vector< std::vector <int> > &backSurface, std::vector< std::vector <int> > &theMap)
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

void engine::drawBack(int tileHeight, int tileWidth, int y, int x, engine *theEngine, std::vector< std::vector <int> > &backSurface, std::vector<SDL_Surface *> surfaces, SDL_Surface *back)
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

int engine::loadSurfaces(char *filename, std::vector<SDL_Surface *> &surfaces)
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
    }
    return 0;
}


int engine::loadPlayer(char *filename, player* &thePlayer, vector<spriteBase *> playerBase, SDL_Surface *screen, spriteBase* weaponBase, spriteBase* boomBase)
{
    int x;
    int y;
    int w;
    int h;


    FILE *fp;
    char buffer[255];

    if((fp=fopen(filename, "r")) == NULL)
    {
        printf("Error opening file %s\n", filename);
        return -1;
    }
    while(!feof(fp))
    {
        fgets(buffer, 255, fp);
        sscanf(buffer, "PLAYER: %d %d %d %d", &x, &y, &w, &h);
    }
    fclose(fp);

    thePlayer = new player(playerBase, screen, x, y, w, h, weaponBase, boomBase);
    //thePlayer->initSprite(playerBase, screen, x, y, w, h);
    thePlayer->setDirection('S');
    thePlayer->setScore(0);

    return 0;
}




int engine::loadSprites(char *filename, std::vector<sprite *> &theSprite, std::vector<spriteBase *> &spriteBase, SDL_Surface *screen)
{
    int x;
    int y;
    int w;
    int h;
    int base;

    int count = theSprite.size();

    FILE *fp;
    char buffer[255];

    if((fp=fopen(filename, "r")) == NULL)
    {
        printf("Error opening file %s\n", filename);
        return -1;
    }
    while(!feof(fp))
    {
        fgets(buffer, 255, fp);
        sscanf(buffer, "SPRITE: %d %d %d %d %d", &base, &x, &y, &w, &h);
	if((w > 0) && (h > 0)){
        theSprite.push_back(new sprite);
        theSprite[count]->initSprite(spriteBase[base], screen, x, y, w, h);
        count++;
	}
    }
    fclose(fp);

    return 0;
}

int engine::loadSprites(char *filename, std::vector<Item *> &theItem, std::vector<spriteBase *> &spriteBase, SDL_Surface *screen)
{
    int x;
    int y;
    int w;
    int h;
    int base;

    int count = theItem.size();

    FILE *fp;
    char buffer[255];
    char n[255];
    int v;
    

    if((fp=fopen(filename, "r")) == NULL)
    {
        printf("Error opening file %s\n", filename);
        return -1;
    }
    while(!feof(fp))
    {
        fgets(buffer, 255, fp);
        sscanf(buffer, "SPRITE: %d %d %d %d %d %d %s", &base, &x, &y, &w, &h, &v, &n);
	    
        if((w > 0) && (h > 0))
        {
            theItem.push_back(new Item(n));
            theItem[count]->initSprite(spriteBase[base], screen, x, y, w, h);
            
            if (v == 1)
                theItem[count]->setVisible(false);
            
            count++;
	    }
    }
    fclose(fp);

    return 0;
}

int engine::loadSprites(char *filename, std::vector<orc *> &theSprite, std::vector<spriteBase *> &spriteBase, SDL_Surface *screen, spriteBase* weaponBase)
{
    int x;
    int y;
    int w;
    int h;
    int base;
    int life;
    int range;
    int vision;
    int type;
    char directions[255];

    int count = theSprite.size();

    FILE *fp;
    char buffer[255];

    if((fp=fopen(filename, "r")) == NULL)
    {
        printf("Error opening file %s\n", filename);
        return -1;
    }
    while(!feof(fp))
    {
        fgets(buffer, 255, fp);
	sscanf(buffer, "SPRITE: %d %d %d %d %d %d %d %d %d %s", &base, &x, &y, &w, &h, &type, &life, &range, &vision, &directions); 
	if((w > 0) && (h > 0)){

	if (type==1)
	{
	    theSprite.push_back(new orc(type, weaponBase));
    }
    else      
    {
	    theSprite.push_back(new orc(type));
     }
	theSprite[count]->initSprite(spriteBase[base], screen, x, y, w, h);
	theSprite[count]->loadDirections(directions);
	theSprite[count]->setLife(life);
	theSprite[count]->setRange(range);
	theSprite[count]->setVision(vision);

	count++;
	}
    }
    fclose(fp);
    theSprite.pop_back();

    return 0;
}

int engine::loadBase(char *filename, spriteBase* &playerBase)
{
    int r, g, b;

    FILE *fp;
    char buffer[255];
    char left[255];
    char right[255];
    char up[255];
    char down[255];
    char left1[255];
    char right1[255];
    char up1[255];
    char down1[255];

    if((fp=fopen(filename, "r")) == NULL)
    {
        printf("Error opening file %s\n", filename);
        return -1;
    }
    while(!feof(fp))
    {
        fgets(buffer, 255, fp);
        sscanf(buffer, "LEFT: %s %d %d %d", &left, &r, &g, &b);
        sscanf(buffer, "RIGHT: %s %d %d %d", &right, &r, &g, &b);
        sscanf(buffer, "UP: %s %d %d %d", &up, &r, &g, &b);
        sscanf(buffer, "DOWN: %s %d %d %d", &down, &r, &g, &b);
        sscanf(buffer, "LEFT1: %s %d %d %d", &left1, &r, &g, &b);
        sscanf(buffer, "RIGHT1: %s %d %d %d", &right1, &r, &g, &b);
        sscanf(buffer, "UP1: %s %d %d %d", &up1, &r, &g, &b);
        sscanf(buffer, "DOWN1: %s %d %d %d", &down1, &r, &g, &b);
    }
    fclose(fp);

    playerBase = new spriteBase;
    playerBase->loadImage(left, "left", r, g, b);
    playerBase->loadImage(right, "right", r, g, b);
    playerBase->loadImage(up, "up", r, g, b);
    playerBase->loadImage(down, "down", r, g, b);
    playerBase->loadImage(left1, "left1", r, g, b);
    playerBase->loadImage(right1, "right1", r, g, b);
    playerBase->loadImage(up1, "up1", r, g, b);
    playerBase->loadImage(down1, "down1", r, g, b);

    return 0;
}



int engine::loadPlayerBase(char *filename, spriteBase* &playerBase)
{
    int r, g, b;

    FILE *fp;
    char buffer[255];
    char image[255];


    if((fp=fopen(filename, "r")) == NULL)
    {
        printf("Error opening file %s\n", filename);
        return -1;
    }
    
    while(!feof(fp))
    {
        fgets(buffer, 255, fp);
        sscanf(buffer, ": %s %d %d %d", &image, &r, &g, &b);
        playerBase->loadPlayerImage(image, r, g, b);

    }
    fclose(fp);
    

    return 0;
}

int engine::loadBaseList(char *filename, std::vector<spriteBase *> &base)
{
    FILE *fp;
    char buffer[255];
    char file[255];
    int count = base.size();

    if((fp=fopen(filename, "r")) == NULL)
    {
        printf("Error opening file %s\n", filename);
        return -1;
    }
    while(!feof(fp))
    {
        fgets(buffer, 255, fp);
        sscanf(buffer, "BASE: %s", &file);
        base.push_back(new spriteBase);
        loadBase(file, base[count]);
        count++;
    }
    return 0;
}

int engine::loadPlayerBaseList(char *filename, std::vector<spriteBase *> &base)
{
    FILE *fp;
    char buffer[255];
    char file[255];
    int count = base.size();

    if((fp=fopen(filename, "r")) == NULL)
    {
        printf("Error opening file %s\n", filename);
        return -1;
    }
    while(!feof(fp))
    {
        fgets(buffer, 255, fp);
        sscanf(buffer, "BASE: %s", &file);
        base.push_back(new spriteBase);
        loadPlayerBase(file, base[count]);
        count++;
    }
    return 0;
}

int engine::loadConfig(char *filename)
{
    FILE *fp;
    char buffer[255];
    int audio;
    
    if((fp=fopen(filename, "r")) == NULL)
    {
        printf("Error opening config file %s\n", filename);
        exit(1);
    }
    
    fgets(buffer, 255, fp);
    sscanf(buffer, ":audio %d", &audio);
    
    return audio;
        
}

int engine::loadMusic(char *filename, std::vector< string > &theMusic)
{
    FILE *fp;
    char buffer[255];
    char music[255];

    if((fp=fopen(filename, "r")) == NULL)
    {
        printf("Error opening file %s\n", filename);
        return -1;
    }
    while(!feof(fp))
    {
        fgets(buffer, 255, fp);
        sscanf(buffer, ": %s", &music);
        theMusic.push_back(music);
    }

    return 0;
}
