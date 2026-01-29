#include "defs.h"

CONSTRUCT_ROOM
{
    set_short("You are in a hollow in the mountain");
    set_long(
	"You are in a hollow room in the mountain. A draft in the air "+
        "from the north comes through a round opening. There also is "+
	"a small passage to the south and even a narrower one to "+
	"the west.\n");
    EXIT("eelpass","west");
    EXIT("cornerch","north");
    EXIT("maritime","south");
}
