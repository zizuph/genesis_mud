/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * road13.c
 *
 * A road in Ribos
 *
 * Vader
 * Recoded by Sorgum 950602
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

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
    set_long("You are travelling a dirt road.  This " +
	     "road leads west to the post office, and east to an " +
	     "intersection.  There is a house to the north, but since " +
	     "the doors are boarded shut, you see no way in.\n");
   
    add_exit(RIBOS_DIR + "road12", "west", 0);
    add_exit(RIBOS_DIR + "intsec3", "east", 0);
}

