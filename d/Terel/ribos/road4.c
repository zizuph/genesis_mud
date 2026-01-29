/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * road4.c
 *
 * A road in Ribos
 *
 * Vader
 * Recoded by Sorgum 950602
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("A smooth dirt road");
    
    set_long("You are on a dirt road.  One time, it may have " +
	     "been quite smooth, but now it is covered with potholes.  One " +
	     "particular pothole is in the shape of a GIGANTIC foot!  " +
	     "You start to feel uneasy.  There is an intersection to the " +
	     "south, and an Inn to the east.\n");

    add_item(({"inn"}),
	     "It looks open, although in some state of disrepair.\n");

    add_exit(RIBOS_DIR + "road3",   "north", 0);
    add_exit(RIBOS_DIR + "intsec3", "south", 0);
    add_exit(RIBOS_DIR + "inn",     "east",  0);
}

