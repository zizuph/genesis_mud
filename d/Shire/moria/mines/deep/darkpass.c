#include "defs.h"

CONSTRUCT_ROOM
{
    set_short("Dark passage");
    set_long(
	"You are in the Dark Passage.\n"+
	"The passage turns from the north to the west, while in the "+
	"south, there is an opening leading steeply down. There are "+
	"carved stair-steps in the rocks leading upwards.\n");
    NORTH("sheast");
    WEST("longnar1");
    SOUTH("shnarrw");
    UP("shgall1");
}
