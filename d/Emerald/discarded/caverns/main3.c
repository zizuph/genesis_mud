/*
 * MAIN3.c
 * Central Hall/Passage through Caverns
 * - Alaron January 1997
 */

#include <stdproperties.h>
#include "defs.h"

inherit BASECAVE;

void
create_cave()
{
   set_short("Central Hall");
   set_long("   The tunnel here curves to the southwest and to the "+
	    "north. The loud echoing of water dripping from the "+
	    "ceiling is almost a splashing noise here. The excess "+
	    "water has left a large puddle in the middle of the "+
	    "tunnel floor here. The foul, rank odor wafting up from "+
	    "the wall-dwelling fungus is almost unbearable here, making "+
	    "your eyes water.\n\n");

   add_item(({"puddle","slime"}),
	    "The puddle is covered in a layer of thick green slime.\n");

   add_exit(THIS_DIR + "main4", "north");
   add_exit(THIS_DIR + "main2", "southwest");
}
