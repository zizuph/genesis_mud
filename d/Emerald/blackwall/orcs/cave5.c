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
    set_short("Large cavern");
    set_em_long("In a large cavern. The gentle sound of running water "+
	     "reaches your ear, emanating from the darkness to the west. "+
	     "A large column of stone prevents you from heading in a "+
	     "southerly direction while the cavern wall is barely visible "+
	     "to the northwest. The cavern extends freely in all other "+
	     "directions.\n");

    add_item(({"column", "column of stone", "natural column",
		 "natural column of stone"}),
	     "A natural column of stone around which the cavern has "+
	     "formed. It blocks the path south from here.\n");

     add_item(({"sound", "sound of running water", "sound of water",
		 "sound of water", "gentle sound of water",
		 "gentle sound of running water"}),
	     "The sound of running water echoes throughout the cavern. You "+
	     "can guess that some sort of stream or river traverses the "+
	     "cavern to the west.\n");

    add_exit(BLACKWALL_DIR + "orcs/cave1", "north");
    add_exit(BLACKWALL_DIR + "orcs/cave2", "northeast");
    add_exit(BLACKWALL_DIR + "orcs/cave6", "east", safeguard_shrine);
    add_exit(BLACKWALL_DIR + "orcs/cave10", "southeast");
    add_exit(BLACKWALL_DIR + "orcs/cave9", "southwest");
    add_exit(BLACKWALL_DIR + "orcs/cave4", "west");
}


                 






