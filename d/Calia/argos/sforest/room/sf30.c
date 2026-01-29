#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("central");
	
	add_exit("sf40","north");	
	add_exit("sf21", "south");
	add_exit("sf31", "east");
	add_exit("sf29", "west");	
	add_exit("sf41", "northeast");
	add_exit("sf39","northwest");	
	add_exit("sf22","southeast");	
	add_exit("sf20", "southwest");
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}
