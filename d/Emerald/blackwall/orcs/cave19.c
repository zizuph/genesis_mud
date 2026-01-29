/* Room in the orc filled  cavern.

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
    set_short("Southern end of a large cavern");
    set_em_long("Southern end of a large cavern. The sound of running "+
	     "water echoes from the northwest. A small passage leads away "+
	     "from the cavern to the east.\n");

    add_item(({"cavern", "large cavern"}),
	     "The cavern opens up into darkness to the north.\n");

    add_item(({"passage", "small passage", "eastern passage", "east passage",
		 "east"}),
	     "The passage heads east into the darkness.\n");

    add_exit(BLACKWALL_DIR + "orcs/cave17", "north");
    add_exit(BLACKWALL_DIR + "orcs/cave20", "east");
    add_exit(BLACKWALL_DIR +  "orcs/cave16", "northwest");
}


                 






