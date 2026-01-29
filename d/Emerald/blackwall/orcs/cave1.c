/* Room in an orc infested cavern.

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
    set_short("North end of a large cavern");
    set_em_long("North end of a large cavern. It extends into "+
	     "darkness in a southerly direction. The gentle sound "+
	     "of running water permeates the cavern.\n");

    add_item(({"sound", "sound of running water", "sound of water",
		 "sound of water", "gentle sound of water",
		 "gentle sound of running water"}),
	     "The sound of running water echoes throughout the cavern. You "+
	     "can guess that some sort of stream or river traverses the "+
	     "cavern to the southwest.\n");

    add_exit(BLACKWALL_DIR + "orcs/cave2", "east");
    add_exit(BLACKWALL_DIR + "orcs/cave6", "southeast", safeguard_shrine);
    add_exit(BLACKWALL_DIR + "orcs/cave5", "south");
    add_exit(BLACKWALL_DIR + "orcs/cave4", "southwest");
}







