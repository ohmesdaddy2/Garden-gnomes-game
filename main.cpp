/* 
 * File:   main.cpp
 * Author: A mean Gecko
 *
 * Created on February 6, 2013, 6:40 AM
 */
#include <cstdlib>
#include <iostream>
#include "wrapper.hpp"
#include "menu.hpp"
#include "database.hpp"

/*
 * 
 */
int main(int argc, char** argv) {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_Surface* screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE || SDL_SWSURFACE);
    opening topmenu;
    
    if (topmenu.run_menu(screen) == 2){
        goto end;
    }
    
    
    end:
    return 0;
}

