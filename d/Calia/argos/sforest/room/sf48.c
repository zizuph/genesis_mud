#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("northern");
	
	add_exit("sf52", "north");	
	add_exit("sf45", "south");	
	add_exit("sf47", "west");	
	add_exit("sf53", "northwest");
	add_exit("sf51", "northeast");	
	add_exit("sf44", "southwest");
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}
