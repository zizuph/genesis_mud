/* Room in an orc filled cavern.
   Code (c) 2000 to Damian Horton - BKA Casimir.
*/
 
#pragma strict_types
#pragma save_binary 

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Emerald/sys/paths.h"

inherit BLACKWALL_DIR + "orcs/base_cave";

void
create_cave()
{   
    set_short("Large cavern");
    set_em_long("In a large cavern. The gentle sound of running water "+
	     "reaches your ear, emanating from the darkness to the west. "+
	     "The cavern extends freely in all directions.\n");

    add_item(({"sound", "sound of running water", "sound of water",
		 "sound of water", "gentle sound of water",
		 "gentle sound of running water"}),
	     "The sound of running water echoes throughout the cavern. You "+
	     "can guess that some sort of stream or river traverses the "+
	     "cavern to the west.\n");

    add_exit(BLACKWALL_DIR + "orcs/cave5", "northwest");
    add_exit(BLACKWALL_DIR + "orcs/cave6", "north", safeguard_shrine);
    add_exit(BLACKWALL_DIR + "orcs/cave7", "northeast");
    add_exit(BLACKWALL_DIR + "orcs/cave11", "east");
    add_exit(BLACKWALL_DIR + "orcs/cave14", "southeast");
    add_exit(BLACKWALL_DIR + "orcs/cave13", "south");
    add_exit(BLACKWALL_DIR + "orcs/cave12", "southwest");
    add_exit(BLACKWALL_DIR + "orcs/cave9", "west");
}


                 






