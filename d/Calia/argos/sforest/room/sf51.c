#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("northern");
	
	add_exit("sf56", "north");
	add_exit("sf47", "south");	
	add_exit("sf452", "east");
	add_exit("sf50", "west");	
	add_exit("sf57", "northeast");
	add_exit("sf55", "northwest");
	add_exit("sf48", "southeast");
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}
