#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("central");
	
	add_exit("sf30", "north");
	add_exit("sf14", "south");
	add_exit("sf22", "east");	
	add_exit("sf20","west");
	add_exit("sf31", "northeast");
	add_exit("sf29", "northwest");
	add_exit("sf13", "southwest");
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}

