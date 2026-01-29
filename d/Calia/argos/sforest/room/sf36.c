#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("central");
	
	add_exit("sf45", "north");
	add_exit("sf26", "south");
	add_exit("sf37","east");
	add_exit("sf35", "west");
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}