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

    set_short("West side of a large cavern");
    set_em_long("West side of a large cavern. A river flows through the cavern "+
	     "from the north and flows into the southern wall here. The "+
	     "cavern seems to narrow to the south while it widens to the "+
	     "north.\n");

    add_exit(BLACKWALL_DIR + "orcs/cave12", "north");
    add_exit(BLACKWALL_DIR + "orcs/cave13", "northeast");
    add_exit(BLACKWALL_DIR + "orcs/cave17", "east");
    add_exit(BLACKWALL_DIR + "orcs/cave19", "southeast");
}

void
init()
{
    ::init();
    add_action(drink_from_river, "drink");
}
                 








