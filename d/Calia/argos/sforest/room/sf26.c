#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("central");
	
	add_exit("sf36", "north");	
	add_exit("sf17","south");
	add_exit("sf27", "east");	
	add_exit("sf25", "west");
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}
