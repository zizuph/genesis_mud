#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("northern");
	
	add_exit("sf62", "north");
	add_exit("sf51", "south");	
	add_exit("sf57", "east");
	add_exit("sf55", "west");	
	add_exit("sf63", "northeast");
	add_exit("sf61", "northwest");
	add_exit("sf52", "southwest");
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}