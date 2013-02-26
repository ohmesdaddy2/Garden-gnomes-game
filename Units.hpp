/* 
 * File:   Units.hpp
 * Author: garys
 *
 * Created on February 21, 2013, 8:56 PM
 */

#ifndef UNITS_HPP
#define	UNITS_HPP

#include "enemy.hpp"
#include "wrapper.hpp"
#include "directions.hpp"
#include "ranging.hpp"

template <class T> class units{
    float x, y;
    short damage;
    short health;
    bool special;
    direction pointing;
    killzone range;
    public:
    
    units(){
        x = -500;
        y = -500;
        damage = 0;
        health = 0;
        special = false;
    }
    
    float getx(){
        return x;
    }
    
    float gety(){
        return y;
    }
    
    void place(float a, float b){
        x = a;
        y = b;
        range.place(a, b,);
        }
    
    void attack(foes a){
        
    }
    
};

#endif	/* UNITS_HPP */

