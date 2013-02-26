/* 
 * File:   enemy.hpp
 * Author: garys
 *
 * Created on February 22, 2013, 10:03 PM
 */

#ifndef ENEMY_HPP
#define	ENEMY_HPP

#include <iostream>

template <class bg> class foes{
    
    enum morph{
            //grunts
            smallant,
            largeant,
            smalltermite,
            largetermite,
            //blocking bugs
            worm, //blocks off resources and escape routes

            //bosses
            smallspider, //early boss
            largerspider, // slightly larger boss
            antqueen, // mid-time boss

            termiteking, // ultimate boss
        };
    public:
    float x, y;
    bool alive;
    short health;
    short damage;
    morph type;
        
    foes(){
        x = -100;
        y = -100;
        alive = false;
        health = 10;
        damage = 1;
    }
    
    void place(float a, float b){
        x = a;
        y = b;
        alive = true;
    }
    
    void settype(short a){
        if ( a >= 0 && a <= 9 ){
            type = a;
        }
        else {std::cout<<"no such type\n";}
        
    }
    
};

#endif	/* ENEMY_HPP */

