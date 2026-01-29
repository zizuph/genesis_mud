#include "defs.h"

CONSTRUCT_ROOM
{
    set_short("By a small hole");
    set_long(
	"You stand by a small hole in the ground. In the north "+
	"you can see a large slab of stone.\n");
    add_item("slab", "Perhaps go there?");
    add_item("hole", "You could descend into it.");
    NORTH("stneslab");
    DOWN("inhole");
}
