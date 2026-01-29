#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("northern");
	
	add_exit("sf57", "north");	
	add_exit("sf48", "south");	
	add_exit("sf53", "east");
	add_exit("sf51", "west");	
	add_exit("sf58", "northwest");
	add_exit("sf56", "northeast");	
	add_exit("sf47", "southwest");
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}
