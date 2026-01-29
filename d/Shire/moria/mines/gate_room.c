#include "defs.h"

CONSTRUCT_ROOM
{
    set_short("The gate room of Durin's Doors");
    set_long("You have entered a rather dark room which obviously must have "+
	     "been the gate room of Durin's Doors. It looks like the dwarves "+
	     "had it rather sparse here, as there are no signs of elaborate "+
	     "architecture here. It is what it is. A room for the Guards. " +
"There seems to be a trapdoor leaving downwards here.");
    
    SOUTH("stair2");
    DOWN("exit1");
}
