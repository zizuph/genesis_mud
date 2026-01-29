#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("central");
	
	add_exit("sf29", "south");
	add_exit("sf40", "east");	
	add_exit("sf38", "west");	
	add_exit("sf30","southeast");
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}
