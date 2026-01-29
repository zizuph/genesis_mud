#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("northern");
	
	add_exit("sf67", "north");
	add_exit("sf58", "south");
	add_exit("sf65", "east");	
	add_exit("sf63", "west");
	add_exit("sf68", "northeast");	
	add_exit("sf66", "northwest");
	add_exit("sf59", "southeast");	
	add_exit("sf57", "southwest");
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}