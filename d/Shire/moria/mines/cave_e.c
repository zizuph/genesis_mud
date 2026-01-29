#include "defs.h"

CONSTRUCT_ROOM {
    set_short("You are in a hollow in the rocks.");
    set_long("You are in a hollow in the rocks. It is so low under here "+
	     "that you cannot stand upright. There is a small opening to "+
	     "the west.\n");
    EXIT("bat_cave","west");
}
