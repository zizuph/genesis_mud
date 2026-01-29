#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("northern");
	
	add_exit("sf71", "south");
	add_exit("sf75", "northeast");
		
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}