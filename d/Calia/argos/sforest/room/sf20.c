#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("central");
	
	add_exit("sf29", "north");
	add_exit("sf13", "south");
	add_exit("sf21", "east");	
	add_exit("sf19","west");
	add_exit("sf30", "northeast");
	add_exit("sf14","southeast");	
	add_exit("sf12", "southwest");
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}
