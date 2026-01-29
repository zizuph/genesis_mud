/*
 * MAIN1.c
 * Southern Hallway
 * - Alaron January 1997
 */

#include <stdproperties.h>
#include "defs.h"

inherit BASECAVE;

void
create_cave()
{
   set_short("Southern Hallway");
   set_long("   The dark, damp caverns split here. One branch narrows "+
	    "and continues into the darkness heading north. Another "+
	    "leads west into what looks to be some kind of storage "+
	    "room. The tunnel leading south widens into the mouth "+
	    "of an opening glowing brightly in the dimly lit corridors "+
	    "of the cave. A foul odor seems to drift up from an "+
	    "ugly, slimy fungus which is attached to the wall. Fine "+
	    "trickles of water drip down from the ceiling.\n\n");

   add_exit(THIS_DIR + "fmcove", "south");
   add_exit(THIS_DIR + "storage", "west");
   add_exit(THIS_DIR + "main2", "north");

}
