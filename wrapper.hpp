/* 
 * File:   wrapper.hpp
 * Author: garys
 *
 * Created on February 8, 2013, 6:11 AM
 */

#ifndef WRAPPER_HPP
#define	WRAPPER_HPP

#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_gfxPrimitives.h"
#include "SDL/SDL_ttf.h"


namespace wrapper{
    
    short keystroke(SDL_Event event){
	if (event.type == SDLK_DOWN){
	    return event.key.keysym.sym;
	}
	else if (event.type == SDLK_UP){
	    return -1;
	}
	else return -400;
    }
    
    void Draw_Pics(SDL_Surface* a, SDL_Surface* b, int x, int y, SDL_Rect* c = NULL){
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	SDL_BlitSurface(b, c, a, &dest);
	}
    
    void Draw_Text(SDL_Surface* a, SDL_Color wordcolor, std::string input, int size, int x, int y){
	TTF_Font *font = TTF_OpenFont( "FreeMono.ttf", size);
	std::stringstream stuff;
	stuff << input;
	SDL_Surface* Message = TTF_RenderText_Solid( font, stuff.str().c_str(), wordcolor );
	Draw_Pics(a, Message, x, y);
	SDL_FreeSurface(Message);
	TTF_CloseFont(font);
	}
		
    void Draw_Numbers(SDL_Surface* a, SDL_Color wordcolor, int score, int size, int x, int y){
	TTF_Font *font = TTF_OpenFont( "FreeMono.ttf", size);
	std::string input;
	std::stringstream stuff;
	stuff << score;
	SDL_Surface* Message = TTF_RenderText_Solid( font, stuff.str().c_str(), wordcolor );
	Draw_Pics(a, Message, x, y);
	SDL_FreeSurface(Message);
	TTF_CloseFont(font);
	}
    
}

#endif	/* WRAPPER_HPP */

