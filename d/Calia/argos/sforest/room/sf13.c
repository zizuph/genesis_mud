#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("southern");
	
	add_exit("sf20", "north");
	add_exit("sf7", "south");
	add_exit("sf14","east");
	add_exit("sf12","west");
	add_exit("sf21", "northeast");
	add_exit("sf19", "northwest");
	add_exit("sf6", "southwest");
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}
