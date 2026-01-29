#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "../../std/defs.h"

inherit ISL_DIR+"/std/room";

void
create_island_room()
{
	set_short("Clearing");
	set_long("The path here starts to climb slightly towards the "+
		 "east. To the west it leads to a vast forest. All "+
		 "around there are low hills covered with dry grass "+
		 "and some bushes scattered here and there.\n\n");
	
	add_exit(FROOMS+"/path15","northeast");
	add_exit(FROOMS+"/path13","west");
	
}

