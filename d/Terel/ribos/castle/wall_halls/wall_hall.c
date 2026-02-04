/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * wall_hall.c
 *
 * Vader
 * Recoded by Sorgum 950708
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
    set_short("A dark hallway");
    set_long("You are within the large, sturdy walls of the castle.  " +
	     "This dark, moist chamber is barely lighted with torches, " +
	     "too high for you to reach.  The stones that build it " +
	     "are much uglier in here than they are on the outside.  " +
	     "Your footsteps echo quite loudly here.\n");

    add_item(({"stones", "wall"}), 
	     "These stones have been darkened by mildew, moisture, and the " +
	     "smoke billowing from the torches that light the place.\n");

    add_item(({"torch", "torches"}), 
	     "You wonder why they put these so high up.  It must be a " +
	     "pain to light them.  Otherwise, they are just your plain, " +
	     "ordinary torches.\n");

    INSIDE;
}

