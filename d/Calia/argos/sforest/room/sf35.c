#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("central");
	
	add_exit("sf36","east");
	add_exit("sf43", "northwest");
	add_exit("sf24", "southwest");	
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}