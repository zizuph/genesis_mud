#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("southern");
	
	add_exit("sf19", "north");
	add_exit("sf6", "south");
	add_exit("sf13","east");
	add_exit("sf11","west");
	add_exit("sf20", "northeast");
	add_exit("sf7", "southeast");
	add_exit("sf5", "southwest");
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}
