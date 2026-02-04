/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * top_wall_hall.c
 *
 * This is the base room for a room that on the top edge of the castle
 *
 * Vader
 * Recoded by Sorgum 950712
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
    set_short("Atop the castle wall");
    set_long("Atop the sturdy walls of the castle, you can see all " +
	     "of Ribos, and all of the castle as well.  In the " +
	     "event of a seizure by some invading force, the Ribos " +
	     "Knights would defend the castle from these ledges.  " +
	     "The stones here are bright, almost looking like " +
	     "marble.  The view is majestic, and the wind sifts through " +
	     "your clothes and hair as freely as ever.\n");

    add_item(({"stones"}), 
	     "These stones form the castle.  They look sort of like marble, " +
	     "but not quite.  It must take alot of care to keep the ravages " +
	     "of wind and time from destroying their beauty.\n");

   add_item(({"ribos", "castle"}), 
	    "As you look into a window far below, you think you see " +
	    "someone of the opposite sex undressing.  Shame on you!\n");
}


