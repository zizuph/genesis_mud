/*
 * MAIN8.c 
 * Main Passage through the Caverns
 * - Alaron January 1997
 */

#include <stdproperties.h>
#include "defs.h"

inherit BASECAVE;

void
create_cave()
{
   set_short("Main Hall - North");
   set_long("   This is another passage in the vast network of "+
	    "interlocking caves and passageways. The sound of water "+
	    "dripping and running along the ground echoes throughout "+
	    "the entire system. The northeast end of the passage widens "+
	    "as it heads around the bend, as the southern end of the "+
	    "curve begins to narrow and get darker. It seems odd that "+
	    "as soon as the light from one curve begins to run out, "+
	    "light appears around the next bend. You wonder if the "+
	    "positioning of holes and gaps and cracks allowing small "+
	    "bits of light into this cave wasn't deliberate.\n\n");


   add_prop(ROOM_I_INSIDE, 1);
   
   add_exit(THIS_DIR + "main9", "northeast");
   add_exit(THIS_DIR + "main7", "south");

}
