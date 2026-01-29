/*
 * WTURN4.c
 * fork in the caverns.
 * - Alaron January 1997
 */

#include <stdproperties.h>
#include "defs.h"

inherit BASECAVE;

void
create_cave()
{
   set_short("Forked Cavern");
   set_long("   The narrow cavern comes to an abrupt fork here. The west "+
	    "fork leads through what looks like a circular hole in the "+
	    "west wall into a chamber on the other side. The tunnel "+
	    "continues into the darkness to the northeast and south. The "+
	    "relative darkness of those tunnels is accented more by the "+
	    "fact that a torch hangs from the wall here, casting flickering "+
	    "shadows and beams of amber illumination across the "+
	    "dark, damp cavern. Occasionally, when the occasional "+
	    "breeze blows through the cavern, the torch flickers enough "+
	    "to drop a veil of shadow over the west wall, revealing "+
	    "an officious-looking room on the other side of the hole.\n\n");

   add_prop(ROOM_I_INSIDE, 1);

   add_item( ({"hole", "circular hole"}),
	     "The circular hole in the wall reveals an officious-looking "+
	     "room on the other side.\n");

   add_item( ({"room", "official room", "officious room",
		 "officious-looking room"}),
	     "You try and peer into the room, but can't make out "+
	     "anything more than vague shadows. The torch illuminating "+
	     "this room is actually making it harder for you to see through "+
	     "the hole in the cave wall.\n");

   add_item(({"torch","large torch"}),
	    "The torch is drenched in tar. The flame is low "+
	    "and there is much tar; The torch shouldn't go out anytime "+
	    "in the near future.\n");

   add_exit(THIS_DIR + "wturn5", "northeast");
   add_exit(THIS_DIR + "woffice", "west");
   add_exit(THIS_DIR + "wturn3", "south");

}
