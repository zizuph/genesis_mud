/* Room in an orc-infested  cavern.
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
    set_short("Northeast corner of a large cavern");
    set_em_long("An isolated alcove off of the northeast corner of a large "+
	     "cavern. This is the juction of two separate passages which "+
	     "jut off of the main cavern for a short distance. You can "+
	     "return to the main portion of the cavern by heading west, "+
	     "or to the south.\n");

     add_item(({"cavern", "large cavern", "main cavern", "main portion",
		  "main portion of the cavern"}),
	     "You can make out little about it from here.\n");

     add_exit(BLACKWALL_DIR + "orcs/cave2", "west");
     add_exit(BLACKWALL_DIR + "orcs/cave7", "south");
}


                 






