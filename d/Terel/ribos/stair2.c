/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * stair2.c
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
    set_long("You are on an ancient staircase, carved carefully " +
	     "into this shaft eons ago.  Light filters in through " +
	     "a small natural window in the ancient rock wall.\n");

    add_item(({"window"}),
	     "Outside you see the city below you, and several birds " +
	     "flying.\n");

    add_item(({"bird", "birds"}),
	     "They fly about gracefully.  You wish you could fly, too!\n");

    add_exit(RIBOS_DIR + "stair1", "up",   0, 3);
    add_exit(RIBOS_DIR + "stair3", "down", 0);
}
