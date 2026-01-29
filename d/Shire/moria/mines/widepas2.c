#include "defs.h"

CONSTRUCT_ROOM
{
    set_short("A wide passage");
    set_long(
	"You are in a wide passage which slopes gently up to the north and "+
	"down to the south. The walls are amazingly straight and dry.\n");
    add_item("passage", "It is wide.");
    add_item("walls", "The walls are amazingly straight, a clear example of "+
	"the craftsmanship of the dwarves which made these mines. The walls "+
	"are ornamented in the 'hammer & anvil'-style often used in the late "+
	"architecture of the Naugrim.");
    add_item(({"ornaments","style"}),
	"The ornaments are made by interlacing vertical patterns of hammers "+
	"and anvils, which were great tools for the dwarves in the making of "+
	"these mines.");
    add_item("floor","Hewn out of the rock, they are also amazingly straight.");
    add_item("ceiling", "The ceiling is 2 meters above the floor, and follows "+
	"the floor-slope perfectly.");
    add_item(({"slope","floor-sloope"}),
	"You would estimate the slope to be about one to seven, which by the "+
	"way is a sacred number, since the original fathers of the dwarves where "+
	"seven in numbers, and there are Seven Tribes of Dwarves.");
    NORTH("widepas1");
    SOUTH("cross");
}
