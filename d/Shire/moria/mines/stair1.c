#include "defs.h"

CONSTRUCT_ROOM
{
    set_short("Stairs of stone.");
    set_long("You are walking some wide stairs of stone. The stairs are "+
	     "hewn out of the mountain, but are amazingly straight and "+
	     "fine. They appear to have been well used, since the middle "+
	     "of the stairs are rather worn.\n");
    add_item("stairs",
	     "They are obviously dwarven made. You'd guess this was once "+
	     "the main entrance to the mighty mines of Moria.");
    DOWN("stair0");
    UP("stair2");
}
