#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("northern");
	
	add_exit("sf65", "south");
	add_exit("sf67", "west");
	add_exit("sf70", "northeast");	
	add_exit("sf64", "southwest");
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}
