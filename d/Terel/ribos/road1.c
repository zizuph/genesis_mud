/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * road1.c
 *
 * A road in Ribos
 *
 *  Modified: 3 May 2003, by Bleys
 *      - fixed a typo
 *
 */

#include "/d/Terel/include/Terel.h"
inherit RIBOS_DIR + "road_room";

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("A smooth dirt road");
    set_long("You are traveling on a dirt road, west of the town square.  " +
	     "You cannot help but notice that it is a very smooth road, " + 
	     "even though it's made from dirt.  There are several houses " + 
	     "to the north and south, but they are all boarded up and " + 
	     "unenterable.  You wonder where all the people have gone " +
	     "to.\n");
   
    add_exit(RIBOS_DIR + "square",  "east", 0);
    add_exit(RIBOS_DIR + "intsec1", "west", 0);
}

