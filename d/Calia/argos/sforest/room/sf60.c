#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("northern");
	
	add_exit("sf54", "south");
	add_exit("sf61","east");	
	add_exit("sf55", "southeast");
	
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}