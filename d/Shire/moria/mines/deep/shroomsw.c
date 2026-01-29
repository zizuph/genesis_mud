#include "defs.h"

CONSTRUCT_ROOM
{
    set_short("South-west of Big Room");
    set_long(
	"You are standing by the south-west corner of a big room.\n"+
	"The ceiling vaults high above you and the floor extends evenly "+
	"to the north and to the east. Along the walls there are several "+
	"small platforms or ledges, and there is an exit in the wall to "+
	"the west.\n");
    NORTH("shroomnw");
    NORTHEAST("shroomne");
    EAST("shroomse");
    WEST("shnarrw");
    add_item(({"ceiling","corner","floor","exit"}),
	"There isn't really much else to tell really..");
    add_item(({"platforms","ledges"}),
	"I guess you would have to go there to investigate those.");
}
