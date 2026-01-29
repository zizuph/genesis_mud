#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("northern");
	
	add_exit("sf65", "north");
	add_exit("sf58", "west");
	add_exit("sf64", "northwest");	
	add_exit("sf53", "southwest");
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}
