/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * intsec1.c
 *
 * An intersection in Ribos
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
    set_short("A smooth dirt intersection");
    set_long("You are at a dirt intersection.  There are " +
	     "roads heading to the south, north, and east.  To the north, " +
	     "you see the Castle of Ribos.  South, you can see the Post " + 
	     "Office of Ribos.\n");

    add_item(({"castle"}), "You can't see much detail from here, but " +
             "you can tell that it is high and regal.\n");

    add_exit(RIBOS_DIR + "road5", "north", 0);
    add_exit(RIBOS_DIR + "road1", "east",  0);
    add_exit(RIBOS_DIR + "road9", "south", 0);
}

