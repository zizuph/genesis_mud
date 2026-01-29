#include <macros.h>
#include <stdproperties.h>
#include "../../std/defs.h"

inherit ISL_DIR+"/std/room";

void
create_island_room()
{
	set_short("In the forest");
	set_long("You are in the shadowy forest, surrounded "+
		 "by mighty oaks and willows. The branches "+
		 "so thick that hardly any sunrays reach the "+
		 "ground. To the east the forest is even darker,"+
		 " and to the west you seem to hear the sea.\n\n");
	
	//add_exit("forest2","south");
	add_exit("forest3","north");
	add_exit("forest8","east");
	add_exit(ISL_DIR+"/rooms/shore/docks","west");
	
	add_item(({"tree","trees","oak","oaks","willow","willows"}),
		"Those trees are really ancient, gnarled branches "+
		"spread widely, thick knotty roots covered by the"+
		" undergrowth.\n\n");
	
	add_item("ground","You see a lot of trails disappearing "+
		 "into the bushes. You assume that those were "+
		 "made by animals.\n\n");
	
}
