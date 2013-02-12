/*
 *  gameengine.h
 *  Author: gary ohmes
 *  
 */
#ifndef _game_engine_
#define _game_engine_
//my complier got stupider somehow... this is why the /../../ is here...
#include "/../../usr/include/SDL/SDL.h"
#include "/../../usr/include/SDL/SDL_image.h"
#include "/../../usr/include/SDL/SDL_ttf.h"
#include "SDL/SDL_gfxPrimitives.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <dirent.h>
#include <boost/ptr_container/ptr_vector.hpp>
//sqllite stuff...
#include "sqlite3.h"
//for random # generatior...
#include <stdlib.h>
#include <time.h>

namespace sqlite{
    /*Create and close a blank sqllite database*/
    bool CreateDB(std::string DBstring){
        //convert string to const char*
        const char * DBname = DBstring.c_str();
        //make DB object
        sqlite3 *database;
        //open the database on disc
        sqlite3_open(DBname, &database);
        //close the database
        sqlite3_close(database);
        //remove the ram used...
        delete DBname;
    }
    //SAMPLE TABLE COMMAND: "CREATE TABLE a (b INTEGER, c INTEGER);"
    bool CreateTable(std::string DBstring, std::string TableCommandS){
        //convert string to const char* (as needed)
        const char * DBname = DBstring.c_str();
        const char * TableCommand = TableCommandS.c_str();
        //create DB object
        sqlite3 *database;
        //open the database
        sqlite3_open(DBname, &database);
        //do a prepared statement CREATE table....
        sqlite3_stmt *statement;
	 
	    if(sqlite3_prepare_v2(database, TableCommand, -1, &statement, 0) == SQLITE_OK)
	    {
	        int cols = sqlite3_column_count(statement);
	        int result = 0;
	        while(true)
	        {
	            result = sqlite3_step(statement);
	             
	            if(result == SQLITE_ROW)
	            {
	                for(int col = 0; col < cols; col++)
	                {
	                    std::string s = (char*)sqlite3_column_text(statement, col);
	                    //do something with it
	                }
	            }
	            else
	            {
	                break;  
	            }
	        }
	        
	        sqlite3_finalize(statement);
	    }
        //Close the database
        sqlite3_close(database);
    }
}

namespace engine{
        /*
         * Covert int to string
         * @Author multicoder
         */
        std::string IntToString(int i){
            std::stringstream out;
            out << i;
            return out.str();
        }
        
        int StringToInt(std::string i){
            return atoi(i.c_str());
        }
        /**
         * Random # generators
         * @Author multicoder
         * @return A random #
         */
        int Rnum(){     
            return rand();
        }
        int Rnum(int max){
            return (rand() % (max - 1 + 1)) + 1;
        }
        int Rnum(int min, int max){
            return (rand() % (max - min + 1)) + min;
        }
        /*
         * Image Loading function
         * @Author gary ohmes
         */
	SDL_Surface *load_image( std::string filename ){
		SDL_Surface* loadedImage = NULL;
		SDL_Surface* optimizedImage = NULL;
		loadedImage = IMG_Load( filename.c_str() );

		if( loadedImage != NULL ){
		    optimizedImage = SDL_DisplayFormat(loadedImage);
		    SDL_FreeSurface(loadedImage);
		    if(optimizedImage != NULL){
            Uint32 colorkey = SDL_MapRGB(optimizedImage->format, 0, 0, 0);
            SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey);
                                }
                        }

