#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("central");
	
	add_exit("sf31", "north");
	add_exit("sf21","west");
	add_exit("sf32", "northeast");
	add_exit("sf30", "northwest");
	add_exit("sf14", "southwest");
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}
