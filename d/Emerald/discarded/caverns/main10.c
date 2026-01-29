/*
 * MAIN10.c
 * Main Passage through the Caverns
 * - Alaron January 1997
 */

#include <stdproperties.h>
#include "defs.h"

inherit BASECAVE;

void
create_cave()
{
   set_short("North Hall");
   set_long("   This is a somewhat narrow, winding bend in a "+
	    "passageway through a network of cavern systems. You can "+
	    "see dozens of little caves branching off in all direction, "+
	    "most of which are only small enough for small animals "+
	    "to fit through. You can smell a strange, unidentifiable "+
	    "odor here. The walls have a green, slimy growth on them "+
	    "which glistens with moisture dripping from the ceiling. The "+
	    "passage continues to the northeast and southeast.\n\n");

   add_prop(ROOM_I_INSIDE, 1);

   add_item( ({"caves", "little caves", "branches"}),
	     "The little caves branching off in all directions, including "+
	     "straight up and down, are too small for anything but small "+
	     "animals to squeeze through.\n\n");

   add_exit(THIS_DIR + "main11", "northeast");
   add_exit(THIS_DIR + "main9", "southeast");

}

