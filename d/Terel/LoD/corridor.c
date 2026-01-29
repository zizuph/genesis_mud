/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * corridor.c
 *
 * A generic corridor in the Legion of Darkness.  
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "legion_room";

/* add actions for the carpet */

/* add call-outs for noises. */

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("corridor in the legion quarters");
    set_long("You are standing in a corridor in the legion of darkness " +
	     "quarters below the old mansion.  The walls are draped " +
	     "with dust.  Cobwebs are everywhere.\n");

    add_item(({"floor"}), "The floor is made of wooden boards which " +
	     "have shrunk in this dry climate, leaving quite large gaps " +
	     "between the boards.  An old carpet lies on the floor.\n");

    add_item(({"wall", "walls"}), "The dusty wooden walls have not " +
	     "been touched by human hands for many years.\n");

    add_item(({"web", "webs", "cobwebs", "cobweb"}), 
	     "Just ordinary cobweb with dust all over it " +
	     "it seems that the creatures that have made the web has moved " +
	     "somewhere else. \n");
}
    
