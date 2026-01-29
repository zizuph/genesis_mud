#include "defs.h"

CONSTRUCT_ROOM
{
    set_short("In a niche in the Big Hall");
    set_long(
	"You are in a niche by the northern wall of the Big Hall. "+
	"The floor is very dirty here.\n");
    add_item("hall",
	"The hall is quite big, therefore it's name. It extends west and south "+
	"and the ceiling looms a hundred yards above you.");
    add_item("ceiling",
	"Looking upwards, you can see the sad remains of the once beautiful "+
	"artistery of the dwarves. Now, however, the paintings are sotted and "+
	"you can just imagine how it looked like when the Halls were bright "+
	"and the area was inhabited.");
    add_item("painting",
	"You see colours vaguely, but you can not figure out what it is in this "+
	"darkness and the sotting of the painting.");
    add_item("path",
	"The path winds steeply up towards what must be a gallery far upwards.");
    add_item(({"floor","dirt"}),
	"The floor is very dirty here. Probably due to the deserting of the "+
	"dwarves.");
    SOUTH("bighalln");
}
