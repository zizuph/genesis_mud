#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("northern");
	
	add_exit("sf55", "south");
	add_exit("sf62","east");
	add_exit("sf60", "west");	
	add_exit("sf56", "southeast");
	add_exit("sf54", "southwest");
	
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}
