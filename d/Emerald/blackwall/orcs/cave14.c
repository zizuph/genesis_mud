/* Room in an orc filled  cavern.
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
    set_short("East side of a large cavern");
    set_em_long("On the eastern side of a large cavern. The cavern extends "+
	     "into darkness to the north, west and south. The "+
	     "gentle sound of running water reaches your ear.\n");
	            
    add_item(({"sound", "sound of running water", "sound of water",
		 "sound of water", "gentle sound of water",
		 "gentle sound of running water"}),
	     "The sound of running water echoes throughout the cavern. You "+
	     "surmise that some sort of stream or river traverses the "+
	     "cavern to the west.\n");

    add_exit(BLACKWALL_DIR + "orcs/cave11", "north");
    add_exit(BLACKWALL_DIR + "orcs/cave10", "northwest");
    add_exit(BLACKWALL_DIR + "orcs/cave18", "south");
    add_exit(BLACKWALL_DIR + "orcs/cave17", "southwest");
    add_exit(BLACKWALL_DIR + "orcs/cave13", "west");
}


                 






