#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("northern");
	
	add_exit("sf76", "west");
	add_exit("sf74", "southeast");
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}