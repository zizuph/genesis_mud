/*
 * MAIN6.c
 * Main Intersection of Caverns
 * - Alaron January 1997
 */

#include <stdproperties.h>
#include "defs.h"

inherit BASECAVE;

void
create_cave()
{
   set_short("Central Hall");
   set_long("   The cave forms a bowl-like shape at the intersection "+
	    "of three large tunnels. The tunnels branch off forming a "+
	    "'Y' pattern going northeast, northwest, and south. The "+
	    "tunnel leading south becomes increasingly wider as it "+
	    "continues away from the intersection. There is a large, "+
	    "tar-drenched torch here creating flickering amber "+
	    "glows all throughout the cave. The soft hiss of the "+
	    "burning tar can occasionally be heard when the noise of "+
	    "the dripping water temporarily lets up.\n\n");

   add_item(({"torch","large torch"}),
	    "The large torch is made of some kind of treated wood. It "+
	    "is enormous and resembles a tree stump rather than a "+
	    "regular torch. It is illuminating a very wide area. The "+
	    "tar-drenched wrap around the tip of the torch hisses "+
	    "softly as the flame slowly consumes it. The torch looks "+
	    "like it will last quite a bit longer. Although, you have "+
	    "to wonder about who or what maintains this torch.\n");

   add_exit(THIS_DIR + "loop3", "northeast");
   add_exit(THIS_DIR + "main5", "south");
   add_exit(THIS_DIR + "main7", "northwest");

}
