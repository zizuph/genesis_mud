#include "defs.h"

CONSTRUCT_ROOM
{
    set_short("West of the Shaft");
    set_long(
	"You are standing in the west of the Shaft, in the Depths "+
	"of the Mountain. Southwards there is a dark passage.\n");
    EAST("bottom");
    SOUTH("darkpass");
}
