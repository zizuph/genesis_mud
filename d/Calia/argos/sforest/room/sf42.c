#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("northern");
	
	add_exit("sf46", "north");	
	add_exit("sf33", "south");
	add_exit("sf34", "southeast");	
	
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}
