#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("northern");
	
	add_exit("sf51", "north");
	add_exit("sf44", "south");	
	add_exit("sf48", "east");
	add_exit("sf52", "northeast");
	add_exit("sf50", "northwest");
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}
