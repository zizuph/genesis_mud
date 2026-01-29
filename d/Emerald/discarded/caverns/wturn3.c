/*
 * WTURN3.c
 * West Turn - Caverns
 * - Alaron January 1997
 */

#include <stdproperties.h>
#include "defs.h"

inherit BASECAVE;

void
create_cave()
{
   set_short("Bend in a Tunnel Passage");
   set_long("   The tunnel here makes a sharp turn, forming a right "+
	    "angle with thepassage continuine to the north and to "+
	    "the east. The faint sound of water dripping can be heard "+
	    "echoing in either direction. The passage forms such a "+
	    "sharp, smoothed right angle that you wonder if this turn "+
	    "wasn't chiseled out of the cave by people rather than "+
	    "forming naturally.\n\n");

   add_exit(THIS_DIR + "wturn4", "north");
   add_exit(THIS_DIR + "wturn2", "east");

}
