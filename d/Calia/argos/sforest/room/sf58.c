#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("northern");
	
	add_exit("sf64", "north");
	add_exit("sf53", "south");
	add_exit("sf59", "east");	
	add_exit("sf57", "west");
	add_exit("sf65", "northeast");	
	add_exit("sf63", "northwest");	
	add_exit("sf52", "southwest");
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}
