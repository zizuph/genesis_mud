#include "defs.h"

CONSTRUCT_ROOM
{
    set_short("South-east of Big Room");
    set_long(
	"You are standing in a corner of a big room.\n"+
	"The ceiling vaults high above you and the floor extends evenly "+
	"around you. Along the walls there are several "+
	"small platforms or ledges. The room extends in the north and the "+
	"west.\n");
    WEST("shroomsw");
    NORTHWEST("shroomnw");
    NORTH("shroomne");
    add_item(({"ceiling","corner","floor","exit"}),
	"There isn't really much else to tell really..");
    add_item(({"platforms","ledges"}),
	"I guess you would have to go there to investigate those.");
}
