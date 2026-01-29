/* Room in an orc-infested cavern.

   Code (c) 2000 to Damian Horton - BKA Casimir.
*/
 
#pragma strict_types
#pragma save_binary 

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Emerald/sys/paths.h"

inherit BLACKWALL_DIR + "orcs/base_cave";
inherit "/d/Emerald/lib/search.c"; //allows for searching of add_items 

void
create_cave()
{   
    set_short("North end of a large cavern");
    set_em_long("North end of a large cavern. The cavern extends into "+
	     "darkness in a southerly direction. The gentle sound "+
	     "of running water echoes throughout the cavern. A small "+
	     "passage heads east, away from the cavern.\n");

     add_item(({"sound", "sound of running water", "sound of water",
		 "sound of water", "gentle sound of water",
		 "gentle sound of running water"}),
	     "The sound of running water echoes throughout the cavern. You "+
	     "can guess that some sort of stream or river traverses the "+
	     "cavern to the west.\n");

    add_item(({"passage", "extension", "narrow extension", "small passage",
		 "east passage"}),
	     "It is less of a passage and more a narrow extension "+
	     "of the cavern.\n");

    add_search(({"ground", "floor", "cavern floor"}),
	       BLACKWALL_DIR + "/orcs/elf_bone", 5, 10 + random(10)); 

    add_exit(BLACKWALL_DIR + "orcs/cave3", "east");
    add_exit(BLACKWALL_DIR + "orcs/cave6", "south", safeguard_shrine);
    add_exit(BLACKWALL_DIR + "orcs/cave5", "southwest");
    add_exit(BLACKWALL_DIR + "orcs/cave1", "west");
}


                 






