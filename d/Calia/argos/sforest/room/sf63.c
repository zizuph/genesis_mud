#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("northern");
	
	add_exit("sf66", "north");	
	add_exit("sf57", "south");	
	add_exit("sf64", "east");
	add_exit("sf62", "west");	
	add_exit("sf67", "northeast");
	add_exit("sf58", "southeast");
	add_exit("sf56", "southwest");
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}

