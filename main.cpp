/* 
 * File:   main.cpp
 * Author: A mean Gecko
 *
 * Created on February 6, 2013, 6:40 AM
 */
#include <cstdlib>
#include <iostream>
#include "wrapper.hpp"

/*
 * 
 */
int main(int argc, char** argv) {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_Event event;
    SDL_Surface* screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);
    bool done = false;
    
    while (!done){
	while(SDL_PollEvent(&event)){
	    short key = wrapper::keystroke(event);
	    std::cout<<key<<"\n";
        }
    }
    
    return 0;
}

