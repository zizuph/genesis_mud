#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("southern");
	
	add_exit("sf21", "north");
	add_exit("sf13","west");
	add_exit("sf22", "northeast");
	add_exit("sf20", "northwest");
	add_exit("sf7", "southwest");
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}
