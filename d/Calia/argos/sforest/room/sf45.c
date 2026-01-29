#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("northern");
	
	add_exit("sf48", "north");
	add_exit("sf36", "south");	
	add_exit("sf44", "west");	
	add_exit("sf47", "northeast");	
	
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}

