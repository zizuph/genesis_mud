#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("central");
	
	add_exit("sf8", "south");
	add_exit("sf23", "northwest");
	add_exit("sf9", "southeast");
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}
