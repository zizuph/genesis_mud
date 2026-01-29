#include "defs.h"

CONSTRUCT_ROOM
{
    set_short("Narrow fissure");
    set_long(
	"You have arrived in a narrow fissure which goes north-south. A wide "+
	"passage from the east extends to the west.\n");
    add_item("fissure",
	"It is a natural fissure, and you could follow it either to the north "+
	"or the south, though probably not so very far.");
    add_item("passage",
	"The passage leads out of this fissure in the east or the west.");
    add_item("floor",
	"The floor is sloping steeply, and it is hard to keep your balance here.");
    add_item(({"wall","walls","ceiling"}),
	"The fissure seems natural, though you can't seem to find any precious "+
	"metals here.");
    WEST("easthall");
    NORTH("fiss_n");
    SOUTH("fiss_s");
    EAST("west_dep");
}
