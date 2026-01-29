#include "defs.h"

CONSTRUCT_ROOM
{
    set_short("South end of a fissure");
    set_long(
	"The southern end of a fissure. The fissure leads even further into the "+
	"south, but it gets so narrow that you can not follow it. The only "+
	"direction out of here is back in the north.\n");
    add_item("fissure",
	"It is a natural fissure, and you could follow to the north, "+
	"but not further south as it gets too narrow for you.");
    add_item("floor",
	"The floor is sloping steeply, and it is hard to keep your balance here.");
    add_item(({"wall","walls","ceiling"}),
	"The fissure seems natural, though you can't seem to find any precious "+
	"metals here.");
    NORTH("narrfiss");
}
