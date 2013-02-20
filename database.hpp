/* 
 * File:   database.hpp
 * Author: garys
 *
 * Created on February 18, 2013, 9:17 PM
 */

#ifndef DATABASE_HPP
#define	DATABASE_HPP

#include <sqlite3.h>

namespace database{
    
    void CreateDB(std::string DBstring){
        //convert string to const char*
        const char * DBname = DBstring.c_str();
        //make DB object
        sqlite3 *database;
        //open the database on disc
        sqlite3_open(DBname, &database);
        //close the database
        sqlite3_close(database);
        //remove the ram used...
        //delete DBname;
    }
    //SAMPLE TABLE COMMAND: "CREATE TABLE a (b INTEGER, c INTEGER);"
    void CreateTable(std::string DBstring, std::string TableCommandS){
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

#endif	/* DATABASE_HPP */

