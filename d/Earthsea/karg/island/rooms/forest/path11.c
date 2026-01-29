#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "../../std/defs.h"

inherit ISL_DIR+"/std/room";

void
create_island_room()
{
	set_short("Path in the forest");
	set_long("To the west from here you see an impenetrable wall of "+
		 "trees. The path that comes from the east, disappears into "+
		 "the darkness. You shudder at the thought of following it. "+
		 "A very light trace of smoke is in the air. There is no "+
		 "smoke without fire. And there is no fire without people. "+
		 "And that path again... it is not very natural... You "+
		 "wonder who might live here.\n\n");
	
	add_exit(FROOMS+"/path12","east");
	add_exit(FROOMS+"/path9","west");
	
	add_item(({"tree","trees","forest"}),
		"The forest here is much brighter than that to "+
		"the west. Patches of blue sky are clearly visible "+
		"through the branches.\n\n");
	
	add_item(({"ground","path","track"}),
		 "The path is well-trodden, unlike all those "+
		 "animal tracks you have seen around. There must "+
		 "be men somewhere around.\n\n");
	
}


