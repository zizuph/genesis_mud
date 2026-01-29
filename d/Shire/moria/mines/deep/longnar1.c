#include "defs.h"

CONSTRUCT_ROOM
{
    set_short("North end of a long narrow room");
    set_long(
	"You are in the northern end of a long and narrow room.\n"+
	"In the east, there is an opening to a dark passage.\n");
    EAST("darkpass");
    SOUTH("longnar2");
}
