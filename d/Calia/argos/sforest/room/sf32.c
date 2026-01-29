#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("central");
	
	add_exit("sf31", "west");	
	add_exit("sf41","northwest");	
	add_exit("sf22", "southwest");
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}

