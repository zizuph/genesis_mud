#include "defs.h"
#include "/sys/terrain.h"

CONSTRUCT_ROOM
{
    set_short("Trolls dungeon");
 
    set_long(
	"This is the dungeon of the Trolls.\n"+
	"There is a closed door to the west, and a small hole "+
	"in the floor leading to another room.\n");
    add_item("door",
	"It is obviosly barred and locked from the outside, and "+
	"you couldn't possible get out that way.");
    add_item(({"hole","floor"}),
	"There is a hole in the floor here, leading to another room.");
    add_item(({"wall","walls","dungeon"}),
	"It seems like the dwarves made this dungeon quite safe for "+
	"their prisoners. The walls look very solid.\n");
    DOWN("prison2");
}
