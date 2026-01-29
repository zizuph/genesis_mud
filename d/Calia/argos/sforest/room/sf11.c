#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("southern");
	
	
	add_exit("sf5", "south");
	add_exit("sf12", "east");
	add_exit("sf17", "northwest");
	add_exit("sf19", "northeast");
	add_exit("sf6", "southeast");
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}
