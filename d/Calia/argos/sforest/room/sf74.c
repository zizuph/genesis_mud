#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("northern");
	
	add_exit("sf72", "south");
	add_exit("sf77", "northwest");
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}