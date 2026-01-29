#include "defs.h"

CONSTRUCT_ROOM {
    set_short("Squared Chamber");
    set_long("Squared Chamber. A draft of air streams from an opening in "+
	     "the east wall into another opening in the west wall. A small "+
	     "rockslide in a corner has caused a new entrance to a somewhat "+
	     "bigger room up.\n");
    add_item(({"air","draft","stream","opening","openings"}), 
	    "It seems that there are three exits, that is east, west and up.");
    add_item(({"rockslide","rock","slide"}),
	     "There are no dangers involved in climbing up there.");
    EXIT("npass1", "west");
    EXIT("stonechb", "east");
    EXIT("guestroom", "up");
}
