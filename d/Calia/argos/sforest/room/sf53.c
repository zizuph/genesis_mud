#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("northern");
	
	add_exit("sf58", "north");
	add_exit("sf52", "west");
	add_exit("sf59", "northeast");	
	add_exit("sf57", "northwest");	
	add_exit("sf48", "southwest");
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}

