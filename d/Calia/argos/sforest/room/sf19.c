#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("central");
	
	add_exit("sf12", "south");
	add_exit("sf20", "east");	
	add_exit("sf29", "northeast");
	add_exit("sf13","southeast");	
	add_exit("sf11", "southwest");
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}