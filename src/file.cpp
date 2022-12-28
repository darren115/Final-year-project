#include "file.h"
#include <string.h>


file::file()
{
}
            
void file::save(player *thePlayer)
{
            ofstream a_file ( savefile );
            a_file<<"Hearts: "<<thePlayer->getHearts()<<endl;
            a_file<<"Life: "<<thePlayer->getLife()<<endl;
            a_file<<"Score: "<<thePlayer->getScore()<<endl;
            a_file<<"Progress: "<<thePlayer->getProgress()<<endl;
            a_file<<"Rupees: "<<thePlayer->getRupees()<<endl;
            a_file<<"Arrows: "<<thePlayer->getArrows()<<endl;
            a_file<<"Bombs: "<<thePlayer->getBombs()<<endl;
            a_file<<"Magic: "<<thePlayer->getMagic()<<endl;
            a_file<<"Name: "<<thePlayer->getName()<<endl;
            a_file<<"Pieces: "<<thePlayer->getPieces()<<endl;
            a_file<<"Bow: "<<thePlayer->returnInventory()[0]->getVisible()<<endl;
            a_file<<"Boomerang: "<<thePlayer->returnInventory()[1]->getVisible()<<endl;
            a_file<<"Bomb: "<<thePlayer->returnInventory()[2]->getVisible()<<endl;
            a_file<<"Bottle: "<<thePlayer->returnInventory()[3]->getVisible()<<endl;
            a_file<<"Lamp: "<<thePlayer->returnInventory()[4]->getVisible()<<endl;            
            a_file<<"Shovel: "<<thePlayer->returnInventory()[5]->getVisible()<<endl;      
            a_file<<"Courage: "<<thePlayer->returnInventory()[10]->getVisible()<<endl;
            a_file<<"Wisdom: "<<thePlayer->returnInventory()[11]->getVisible()<<endl;
            a_file<<"Power: "<<thePlayer->returnInventory()[12]->getVisible()<<endl;
            a_file<<"Mushroom: "<<thePlayer->returnInventory()[13]->getVisible()<<endl;
            
            
            
            for (int i=0; i<6; i++)
            {
            if (thePlayer->returnInventory()[i]->getSelected())
               a_file<<"Current: "<<i<<endl;
            }
            
            
            string test;             
            for (int i=0; i<4; i++)
            {
                test=i;
                   a_file<<i<<": "<<thePlayer->getCollected(i)<<endl;
            }
                 
            // Close the file stream explicitly
            a_file.close();
            load("Hearts");
            
}

void file::setFile(char *filename)
{
     savefile=filename;
}

void file::erase()
{
            ofstream a_file ( savefile );
            a_file<<"";
            // Close the file stream explicitly
            a_file.close();
}

int file::load(string type)
{
    ifstream a_file ( savefile );
    string line;
    string sub1;
    string sub2;
    int val;
            
    if (a_file.is_open())
    {
            while(!getline(a_file, line).eof())
            {
                   sub1=line.substr(0, line.find(':'));
                   sub2=line.substr(line.find(':')+2, line.length());
                   val=atoi(sub2.c_str());
                   if (type.compare( sub1 )==0)
                   {
                        a_file.close();
                        return val;
                   }
            }
            a_file.close();
    }
    //Cannot return 0 as it is a valid value
    return 9999;
}

void file::loadAll(player* &thePlayer, SDL_Surface *screen)
{
     if (load("Hearts")!=9999)
                     {
                        thePlayer->setHearts(load("Hearts"), screen, 17, 24);
                        thePlayer->setLife(load("Life"));
                        thePlayer->setScore(load("Score"));
                        thePlayer->setProgress(load("Progress"));
                        thePlayer->setRupees(load("Rupees"));
                        thePlayer->setArrows(load("Arrows"));
                        thePlayer->setBombs(load("Bombs"));
                        thePlayer->setMagic(load("Magic"));
                        thePlayer->setName(loadName());
                        if (load("Bow") == 1)
                        thePlayer->addItem(0);
                        if (load("Boomerang") == 1)
                        thePlayer->addItem(1);
                        if (load("Bomb") == 1)
                        thePlayer->addItem(2);
                        if (load("Bottle") == 1)
                        thePlayer->addItem(3);
                        if (load("Lamp") == 1)
                        thePlayer->addItem(4);
                        if (load("Shovel") == 1)
                        thePlayer->addItem(5);
                        if (load("Current")!=9999)
                        thePlayer->selectItem(load("Current"));
                        thePlayer->setPieces(load("Pieces"), screen);
                        if (load("Courage") == 1)
                        thePlayer->addItem(10);
                        if (load("Wisdom") == 1)
                        thePlayer->addItem(11);
                        if (load("Power") == 1)
                        thePlayer->addItem(12);
                        if (load("Mushroom") == 1)
                        thePlayer->addItem(13);
                        
                        
                        string test;
                        char buffer[10];
                        for (int i=0; i<4; i++)
                        {
                            itoa (i,buffer,10);
                           
                            if (load((buffer)) == 1)
                              thePlayer->setCollected(i);
                        }
                     }
}



string file::loadName()
{
            string name ="Name";
            ifstream a_file ( savefile );
            string line;
            string sub1;
            string sub2;
            int val;
            
            if (a_file.is_open())
            {
            while(!getline(a_file, line).eof())
            {
                   sub1=line.substr(0, line.find(':'));
                   sub2=line.substr(line.find(':')+2, line.length());
                   if (name.compare( sub1 )==0)
                   {
                        a_file.close();
                        return sub2;
                   }
            }
            a_file.close();
            }
            return "0";
}
