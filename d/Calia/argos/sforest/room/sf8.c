#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("southern");
	
	add_exit("sf15", "north");
	add_exit("sf9", "east");
	add_exit("sf3", "south");
	add_exit("sf4", "southeast");
	
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}
