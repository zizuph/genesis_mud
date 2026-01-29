#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "../../std/defs.h"

inherit ISL_DIR+"/std/room";

void
create_island_room()
{
	set_short("Path through the hills");
	set_long("The path continues climbing steadily towards the "+
		 "east. To the west it leads to a vast forest. All "+
		 "around there are low hills covered with dry grass "+
		 "and some bushes scattered here and there. "+
		 "From this height you can see the sea line beyond "+
		 "the forest.\n\n");
	
	add_exit(FROOMS+"/path17","east");
	add_exit(FROOMS+"/path15","northwest");
	
}

