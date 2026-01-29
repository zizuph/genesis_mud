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
    set_em_long("Eastern side of a large cavern. The caverns extends into "+
	     "darkness in a northwesterly direction. Small passegeways "+
	     "leave the cavern to the south and to the northeast.\n");

    add_item(({"passageway", "passage"}),
	     "Examine which passege, the one to the northeast, or the "+
	     "one extending south?\n");

    add_item(({"northeast passageway", "northeast passage", "extension",
		 "natural extension"}),
	     "Its more of a natural extension of the cavern than a "+
	     "true passageway. It curves gently to the north before "+
	     "extending out of view.\n");

    add_item(({"south passage", "south passageway", "corner",
		 "sharp corner", "passage extending south"}),
	     "The southern passage leads to a sharp corner from which "+
	     "it appears it would be possible travel in an westerly "+
	     "direction.\n");

    add_exit(BLACKWALL_DIR + "orcs/cave14", "north");
    add_exit(BLACKWALL_DIR + "orcs/cave15", "northeast");
    add_exit(BLACKWALL_DIR + "orcs/cave20", "south");
    add_exit(BLACKWALL_DIR + "orcs/cave13", "northwest");
}


                 






