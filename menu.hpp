/* 
 * File:   menu.hpp
 * Author: garys
 *
 * Created on February 8, 2013, 6:24 AM
 */

#ifndef MENU_HPP
#define	MENU_HPP

#include "wrapper.hpp"

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
	w = a;
	h = b;
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
        std::cout<<"z.x == "<<z.x<<"\n";
            std::cout<<"z.y == "<<z.y<<"\n";
    }
    
    void draw(SDL_Surface* a){
	boxRGBA(a, x, y, x + w, y + h, background.r, background.g, background.b, 255);
	wrapper::Draw_Text(a, label_color, label, 15, x + 5, y + 5);
    }
    
};

class opening{
    clicker button[2];
    
public:
    opening(){
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
        for (int i = 0; i < 2; i++){
            button[i].draw(screen);
        }
    }
    
    short run_menu(SDL_Surface* screen){
        SDL_Event event;
        wrapper::pointer mouse;
        bool done = false;
        while (!done){
            while (SDL_PollEvent(&event)){
                if (mouse.mouseinput(event) == 1){
                    if (select(mouse) == 2){
                        done = true;
                    }
                }
            }
            render(screen);
            SDL_Flip(screen);    
        }
        return 0;
    }
};


#endif	/* MENU_HPP */

