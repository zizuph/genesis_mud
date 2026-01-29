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
    set_em_long("In a large cavern. Some kind of blue-green lichen carpets "+
	     "much of this section of the cavern. A large mound of "+
	     "rock prevents you from travelling directly south. The "+
	     "gentle sound of "+
	     "running water reaches your ear, emanating from the darkness "+
	     "to the west. The cavern extends freely in all directions.\n");

    add_item(({"lichen", "blue-green lichen", "blue lichen", "green lichen"}),
	     "Flaky strands of blue-green lichen cover much of the "+
	     "cavern floor in this area. It seems to be harmless.\n");

    add_item(({"mound", "large mound", "mound of rock", "outcrop",
		 "large mound of rock", "large outcrop", "outcrop of rock"}),
	     "A large outcrop of rock makes travel directly southwards "+
	     "impossible.\n");
	            
    //  ovewrites the default in base_cave 
    add_item(({"ground", "floor", "cavern floor", "down"}),
	     "The cavern floor has been carved out of black rock via many "+
	     "years of water action. The floor is fairly dry in this "+
	     "portion of the cavern and is covered by a"+
	     "bluish-green lichen.\n");

    add_item(({"sound", "sound of running water", "sound of water",
		 "sound of water", "gentle sound of water",
		 "gentle sound of running water"}),
	     "The sound of running water echoes throughout the cavern. You "+
	     "can guess that some sort of stream or river traverses the "+
	     "cavern to the west.\n");

    add_exit(BLACKWALL_DIR + "orcs/cave9", "northwest");
    add_exit(BLACKWALL_DIR + "orcs/cave10", "north");
    add_exit(BLACKWALL_DIR + "orcs/cave11", "northeast");
    add_exit(BLACKWALL_DIR + "orcs/cave14", "east");
    add_exit(BLACKWALL_DIR + "orcs/cave18", "southeast");
    add_exit(BLACKWALL_DIR + "orcs/cave16", "southwest");
    add_exit(BLACKWALL_DIR + "orcs/cave12", "west");
}


                 






