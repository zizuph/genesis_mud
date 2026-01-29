#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("southern");
	
	add_exit("sf13", "north");
	add_exit("sf6", "west");
	add_exit("sf14", "northeast");
	add_exit("sf12", "northwest");
	add_exit("sf2", "southwest");
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}