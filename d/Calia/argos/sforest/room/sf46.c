#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("northern");
	
	add_exit("sf49", "north");	
	add_exit("sf43", "south");
	add_exit("sf50", "northeast");	
	
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}
