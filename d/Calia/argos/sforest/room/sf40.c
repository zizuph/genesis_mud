#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("central");
	
	add_exit("sf30", "south");
	add_exit("sf41", "east");	
	add_exit("sf39", "west");	
	add_exit("sf31","southeast");	
	add_exit("sf29", "southwest");
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}
