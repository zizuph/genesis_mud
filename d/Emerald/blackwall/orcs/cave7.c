/* Hallowed orc cavern.

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
    set_short("Eastern side of a large cavern");
    set_em_long("Eastern side of a large cavern. The gentle sound of "+
	     "running water reaches your ear, emanating from the darkness "+
	     "to the west. The cavern extends freely in that and the "+
	     "southerly directions, while you may enter an isolated "+
	     "section of the cavern by heading north.\n");
    
     add_item(({"sound", "sound of running water", "sound of water",
		 "sound of water", "gentle sound of water",
		 "gentle sound of running water"}),
	     "The sound of running water echoes throughout the cavern. You "+
	     "can guess that some sort of stream or river traverses the "+
	     "cavern to the west.\n");

     add_item(({"secluded sction"}),
	      "An isolated corner of the cavern lies to the north of here. "+
	      "You cannot make out any details from this distance.\n");

    add_exit(BLACKWALL_DIR + "orcs/cave3", "north");
    add_exit(BLACKWALL_DIR + "orcs/cave6", "west", safeguard_shrine);
    add_exit(BLACKWALL_DIR + "orcs/cave10", "soutwest");
    add_exit(BLACKWALL_DIR + "orcs/cave11", "south");
}


                 






