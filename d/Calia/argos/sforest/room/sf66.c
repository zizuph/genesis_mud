#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("northern");
	
	add_exit("sf63", "south");	
	add_exit("sf67", "east");
	add_exit("sf69", "northwest");
	add_exit("sf64", "southeast");
	add_exit("sf62", "southwest");
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}
