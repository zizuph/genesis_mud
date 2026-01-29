#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("central");
	
	add_exit("sf39","north");	
	add_exit("sf20", "south");
	add_exit("sf30", "east");	
	add_exit("sf40", "northeast");
	add_exit("sf38","northwest");	
	add_exit("sf21","southeast");	
	add_exit("sf19", "southwest");
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}