		return optimizedImage;
		}

	//Drawing functions
	void Draw_Pics(SDL_Surface* a, SDL_Surface* b, int x, int y, SDL_Rect* c = NULL){
		SDL_Rect dest;
		dest.x = x;
		dest.y = y;
		SDL_BlitSurface(b, c, a, &dest);
		}
	
	void Draw_Clip(SDL_Surface* a, SDL_Surface* b, SDL_Rect c[3], int x, int y, int w, int h){
		SDL_Rect dest;
		dest.x = x;
		dest.y = y;
		dest.w = w;
		dest.h = h;
		SDL_BlitSurface(b, c, a, &dest);
		}

	bool keystroke(bool a[323],SDL_Event event){
		if( event.type == SDL_KEYDOWN ){
			a[event.key.keysym.sym] = true;
			return true;
			}
		else if( event.type == SDL_KEYUP ){
			a[event.key.keysym.sym] = false;
			}
	   	return false;
		}

	void Draw_Text(SDL_Surface* a, SDL_Color wordcolor, std::string input, int size, int x, int y){
		TTF_Font *font = TTF_OpenFont( "FreeMono.ttf", size);
		std::stringstream stuff;
		stuff << input;
		SDL_Surface* Message = TTF_RenderText_Solid( font, stuff.str().c_str(), wordcolor );
		engine::Draw_Pics(a, Message, x, y);
		SDL_FreeSurface(Message);
		TTF_CloseFont(font);
		}
		
	void Draw_Numbers(SDL_Surface* a, SDL_Color wordcolor, int score, int size, int x, int y){
		TTF_Font *font = TTF_OpenFont( "FreeMono.ttf", size);
		std::string input;
		std::stringstream stuff;
		stuff << score;
		SDL_Surface* Message = TTF_RenderText_Solid( font, stuff.str().c_str(), wordcolor );
		engine::Draw_Pics(a, Message, x, y);
		SDL_FreeSurface(Message);
		TTF_CloseFont(font);
		}

	class pointer{
public:
    int x;
    int y;
    bool clicking;

    pointer(){
	    x = 0;
	    y = 0;
	    clicking = false;
	    }

    int mouseinput(SDL_Event click){
	    if (click.type == SDL_MOUSEBUTTONDOWN){
		    if (click.button.button == SDL_BUTTON_LEFT){
			    x = click.button.x;
			    y = click.button.y;
			    clicking = true;
			    return 1;
			    }
		    else if (click.button.button == SDL_BUTTON_RIGHT){
			    clicking = true;
			    return 2;
			    }
		    }
	    else if (click.type == SDL_MOUSEBUTTONUP){
		    if (click.button.button == SDL_BUTTON_LEFT){
			    x = 0;
			    y = 0;
			    clicking = false;
			    }
		    if (click.button.button == SDL_BUTTON_RIGHT){
			    clicking = false;
			    }
		    }
	    else if (click.type == SDL_MOUSEMOTION){
		    x = click.button.x;
		    y = click.button.y;
		    return 3;
		    }
	return 0;
	}
    };
	
	class clock{
		
		bool started;
		bool paused;
		int starttime;
		int currenttime;
		int pausetime;
		int endtime;
		
		clock(){
			started = false;
			paused = false;
			starttime = 0;
			currenttime = 0;
			pausetime = 0;
			endtime = 120000;
			}
		
		void start_clock(){
			started = true;
			starttime = SDL_GetTicks();
			}
		
		void pause_clock(){
			if(started == true && paused == false){
				paused = true;
				}
			}
		
		void reset_clock(){
			
			}
		
		};
         
        class textin{
            short x, y, w, h;
            std::string word;
            SDL_Surface* box;
            SDL_Color background;
            SDL_Color textcolor;
        public:
            bool active;
            
            textin(){
                x = 0;
                y = 0;
                w = 0;
                h = 0;
                word = "";
                box = NULL;
                background.r = 0;
                background.g = 0;
                background.b = 0;
                textcolor.r = 0;
                textcolor.g = 0;
                textcolor.b = 0;
                active = false;
            }
            
            void blank(){
                word = "";
            }
            
            void place_field(short left, short top, short width, short height){
                x = left;
                y = top;
                w = width;
                h = height;
            }
            
            void set_background_color(Sint8 red, Sint8 green, Sint8 blue){
                background.r = red;
                background.g = green;
                background.b = blue;
            }
            
            void set_text_color(Sint8 red, Sint8 green, Sint8 blue){
                textcolor.r = red;
                textcolor.g = green;
                textcolor.b = blue;
            }
            
            std::string set_string(SDL_Event event){
                if (word.size() < 50){
                    if (event.key.keysym.unicode == (Uint16)' ' ){
                        word += (char)event.key.keysym.unicode;
                    }
                    else if (event.key.keysym.unicode >= (Uint16)'0' && event.key.keysym.unicode <= '9'){
                        word += (char)event.key.keysym.unicode;
                    }
                    else if (event.key.keysym.unicode >= (Uint16)'A' && event.key.keysym.unicode <= 'Z'){
                        word += (char)event.key.keysym.unicode;
                    }
                    else if (event.key.keysym.unicode >= (Uint16)'a' && event.key.keysym.unicode <= 'z'){
                        word += (char)event.key.keysym.unicode;
                    }
                    else if (event.key.keysym.unicode >= (Uint16)'!' && event.key.keysym.unicode <= '/'){
                        word += (char)event.key.keysym.unicode;
                    }
                }
                if (event.key.keysym.sym == SDLK_BACKSPACE && word.length() > 0){
                    word.erase(word.length() - 1);
                }
                else if (event.key.keysym.sym == SDLK_RETURN){
                    active = false;
                    return word;
                }
                else return "";
                
            }
            
            void Render(SDL_Surface* screen, int size){
                if (active){
                    boxRGBA(screen, x, y, w, h, background.r, background.g, background.b, 255);
                    Draw_Text(screen, textcolor, word, size, x, y+2);   
                }
            }
            
        };
        
        class textout{
            short x, y, w, h;
            short time;
            std::string word;
            SDL_Surface* box;
            SDL_Color background;
            SDL_Color textcolor;
        public:
            
            textout(){
                x = 0;
                y = 0;
                w = 0;
                h = 0;
                background.r = 0;
                background.g = 0;
                background.b = 0;
                textcolor.r = 0;
                textcolor.g = 0;
                textcolor.b = 0;
            }
            
            void place_box(short left, short top, short width, short height){
                x = left;
                y = top;
                w = width;
                h = height;
            }
            
            void set_background_color(Sint8 red, Sint8 green, Sint8 blue){
                background.r = red;
                background.g = green;
                background.b = blue;
            }
            
            void set_text_color(Sint8 red, Sint8 green, Sint8 blue){
                textcolor.r = red;
                textcolor.g = green;
                textcolor.b = blue;
            }
            
            void get_word(std::string input){
                word = input;
                time = 50;
            }
            
            void Render(SDL_Surface* screen, int size){
                if (time > 0){    
                    Draw_Text(screen, textcolor, word, size, x, y+2);
                    time--;
                }
            }
            
        };
        
	class textfield{
	    short a, b, c, d;
            short linex, liney;
            short logx, logy;
            short active_word;
	    std::string word;
            std::string logged_word;
            std::string message;
	    SDL_Color background;
	    SDL_Color textcolor;
            SDL_Surface* log;
	    
	public:
	    bool active;
            
	    textfield(){
		active = false;
		a = 0;
		b = 300;
                c = 800;
                d = 600;
                linex = 2;
                liney = 550;
                logx = 2;
                logy = 302;
                active_word = 0;
		word = "";
                logged_word = "";
                message = "";
		background.r = 200;
		background.g = 200;
		background.b = 128;
                textcolor.r = 0;
                textcolor.g = 0;
                textcolor.b = 0;
                log = SDL_CreateRGBSurface(SDL_SWSURFACE || SDL_HWSURFACE, 800, 300, 32, 200, 200, 128, 255);
	    }
	    
            void set_background_color(Sint8 red, Sint8 green, Sint8 blue){
                background.r = red;
                background.g = green;
                background.b = blue;
            }
            
            void set_text_color(Sint8 red, Sint8 green, Sint8 blue){
                textcolor.r = red;
                textcolor.g = green;
                textcolor.b = blue;
            }
            
	    void place(short x, short y, short width, short height){
		a = x;
		b = y;
		c = width;
		d = height;
	    }
	    
            std::string set_string(SDL_Event event){
                    if (word.size() < 16){
                        if (event.key.keysym.unicode == (Uint16)' ' ){
                            word += (char)event.key.keysym.unicode;
                        }
                        else if (event.key.keysym.unicode >= (Uint16)'0' && event.key.keysym.unicode <= '9'){
                            word += (char)event.key.keysym.unicode;
                        }
                        else if (event.key.keysym.unicode >= (Uint16)'A' && event.key.keysym.unicode <= 'Z'){
                            word += (char)event.key.keysym.unicode;
                        }
                        else if (event.key.keysym.unicode >= (Uint16)'a' && event.key.keysym.unicode <= 'z'){
                            word += (char)event.key.keysym.unicode;
                        }
                        else if (event.key.keysym.unicode >= (Uint16)'!' && event.key.keysym.unicode <= '/'){
                            word += (char)event.key.keysym.unicode;
                        }
                    }
                    if (event.key.keysym.sym == SDLK_BACKSPACE && word.length() > 0){
                        word.erase(word.length() - 1);
                    }
                    else if (event.key.keysym.sym == SDLK_BACKSPACE && word.length() <= 0){
                        ;
                    }
                    else if (event.key.keysym.sym == SDLK_RETURN){
                        logged_word = word;
                        Draw_Text(log, textcolor, logged_word, 15, logx, logy);
                        logy = logy + 15;
                        return word;
                    }
                    else return "";
                
            }
            
            void output(std::string a){
                //message = a;
                Draw_Text(log, textcolor, a, 15, logx, logy);
                logy = logy + 15;
            }
            
	    void render(SDL_Surface* screen, int size){
                boxRGBA(screen, a, b, c, d, background.r, background.g, background.b, 255);
               // for (int i = 0; i < word.size(); i++){
                Draw_Pics(screen, log, a, b);
		Draw_Text(screen, textcolor, word, size, linex, liney);
                //}
	    }
	    
	    
	};

}
#endif
