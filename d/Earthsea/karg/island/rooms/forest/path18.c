#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "../../std/defs.h"

inherit ISL_DIR+"/std/room";

void
create_island_room()
{
	set_short("Top of the hills");
	set_long("Suddenly, the path comes to the top of the hills. "+
		 "Far to the west you can see a vast forest, obscured "+
		 "by mists. When you look to the east - you notice "+
		 "some hut nearby. Much further, you can make out "+
		 "huge stronghold, silouetted against sunset-lit "+
		 "sky.\n\n");
	
	add_item(({"hut","post","guardpost"}),
		  "It is a wooden hut located just near the path. "+
		  "Considering the fortress beyond, you assume it is "+
		  "some sort of a guardpost.\n\n");
	
	add_item(({"stronghold","fortress"}),
		"It is too far to see details, but it is huge!\n\n");
	
	add_exit(FROOMS+"/path19","northeast");
	add_exit(FROOMS+"/path17","southwest");
	
}

int block()
{
 write("Stronghold is under construction yet , kargs has blocked the "+
   "way.\n");
 return 1;
}

