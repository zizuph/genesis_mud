/*
 * File         : /d/Genesis/start/hobbit/obj/grid.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 1/25/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        This module adds a concept of x-y grid for an area of rooms. The
 *        grid could then be used to orient an NPC around and limit it to
 *        a certain rectangular area. For now a random walk function is
 *        all that exits but in the future a number of missions could be
 *        added by assigning names to certain coordinate points and make a
 *        simple algorith for the NPC to find it's way to there. Usage:
 *        Just call set_size(x, y) and the set_pos(x, y) in your
 *        create_monster() function to position the NPC in the grid *and*
 *        the grid onto your rooms, assuming that the first room the NPC
 *        will be placed in will have the grid position as set above. Be
 *        aware that if the NPC wimps or is by any other means moved out
 *        of the room it will loose track of where it is.
 * 
 * TODO         :
 * - Add named coordinate points.
 * - Add fast walk to named coordinate points.
 *
 * HISTORY
 * 20000123     :
 * - Fixed bug when X movement is ok but not Y. X is now restored correctly / Seaweed
 * - Added grid_make_cmd to be able to overload it with a function that builds a 
 *   command when the walker moves around. I.e. it can now 'sneak west'. / Seaweed
 * 
 */

/* directives */
#pragma strict_types

/* inherits */

/* includes */
#include <stdproperties.h> 
#include <macros.h> 
#include "../hobbit.h"

/* defines */

/* prototypes */
void grid_move_it();              // call this function to make the NPC move
void grid_set_size(int x, int y); // set size of grid
void grid_set_pos(int x, int y);  // set position in grid
string grid_make_cmd(string str); // overloadable help function
int check_exit(string str);       // help function

/* globals */
int MaxX; // width of area in number of rooms along the west to east axis.
int MaxY; // length of area in number of rooms along the south to north axis.
int PosX; // Holds the west-east position of the NPC within the area
          // 1 = west most room of area and MaxX = east most.
int PosY; // Holds the south-north position of the NPC within the area
          // 1 = south most room of area and MaxY = north most.

/*
 * Function name: grid_set_size
 * Description  : sets the size of the area
 * Arguments    : x - the number of rooms of the area west to east
 *                y - the number of rooms of the area south to north
 */
void
grid_set_size(int x, int y)
{
    MaxX = x;
    MaxY = y;
}

/*
 * Function name: grid_set_pos
 * Description  : sets the size of the area
 * Arguments    : x - the grid X coordinate to set
 *                y - the grid Y coordinate to set
 */
void
grid_set_pos(int x, int y)
{
    PosX = x;
    PosY = y;
}

/*
 * Function name: check_exit
 * Description  : checks weather a certain exit is ok to use and updates
 *                the current position if it is
 * Arguments    : the name of the exit
 */
private int
check_exit(string str)
{
    int err;
    int oldX;
    
    oldX = PosX; // save old position in case we find an error so we can restore it.
    
    switch(str) // check east - west movement
    {
        case "east":
        case "northeast":
        case "southeast":
        {
            if (PosX >= MaxX)
            {
                err++;
            }
            else
            {
                PosX++;
            }
            break;
        }
        case "west":
        case "northwest":
        case "southwest":
        {
            if (PosX <= 1)
            {
                err++;
            }
            else
            {
                PosX--;
            }
            break;
        }
    }
    if (err == 0){
	    switch(str) // check north - south movement
	    {
	        case "north":
	        case "northeast":
	        case "northwest":
	        {
	            if (PosY >= MaxY)
	            {
	                err++;
	                PosX = oldX; // in case we approved it
	            }
	            else
	            {
	                PosY++;
	            }
	            break;
	        }
	        case "south":
	        case "southeast":
	        case "southwest":
	        {
	            if (PosY <= 1)
	            {
	                err++;
	                PosX = oldX; // in case we approved it
	            }
	            else
	            {
	                PosY--;
	            }
	            break;
	        }
	    }
	}
    return (err == 0);
}

/*
 * Function name: grid_make_cmd
 * Description  : overloadable function that enables smart command tweaking.
 *                It must return a command that should move the walker in 
 *                the direction assigned by the argument 'cmd' 
 *                I.e. 'west' -> 'sneak west'
 * Arguments    : cmd - the direction that the walker want to go
 *                y - the grid Y coordinate to set
 */
string
grid_make_cmd(string cmd)
{
  return cmd;
}

/*
 * Function name: grid_move_it
 * Description  : makes the navigator move in a random direction
 *                within the specified area or not if trying to leave.
 * Arguments    : none
 */
void
grid_move_it()
{
    int     number_of_exits;
    string *exits;
    string  exit;
    exits = environment()->query_obvious_exits();
    number_of_exits = sizeof(exits);
    if (number_of_exits)
    {
        int i;
        exit = exits[random(number_of_exits)];
        while (!check_exit(exit))
        {
            if (i <= number_of_exits)
            {
                exit = exits[random(number_of_exits)];
                i++;
            }
            else
            {
                return;
            }
        }
        command(grid_make_cmd(exit));
    }
    else // Will never happend except during wizard failures
    {
        command("say Help! I can't see any exits.");
        command("cry");
    }
}
