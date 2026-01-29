#include "defs.h"

CONSTRUCT_ROOM
{
    set_short("Low room");
    set_long(
	"You are inside a low room. The floor is scattered with boulders, "+
	"and a passage opens in the west, and another in the east.\n");
    add_item("floor", "It is scattered with boulders.");
    add_item("boulders", "Huge boulders lie scattered around here.");
    WEST("west_dep");
    EAST("depress");
}
