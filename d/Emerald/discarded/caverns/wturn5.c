/*
 * WTURN5.c
 * Western Turn in the Caverns
 * - Alaron January 1997
 */

#include <stdproperties.h>
#include "defs.h"

inherit BASECAVE;

void
create_cave()
{
   set_short("Western Turn");
   set_long("   This is a small branch off of the main cavern "+
	    "back to the east. As you look east, you notice the "+
	    "cave open up and become wider as it merges with the "+
	    "cave there. To the south, the network of tunnels becomes "+
	    "gradually more bright. The faint sound of dripping water "+
	    "echoes throughout the caves as constant background "+
	    "noise. Little streams of water run down from the ceiling "+
	    "over the fungus-ridden walls and trickle to the floor, "+
	    "flowing downhill.\n\n");

   add_prop(ROOM_I_INSIDE, 1);

   add_item(({"tunnel","branch","caverns","tunnels"}),
	    "The tunnels to the east widen into a larger, main "+
	    "cavern, while to the south they remain narrow but "+
	    "gain a bit more light.\n");

   add_exit(THIS_DIR + "main7", "east");
   add_exit(THIS_DIR + "wturn4", "southwest");
   
}
