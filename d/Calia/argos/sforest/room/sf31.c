#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("central");
	
	add_exit("sf41","north");	
	add_exit("sf22", "south");
	add_exit("sf32", "east");
	add_exit("sf30", "west");	
	add_exit("sf40","northwest");	
	add_exit("sf21", "southwest");
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}
