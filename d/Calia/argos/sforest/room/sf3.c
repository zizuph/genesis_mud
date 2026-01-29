#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("southern");
	
	add_exit("sf8", "north");
	add_exit("sf4", "east");
	add_exit("sf9", "northeast");
	add_exit("sf1", "southeast");
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}
