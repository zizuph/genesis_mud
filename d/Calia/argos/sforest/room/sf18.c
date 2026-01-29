#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("central");
	
	add_exit("sf17","west");
	add_exit("sf28", "northeast");
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}

