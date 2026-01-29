#include "defs.h"

CONSTRUCT_ROOM {
    set_short("There seems to be a sudden stop here.");
    set_long("There seems to be a sudden stop here. The wall to the east "+
	     "seems unfinished, as if the dwarves who made them suddenly "+
	     "were interupted in their work. A hole is dug in a corner leading down "+
	     "to a quite big room, while in another there is a similar hole "+
	     "leading upwards.\n");
    add_item(({"stop","wall","walls"}), 
	    "I don't think you can continue their work.");
    EXIT("lpass2","west");
    EXIT("terrace","up");
    EXIT("ovalroom","down");
}
