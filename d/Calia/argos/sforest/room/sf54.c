#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("northern");
	
	add_exit("sf60", "north");	
	add_exit("sf49", "south");
	add_exit("sf55","east");	
	add_exit("sf61", "northeast");	
	add_exit("sf50", "southeast");
	
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}