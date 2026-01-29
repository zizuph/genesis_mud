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
    set_short("Large cavern");
    set_em_long("In a large cavern. The cavern doesn't seem to extend very "+
	     "far to the south, but expands considerably to the north. A "+
	     "large outcrop of rock prevents your direct travel in "+
	     "that direction. The "+
	     "gentle sound of running water reaches your ear, emanating "+
	     "from the darkness to the west.\n");

    add_item(({"mound", "large mound", "mound of rock", "outcrop",
		 "large mound of rock", "large outcrop", "outcrop of rock"}),
	     "A large outcrop of rock makes travel directly northwards "+
	     "impossible.\n");
	            
    add_item(({"sound", "sound of running water", "sound of water",
		 "sound of water", "gentle sound of water",
		 "gentle sound of running water"}),
	     "The sound of running water echoes throughout the cavern. You "+
	     "can guess that some sort of stream or river traverses the "+
	     "cavern to the west.\n");

    add_exit(BLACKWALL_DIR + "orcs/cave12", "northwest");
    add_exit(BLACKWALL_DIR + "orcs/cave14", "northeast");
    add_exit(BLACKWALL_DIR + "orcs/cave19", "south");
    add_exit(BLACKWALL_DIR + "orcs/cave16", "west");
}


                 






