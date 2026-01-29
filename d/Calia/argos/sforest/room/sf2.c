#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("southern");
	
	add_exit("sf6", "north");
	add_exit("sf5", "northwest");
	add_exit("sf7", "northeast");
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}
