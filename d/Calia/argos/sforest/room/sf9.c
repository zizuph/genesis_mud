#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("southern");
	
	add_exit("sf8", "west");
	add_exit("sf4", "south");
	add_exit("sf17", "northeast");
	add_exit("sf15", "northwest");
	add_exit("sf3", "southwest");
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}
