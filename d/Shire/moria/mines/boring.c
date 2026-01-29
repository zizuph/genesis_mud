#include "defs.h"

CONSTRUCT_ROOM {
    set_short("A big boring room");
    set_long(
	"This is a big room, though incredibly boring due to the lack "+
	"of details. There is an opened door leading north, and another "+
	"opening to the west.\n");
    EXIT("dopening","north");
    EXIT("cornerch","west");
}
