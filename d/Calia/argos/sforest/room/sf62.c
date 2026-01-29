#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("northern");
	
	add_exit("sf56", "south");	
	add_exit("sf63", "east");
	add_exit("sf61", "west");	
	add_exit("sf66", "northeast");
	add_exit("sf57", "southeast");
	add_exit("sf55", "southwest");
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}