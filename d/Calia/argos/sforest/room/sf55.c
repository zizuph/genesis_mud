#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("northern");
	
	add_exit("sf61", "north");
	add_exit("sf50", "south");
	add_exit("sf56","east");
	add_exit("sf54", "west");
	add_exit("sf62", "northeast");
	add_exit("sf60", "northwest");
	add_exit("sf51", "southeast");
	add_exit("sf59", "southwest");
	
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}
