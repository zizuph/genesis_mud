#include "defs.h"

CONSTRUCT_ROOM
{
    set_short("North end of fissure");
    set_long(
	"The north end of the fissure. The fissure leads even further into the "+
	"north, but it gets so narrow that you can not follow it. The only "+
	"direction out of here is back in the south.\n");
    add_item("fissure",
	"It is a natural fissure, and you could follow to the south, "+
	"but not further north as it gets too narrow for you.");
    add_item("floor",
	"The floor is sloping steeply, and it is hard to keep your balance here.");
    add_item(({"wall","walls","ceiling"}),
	"The fissure seems natural, though you can't seem to find any precious "+
	"metals here.");
    SOUTH("narrfiss");
}
