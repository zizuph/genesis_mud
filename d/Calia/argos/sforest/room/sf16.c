#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("central");
	
	add_exit("sf24", "northwest");
	add_exit("sf17","east");
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}
