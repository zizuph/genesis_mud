/*
 * MAIN11.c
 * North Hall in the caverns beneath the island.
 * - Alaron September 13, 1996
 */

#include "defs.h"
#include <stdproperties.h>

inherit BASECAVE;

void
create_cave()
{
   set_short("North Hall");
   set_long("   This section of the cavern looks almost like an enormous, "+
	    "natural hall. It spreads out into the darkness to the "+
	    "southwest and toward the dim light to the northeast. Water "+
	    "continues to drip from the ceiling and run southwest toward "+
	    "lower ground on the cave floor. The sound of water dripping "+
	    "echos throughout the cavern, drowning out all other "+
	    "noises. There are visible tracks here on the floor.\n\n");

   add_item(({"track","tracks", "visible tracks"}),
	    "The floor is largely covered by a slimy green fungus which "+
	    "has formed on the stone and been fed by the constantly "+
	    "running water and the enormous amount of moisture in the "+
	    "air. As you bend closer to the tracks you notice that the "+
	    "water smells of sea salt. The tracks are foot-sized depressions "+
	    "in the slimy green fungus.\n");

   add_item(({"fungus","slimy green fungus","green fungus",
	      "slimy fungus"}),
	    "The slimy green fungus covers the floor and walls.\n");

   add_exit(THIS_DIR + "main12", "north");
   add_exit(THIS_DIR + "2guardrm", "northeast");
   add_exit(THIS_DIR + "main10", "southwest");
   
}
