#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("central");
	
	add_exit("sf42", "north");	
	add_exit("sf23", "south");
	add_exit("sf34", "east");
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}
