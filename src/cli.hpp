#ifndef CLI_H
#define CLI_H
/***
 * Command line interface for Arduino boards
 * 
 * Copyright (C) 2020  Eugenio Pace <eugeniop@auth0.com>
 * Copyright (C) 2021  Marc Bertens-Nguyen <m.bertens@pe2mbs,nl>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Orginal idea by Eugenio from his techincal blog https://eugeniopace.org/arduino/cli/2020/10/30/A-CLI-for-Arduino-followup.html
 * 
 * Improvements for speed, size (RAM), flexability and reuseability.
 * 
 */
#include <Arduino.h>
#include <args.hpp>

// Negative results for the internal command line interface.
// Zero as standard OK result.
// Positive results for the user functions.  
enum { 	CMD_ERROR, 
		CMD_EXIT, 
		CMD_SKIP, 
		CMD_OK = 0 };

typedef int  (*handler_t)( ArgumentsInterface* args );

typedef struct 
{
    const char*   	name;
    handler_t     	handler;
    const char**  	aliases;
} command_t;

class CommandLineIntf 
{
    String      	line;
	ArgumentsIntf	args;
    command_t*  	commands;
    int         	cmdCount;
    Stream*     	console;
 
public:
    CommandLineIntf( Stream* s, command_t* c, unsigned int l );
    CommandLineIntf( command_t* c, unsigned int l );
    void displayUserPrompt();
    int run( void );
    int runOnce( void );
    int help( ArgumentsInterface* args, const char* cmd, const char* helpString );
protected:
    int parseLine( void );
    char* readLine( void );
    command_t* findCommand( char* command );
    int executeCommand( void );
    int cmdHelp( ArgumentsInterface* args );
};

typedef CommandLineIntf		CommandLineInterface;

#endif
