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
inherit "/d/Emerald/lib/search"; //allows the cavern floor to be searched
                                 //for items
void
create_cave()
{   
    set_short("A small passage");
    set_em_long("An isolated passage off of the east side of a large "+
	     "cavern. The passage curves in such a way that you can "+
	     "return to the cavern by heading along it either to the "+
	     "northeast or the southwest.\n");

    add_item(({"cavern", "large cavern"}),
	     "You can make out little about it from here.\n");

    add_search(({"ground", "floor", "cavern floor"}),
	       BLACKWALL_DIR + "/orcs/broken_sword", 5, 5); 
  
    add_exit(BLACKWALL_DIR + "orcs/cave11", "northwest");
    add_exit(BLACKWALL_DIR + "orcs/cave18", "southwest");
}


                 






