#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("northern");
	
	add_exit("sf77", "east");
	add_exit("sf75", "west");
		
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}