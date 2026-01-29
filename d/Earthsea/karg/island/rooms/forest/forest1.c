#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "../../std/defs.h"

inherit ISL_DIR+"/std/room";

void
create_island_room()
{
	set_short("In the forest");
	set_long("You are in the shadowy forest, surrounded "+
		 "by mighty oaks and willows. The branches "+
		 "so thick that hardly any sunrays reach the "+
		 "ground. You are completely lost. \n\n");
	
	add_exit(FROOMS+"/@@random_forest","south");
	add_exit(FROOMS+"/@@random_forest","southeast");
	add_exit(FROOMS+"/@@random_forest","southwest");
	add_exit(FROOMS+"/@@random_forest","northeast");
	add_exit(FROOMS+"/@@random_forest","north");
	add_exit(FROOMS+"/@@random_forest","northwest");
	add_exit(FROOMS+"/@@random_forest","west");
	add_exit(FROOMS+"/@@random_forest","east");
//	add_exit(ISL_DIR+"/rooms/shore/shore5","west");
	
	add_item(({"tree","trees","oak","oaks","willow","willows"}),
		"Those trees are really ancient, gnarled branches "+
		"spread widely, thick knotty roots covered by the"+
		" undergrowth.\n\n");
	
	add_item("ground","You see a lot of trails disappearing "+
		 "into the bushes. You assume that those were "+
		 "made by animals.\n\n");
	
}

string
random_forest()
{
	if (random(100)>(5+TP->query_skill(SS_LOC_SENSE)/2))
		return "forest"+random(20);
	else
		return "path"+random(10);
}

