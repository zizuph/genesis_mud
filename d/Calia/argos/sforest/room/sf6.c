#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("southern");
	
	add_exit("sf12", "north");
	add_exit("sf2", "south");
	add_exit("sf7", "east");
	add_exit("sf5", "west");
	add_exit("sf13", "northeast");
	add_exit("sf11", "northwest");
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}
