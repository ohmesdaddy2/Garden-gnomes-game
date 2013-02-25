/* 
 * File:   ranging.hpp
 * Author: garys
 *
 * Created on February 23, 2013, 12:51 PM
 */

#ifndef RANGING_HPP
#define	RANGING_HPP

#include "enemy.hpp"

class killzone{
    
    float originx, originy;
    
    float end;
public:
    killzone(){
        originx = 0;
        originy = 0;
        end = 0;
    }
    
    void place(float a, float b){
        originx = a;
        originy = b;
    }
    
    void size(float size){
        end = size;
    }
    
    bool scan(foes a){
        if (a.x > originx + end || a.x < originx - end && a.y > originy + end || a.y < originy - end){
            return true;
        }
        else return false;
    }
};

#endif	/* RANGING_HPP */

