/* 
 * File:   enemy.hpp
 * Author: garys
 *
 * Created on February 22, 2013, 10:03 PM
 */

#ifndef ENEMY_HPP
#define	ENEMY_HPP

template <typename bg> class foes{
    public:
    float x, y;
    bool alive;
    short health;
    short damage;
    
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
    
};

#endif	/* ENEMY_HPP */

