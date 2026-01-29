/*
 * MAIN2.c
 * Main Passage through the Caverns
 * - Alaron January 1997
 */

#include <stdproperties.h>
#include "defs.h"

inherit BASECAVE;

void
create_cave()
{
   set_short("South Hall");
   set_long("   You are in a long, winding passage which wanders "+
	    "through the caverns. Small tunnels and passages branch "+
	    "off in all directions. Most of the passages are too "+
	    "small for anything but a small animal to go through. The "+
	    "main passage continues to the northeast and the south. The "+
	    "walls are covered with running water, which causes "+
	    "the fungus inhabiting the walls to glisten with moisture.\n\n");

   add_item( ({"passages", "tunnels"}),
	     "Small tunnels and passages weave in and out from the "+
	     "main hall. Most of these tunnels are so small that "+
	     "only a small animal can get through.\n");

   
   add_exit(THIS_DIR + "main1", "south");
   add_exit(THIS_DIR + "main3", "northeast");

}
