#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("northern");
	
	add_exit("shrine", "north");
	add_exit("sf35","southeast");
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}