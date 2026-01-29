#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("central");
	
	add_exit("sf33", "north");	
	add_exit("sf34", "northeast");
	add_exit("sf15", "southeast");
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}