#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("southern");
	
	add_exit("sf4", "north");
	add_exit("sf3", "northwest");

	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}
