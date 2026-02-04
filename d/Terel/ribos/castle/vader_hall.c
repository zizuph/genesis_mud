/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * vader_hall.c
 *
 * Vader
 * Recoded by Sorgum 950712
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit STDROOM;

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("dank hallway");

    set_long("The dark, slimy stone blocks that make up the " +
	     "walls of this dark, slimy hallway give off a " +
	     "strange light, as if the mold, mildew and " +
	     "fungus that clings to every surface here had " +
	     "some kind of magical property.  It does seem to " +
	     "give off just enough light to see by.  " +
	     "To your north, you can see an even brighter " +
	     "light than what these walls give off.\n");

   add_item(({"walls", "wall", "mold", "mildew", "fungus"}), 
	    "A strange green glow, not very bright, but just " +
	    "enough to give you an idea as to the location of " +
	    "the walls, is what is given off by this wall.\n");
    
    add_item(({"light", "brighter light"}), 
	     "It seems to be emanating from a glowing orb visible " +
	     "to the north.\n");
   
    INSIDE;

    add_exit(CASTLE_DIR + "vader_ent", "north", 0);
}

