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

template <typename T> class units{
    float x, y;
    short damage;
    short health;
    bool special;
    direction pointing;
    killzone range;
    public:
    
    
    
    float getx(){
        return x;
    }
    
    float gety(){
        return y;
    }
    
    void attack(foes a){
        
    }
    
};

#endif	/* UNITS_HPP */

