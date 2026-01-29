/*
 * MAIN4.c
 * Main Intersection in the Caverns
 * - Alaron January 1997
 */

#include <stdproperties.h>
#include "defs.h"

inherit BASECAVE;

void
create_cave()
{
   set_short("Central Hall");
   set_long("   This central intersection in the caves is large "+
	    "with a higher ceiling than the surrounding "+
	    "tunnels. To the north you notice another hall lit "+
	    "by a torch further down the tunnel. You notice that "+
	    "the walls are a little drier here, and the air is "+
	    "warmer and devoid of the foul-smelling odor of the "+
	    "wall-fungus. Off to the east you can hear the clanking "+
	    "of pots and pans accompanied by the drifting smell "+
	    "of roasting meats and smoking fowl. South and west the "+
	    "tunnel continues into the dark, wet gloom.\n\n");

   add_item( ({"caves", "tunnels", "passages"}),
	     "There are dozens of tunnels and passages branching off "+
	     "in all directions. As much as you'd like to explore them "+
	     "all, all but a few are so small only a few small animals "+
	     "might fit into them.\n");

   add_exit(THIS_DIR + "main3", "south");
   add_exit(THIS_DIR + "main5", "north");
   add_exit(THIS_DIR + "foodhall", "east");
   add_exit(THIS_DIR + "wturn1", "west");

}
