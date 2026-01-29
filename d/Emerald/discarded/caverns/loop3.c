/*
 * LOOP3.c
 * Looping tunnel in the caverns.
 * - Alaron January 1997
 */

#include <stdproperties.h>
#include "defs.h"

inherit BASECAVE;

void
create_cave()
{
   set_short("Narrow, Curving Tunnel");
   set_long("   You are in a very small tunnel in the caverns. There "+
	    "is barely enough space for two people to walk alongside "+
	    "eachother here. Peering out of the darkness to the "+
	    "southwest you can see a fairly well-lit bowl-shaped "+
	    "cave which serves as an intersection for other "+
	    "tunnels. The foul odor of the wall-dwelling fungus "+
	    "fills the area.\n\n");

   add_item( ({"cave", "bowl", "bowl-shaped cave"}),
	     "The bowl-shaped cave to the southwest is fairly well-lit, "+
	     "though you can't quite make out the source of that "+
	     "illumination from here. It is large with a high ceiling "+
	     "and has at least one cave exit branching from it, though "+
	     "you suspect there are more hidden from your view.\n");

   
   add_exit(THIS_DIR + "loop2", "southeast");
   add_exit(THIS_DIR + "main6", "southwest");

}
