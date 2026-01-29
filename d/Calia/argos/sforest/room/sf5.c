#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("southern");
	
	add_exit("sf11", "north");
	add_exit("sf6", "east");
	add_exit("sf12", "northeast");
	add_exit("sf2", "southeast");
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}

