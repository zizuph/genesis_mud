#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("central");
	
	add_exit("sf35", "northeast");
	add_exit("sf16","southeast");
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}
