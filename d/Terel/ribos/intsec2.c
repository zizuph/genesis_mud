/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * intsec2.c
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
	     "roads heading in all four directions.  To the north, " +
	     "you can make out the Castle.  To the south, the road " +
	     "continues.\n");

    add_item(({"castle"}), "You can't see much detail from here, but " +
             "you can tell that it is high and regal.\n");

    add_exit(RIBOS_DIR + "road6",  "north", 0);
    add_exit(RIBOS_DIR + "road10", "south", 0);
    add_exit(RIBOS_DIR + "road2",  "west",  0);
    add_exit(RIBOS_DIR + "road16", "east",  0);
}

