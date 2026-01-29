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
    set_short("Eastern side of a large cavern");
    set_em_long("Eastern side of a large cavern. The gentle sound of "+
	     "running water reaches your ear, emanating from the darkness "+
	     "to the west. The cavern extends freely in that and the "+
	     "southerly directions. A small passageway extends from the "+
	     "main cavern to the southeast.\n");

    add_item(({"passageway", "southeast passageway", "southeast passage",
		 "passage", "extension", "natural extension"}),
	     "Its more of a natural extension of the cavern than a "+
	     "true passageway. It curves gently to the south before "+
	     "extending out of view.\n");

    add_exit(BLACKWALL_DIR + "orcs/cave7", "north");
    add_exit(BLACKWALL_DIR + "orcs/cave15", "southeast");
    add_exit(BLACKWALL_DIR + "orcs/cave14", "south");
    add_exit(BLACKWALL_DIR + "orcs/cave13", "soutwest");
    add_exit(BLACKWALL_DIR + "orcs/cave10", "west");
    add_exit(BLACKWALL_DIR + "orcs/cave6", "northwest", safeguard_shrine);
}


                 






