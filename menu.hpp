/* 
 * File:   menu.hpp
 * Author: garys
 *
 * Created on February 8, 2013, 6:24 AM
 */

#ifndef MENU_HPP
#define	MENU_HPP

#include "wrapper.hpp"
#include <iostream>

//clicker is for the menu buttons

class clicker{
    short x, y, w, h;
    std::string label;
    SDL_Color label_color;
    SDL_Color background;
    
public:
    clicker(){
	x = -809;
	y = -809;
	w = -809;
	h = -809;
	label = "";
	label_color.r = 0;
	label_color.g = 0;
	label_color.b = 0;
	background.r = 0;
	background.g = 0;
	background.b = 0;
	
    }
    
    void place_button(int a, int b){
	x = a;
	y = b;
    }
    
    void size_button(int a, int b){
	w = x + a;
	h = y + b;
    }
    
    void label_button(std::string string){
	label = string;
    }
    
    void set_background(Sint8 r, Sint8 g, Sint8 b){
	background.r = r;
	background.g = g;
	background.b = b;
    }
    
    void set_label(Sint8 r, Sint8 g, Sint8 b){
	label_color.r = r;
	label_color.g = g;
	label_color.b = b;
    }
    
    bool select(wrapper::pointer z){
       if (z.x > x && z.x < w && z.y > y && z.y < h){
	    return true;
	}
	else return false;
    }
    
    void draw(SDL_Surface* a){
	boxRGBA(a, x, y, w, h, background.r, background.g, background.b, 255);
	wrapper::Draw_Text(a, label_color, label, 15, x + 5, y + 5);
    }
    
};

class level{
    clicker button[4];
public:
    level(){
        button[0].place_button(100, 450);
        button[0].size_button(500, 60);
        button[0].label_button("Easy");
        button[0].set_background(128, 0, 64);
        button[0].set_label(255, 255, 0);
        button[1].place_button(100, 540);
        button[1].size_button(500, 60);
        button[1].label_button("Medium");
        button[1].set_background(128, 0, 64);
        button[1].set_label(255, 255, 0);
        button[2].place_button(100, 630);
        button[2].size_button(500, 60);
        button[2].label_button("Hard");
        button[2].set_background(128, 0, 64);
        button[2].set_label(255, 255, 0);
        button[3].place_button(100, 720);
        button[3].size_button(500, 60);
        button[3].label_button("Back");
        button[3].set_background(128, 0, 64);
        button[3].set_label(255, 255, 0);
    }
    
    short select(wrapper::pointer z){
        if (button[0].select(z)){
            return 1;
        }
        else if (button[1].select(z)){
            return 2;
        }
        else if (button[2].select(z)){
            return 3;
        }
    }
    
    void draw(SDL_Surface* screen){
        for (int i = 0; i < 4; i++){
            button[i].draw(screen);
        }
    }
    
};

class opening{
    Sint8 selection;
    clicker button[2];
    level difficulty;
public:
    opening(){
        selection = 0;
        button[0].place_button(100, 500);
        button[0].size_button(60, 30);
        button[0].label_button("Start");
        button[0].set_background(128, 64, 0);
        button[1].place_button(180, 500);
        button[1].size_button(60, 30);
        button[1].label_button("Quit");
        button[1].set_background(128, 64, 0);
    }
    
    short select(wrapper::pointer z){
        if (button[0].select(z) == true){
            return 1;
        }
        else if (button[1].select(z) == true){
            return 2;
        }
        else return 0;
    }
    
    void render(SDL_Surface* screen){
        boxRGBA(screen, 0, 0, screen->w, screen->h, 0, 0, 0, 255);
        if (selection == 0){
            for (int i = 0; i < 2; i++){
                button[i].draw(screen);
            }
        }
        else if (selection == 1){
            difficulty.draw(screen);
        }
        
    }
    
    short run_menu(SDL_Surface* screen){
        SDL_Event event;
        wrapper::pointer mouse;
        bool done = false;
        while (!done){
            while (SDL_PollEvent(&event)){
                //std::cout<<"checking events\n";
                if (mouse.mouseinput(event) == 1){
                    if (selection == 0){
                        if (select(mouse) == 1){
                        selection = 1;
                        }
                        if (select(mouse) == 2){
                            done = true;
                        }
                    }
                    if (selection == 1){
                        if (difficulty.select(mouse) == 1){
                            return 3;
                        }
                        else if (difficulty.select(mouse) == 2){
                            return 4;
                        }
                        else if (difficulty.select(mouse) == 3){
                            return 5;
                        }
                    }
                    
                }
                if (event.type == SDL_QUIT){
                    done = true;
                }
            }
            render(screen);
            SDL_Flip(screen);    
        }
        return 0;
    }
};


#endif	/* MENU_HPP */

