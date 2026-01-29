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
    set_river_room(); // the river flows through this room

    set_short("North end of a large cavern");
    set_em_long("North end of a large cavern. A river enters the cavern "+
	     "here, flowing out of the northern wall and continuing "+
	     "southwards along the western wall of the cavern.\n");

    add_exit(BLACKWALL_DIR + "orcs/cave1", "northeast");
    add_exit(BLACKWALL_DIR + "orcs/cave5", "east");
    add_exit(BLACKWALL_DIR + "orcs/cave9", "southeast");
    add_exit(BLACKWALL_DIR + "orcs/cave8", "south");
}

void
init()
{
    ::init();
    add_action(drink_from_river, "drink");
}
                 











