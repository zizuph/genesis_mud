#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("northern");
	
	add_exit("sf64", "south");
	add_exit("sf68", "east");	
	add_exit("sf66", "west");	
	add_exit("sf65", "southeast");	
	add_exit("sf63", "southwest");
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}

