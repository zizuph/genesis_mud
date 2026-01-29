#include "defs.h"

CONSTRUCT_ROOM {

    set_short("You're walking a vast, gently sloping corridor");
    set_long("You're walking a vast, gently sloping corridor. There seems "+
	     "to be no end in either direction. Obviously, this must be "+
	     "one of the main corridors of Moria, leading downwards to the "+
	     "deeper parts of the mines.\n");
    add_item("corridor", 
	     "It is vast, but there are lots of fissures and cracks here, "+
	     "making it a hard time walking.");
    add_item(({"fisures","cracks"}),
	     "Of cource, after such a long time, without being maintained by "+
	     "dwarves the corridor has got some wounds during the decades.");
    EXIT("corr2", "west");
    EXIT("corr4", "east");
}
