/* 
 * File:   game.hpp
 * Author: garys
 *
 * Created on February 8, 2013, 6:22 AM
 */

#ifndef GAME_HPP
#define	GAME_HPP

class game{
    int resources;// Probably just going to be dollars
    bool done;
    SDL_Event event;
    SDL_Surface* buffer;
    
public:
    game(){
        done = false;
        buffer = SDL_CreateRGBSurface(SDL_HWSURFACE, 0, 0, 800, 600, 32, 0, 0, 0, 255 );
        resources = 0;
        
    }
    
    int run_game(SDL_Surface* a){
        
    }
    
};

#endif	/* GAME_HPP */

