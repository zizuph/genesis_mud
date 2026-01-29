/*
 * MAIN9.c
 * Main Hallway of the Caverns
 * - Alaron January 1997
 */

#include <stdproperties.h>
#include "defs.h"

inherit BASECAVE;

void
create_cave()
{
   object sign;

   set_short("North Hall");
   set_long("   The passage widens here, forming a large bowl-like "+
	    "intersection of several connecting minor caves. Water "+
	    "drips from cracks and holes in the cave ceiling ,running "+
	    "down little channels formed by erosion in the cave walls. "+
	    "The soft sound of tickling water echoes through the "+
	    "hall. The sounds of intense laughter and screams of pain "+
	    "can occasionally be heard echoing through passages off to "+
	    "the east. Two of the larger connecting caves lead off "+
	    "to the northwest and southwest.\n\n");

   add_prop(ROOM_I_INSIDE, 1);

   add_item( ({"caves", "connecting caves", "minor caves"}),
	     "The minor caves connecting to this large, hollowed-out "+
	     "cavern hall lead off into darkness in many directions. "+
	     "The two largest of these minor caves lead off northwest "+
	     "and southwest.\n");

   add_exit(THIS_DIR + "main10", "northwest");
   add_exit(THIS_DIR + "main8", "southwest");
   add_exit(THIS_DIR + "1guardrm", "east");

   sign = clone_object(THIS_DIR+"obj/jail_sign");
   sign ->move(TO);
}
