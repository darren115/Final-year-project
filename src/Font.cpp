/*
Copyright (C) 2004 Lion Vollnhals
Copyright (C) 2003 Matthias Braun

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
#ifndef __LIB_2D_FONT_HPP__
#define __LIB_2D_FONT_HPP__

#include <string>
#include <stdexcept>
#include <sstream>
#include "SFont.h"

using namespace std;

/// A thin c++ wrapper around the custom SFont version
class SFont
{
public:

    ///returns the text height
	int getHeight() const
	{ return SFont_TextHeight(font); }

    ///returns the text width 
	int getTextWidth(const char* text) const
	{ return SFont_TextWidth(font, text); }
	
	///returns the text width
	int getTextWidth(const std::string& text) const
	{ return getTextWidth(text.c_str()); }

    ///draws the text to the surface at position x, y
	void write(SDL_Surface* surface, const char* text, int x, int y) const
	{ SFont_Write(surface, font, x, y, text); }
	
	///draws the text to the surface at position x, y
	void write(SDL_Surface* surface, const std::string& text, int x, int y) const
	{ write(surface, text.c_str(), x, y); }
	
	///draws the text to the surface at y, centred horizontally
	void write(SDL_Surface* surface, const char* text, int y) const
	{ SFont_WriteCenter(surface, font, y, text); }
	
	///draws the text to the surface at y, centred horizontally
	void write(SDL_Surface* surface, const std::string& text, int y) const
	{ write(surface, text.c_str(), y); }

    ///converts integer to string
    string IntToString(int num)
    {
        ostringstream myStream; //creates an ostringstream object
        myStream << num << flush;

        /*
        * outputs the number into the string stream and then flushes
        * the buffer (makes sure the output is put into the stream)
        */
  
        return(myStream.str()); //returns the string form of the stringstream object
    }
    
    ///constructor
    SFont(SDL_Surface* surface)
	{
		font = SFont_InitFont(surface);
		if(!font)
			throw std::runtime_error("Couldn't initialize font.");
	}
	
	///destructor
	~SFont()
	{ SFont_FreeFont(font); }
	
	
	
private:
    ///pointer to the font
	SFont_Font* font;
};

#endif


