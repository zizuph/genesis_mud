/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * road2.c
 *
 * A road in Ribos
 */

#include "/d/Terel/include/Terel.h"
inherit RIBOS_DIR + "road_room";

/*
 * Function name: query_moving_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_moving_object_list()
{
    return ({RIBOS_DIR + "monster/w_knight",
	     RIBOS_DIR + "monster/w_knight"});		 
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("A smooth dirt road");
    set_long("You are on a dirt road east of the square.  It " +
	     "looks as if it was once very smooth, but several holes " +
	     "and cracks have marred its surface.  You can't help but " +
	     "wonder where all the people have gone to!  It's almost " +
	     "as if they were scared of something.  You would think " +
	     "they would have little to fear here, in this well protected " +
	     "city.  There are several houses, and they too show neglect.\n");

    add_exit(RIBOS_DIR + "square",  "west", 0);
    add_exit(RIBOS_DIR + "intsec2", "east", 0);
}

