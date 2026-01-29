/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * stair4.c
 *
 * Staircase to Ribos
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
    set_short("An ancient staircase");
    set_long("You are on an ancient staircase, carved from stone eons " +
	     "ago.  Geez, you think!\nAre you ever going to get to " +
	     "the bottom?  Light filters in from\na natural window " +
	     "set into the ancient stone wall\n");

    add_item(({"window"}), "Outside, you see the city.  Its actually " +
             "only 20 feet away.  There are also some birds flying " +
             "around.\n");

    add_item(({"stair", "stairs", "staircase"}),
	     "It looks as if it has seen years of use.\n");

    add_exit(RIBOS_DIR + "stair5", "down", 0);
    add_exit(RIBOS_DIR + "stair3", "up",   0, 3);
}
