#include "defs.h"

CONSTRUCT_ROOM
{
    set_short("Western Department");
    set_long(
	"This is the Western Department. In the east there is a round "+
	"hole, and in the west a wide passage.\n");
    add_item("hole", "It leads east.");
    add_item("passage", "The wide passage leads west.");
    WEST("narrfiss");
    EAST("lowroom");
}
