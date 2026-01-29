#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("southern");
	
	add_exit("sf17", "north");
	add_exit("trail5", "south");
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}
