/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * cave_entrance,c
 *
 * Vader
 * modified by Sorgum 950707
 *
 *  Modified: 3 May 2003, by Bleys
 *      - fixed a typo
 *
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
    set_short("Cave Entrance");
    set_long("This is a small cave that was behind the strange bush.  " +
	     "There is a faint light coming from below, in addition " +
	     "to the light that comes from the south.  There is an " +
	     "ancient spiral staircase made of stone " +
	     "leading down here.  There is also a warm breeze coming " + 
	     "from below.\n");

    add_item(({"stair", "stairs", "staircase"}), "It looks as if " +
             "its seen a great deal of use over the years\n");

    add_exit(RIBOS_DIR + "stair1", "down",  0);
    add_exit(RIBOS_DIR + "path3",  "south", 0);
}
