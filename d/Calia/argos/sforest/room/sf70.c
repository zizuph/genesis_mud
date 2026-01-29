#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("northern");
	
	add_exit("sf72", "north");
	add_exit("sf68", "southwest");
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}