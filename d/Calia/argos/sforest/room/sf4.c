#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("southern");
	
	add_exit("sf9", "north");	
	add_exit("sf1", "south");
	add_exit("sf3", "west");
	add_exit("sf8", "northwest");
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}