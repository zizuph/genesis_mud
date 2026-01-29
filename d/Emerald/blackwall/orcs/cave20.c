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
    set_short("Underground passage");
    set_em_long("An underground passage just outside of a large cavern. You "+
	     "may enter the cavern by heading north, or by heading wast.\n");

    add_item(({"cavern", "large cavern"}),
	     "From here you can only make out that the passageway "+
	     "expands into a cavern of considerable size.\n");

    add_exit(BLACKWALL_DIR + "orcs/cave18", "north");
    add_exit(BLACKWALL_DIR + "orcs/cave19", "west");
}


                 






