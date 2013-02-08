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

class cliker{
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
    
    void draw(SDL_Surface* a){
	boxRGBA(a, x, y, w, h, background.r, background.g, background.b);
	wrapper::Draw_Text(a, label_color, label, 15, x + 5, y + 5);
    }
    
};



#endif	/* MENU_HPP */

