#include "defs.h"

CONSTRUCT_ROOM {
    set_short("You are standing under a huge gothic dome");
    set_long("You are standing under a huge gothic dome. This creates an "+
	     "aura of peace and understanding, but unfortunately a "+
	     "disgusting scent comes from the northern exit. Yack! There is "+
	     "a small hole in the west wall, but more interesting is the "+
	     "gentle stair-case descending to the east.\n");
    add_item("scent",
	     "It sure smells bad! It must be some kind of excrements from "+
	     "something.");
    add_item(({"stair-case","stairs"}),
	     "It is rather wide, and leads somewhat down.");
    add_item(({"hole","wall","west wall"}),
	     "The hole is small, but big enough for dwarves.");
    add_item("dome","It looms above you in interesting colours.");
    add_item("colours","They are in bright blue and dark red.");
    EXIT("gstairs1","east");
    EXIT("bat_cave","north");
    EXIT("dirtrock","west");
}
