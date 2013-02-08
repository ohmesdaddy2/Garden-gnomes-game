/* 
 * File:   main.cpp
 * Author: A mean Gecko
 *
 * Created on February 6, 2013, 6:40 AM
 */
#include <cstdlib>
#include "wrapper.hpp"

/*
 * 
 */
int main(int argc, char** argv) {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_Event event;
    bool done = false;
    
    while (!done){
	while(SDL_PollEvent(&event)){
	    short key = wrapper::keystroke(event);
	    
	    switch (key){
		case 27: done = true; break;
		default: break;
	    }
	}
    }
    
    
    return 0;
}

