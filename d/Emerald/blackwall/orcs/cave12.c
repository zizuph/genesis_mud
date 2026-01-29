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
    set_em_long("West side of a large cavern. A river flows from north to "+
	     "south along the western wall. A large column of stone "+
	     "bars the way north, though it could be circumvented to the "+
	     "northwest or northeast.\n");

    add_item(({"column", "large column", "column of stone",
		 "large column of stone"}),
	     "A natural structure which serves to hold up this "+
	     "cavern's roof.\n");

    add_exit(BLACKWALL_DIR + "orcs/cave8", "northwest");
    add_exit(BLACKWALL_DIR + "orcs/cave10", "northeast");
    add_exit(BLACKWALL_DIR + "orcs/cave13", "east");
    add_exit(BLACKWALL_DIR + "orcs/cave17", "southeast");
    add_exit(BLACKWALL_DIR + "orcs/cave16", "south");
}

void
init()
{
    ::init();
    add_action(drink_from_river, "drink");
}
                 






