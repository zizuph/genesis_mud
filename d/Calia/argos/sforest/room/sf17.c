#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("southern");
	
	add_exit("sf26", "north");
	add_exit("sf10", "south");
	add_exit("sf18", "east");
	add_exit("sf16", "west");
	add_exit("sf9", "southwest");
	add_exit("sf11", "southeast");
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}