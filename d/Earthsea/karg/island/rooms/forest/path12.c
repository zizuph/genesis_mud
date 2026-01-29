#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "../../std/defs.h"

inherit ISL_DIR+"/std/room";

void
create_island_room()
{
	set_short("Path in the forest");
	set_long("You follow the path that goes from west to east. "+
		 "A smell of smoke makes you somewhat uneasy. "+
		 "You think you hear some harsh voices, but can not "+
		 "see anything suspicious beyond the trees.\n\n");
	
	add_exit(FROOMS+"/path13","east");
	add_exit(FROOMS+"/path11","west");
	
	add_item(({"tree","trees","forest"}),
		"The forest here is much brighter than that to "+
		"the west. Patches of blue sky are clearly visible "+
		"through the branches.\n\n");
	
	add_item(({"ground","path","track"}),
		 "The path is well-trodden, unlike all those "+
		 "animal tracks you have seen around. There must "+
		 "be men somewhere around.\n\n");
	
}


