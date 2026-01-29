#include "../sforest.h"
inherit SFOREST + "sforest";

void
create_room()
{
	::create_room();
	config_room("northern");
	
	add_exit("sf54", "north");	
	add_exit("sf42", "south");
	add_exit("sf50","east");	
	add_exit("sf55", "northeast");	
	
	
	add_fail("auto", "The trees are too thick to go "+
	"in that direction.\n");
}