 /* Woodlands south of the Blackwall mountains.

   Code (c) 1999 to Damian Horton - BKA Casimir.
*/
 
#pragma strict_types
#pragma save_binary 

#include "/d/Emerald/sys/paths.h"

inherit BLACKWALL_VALLEY1_DIR + "base_valley.c";

void
create_valley_room()
{
    set_short("Slope into a gulley.");
    set_em_long("In thick forest, not far from "+
		"the Blackwall mountains. You are on a steep slope "+
		"which leads into a thickly vegetated gulley. "+
		"The slope descends into the gulley to the east, "+
		"and rises out of it to the west.\n");

    remove_item("sky");
    add_item(({"sky", "up", "canopy", "forest canopy"}),
	     "Your view of it is obscured by the forest canopy.\n"); 

    add_item("gulley",
	     "You can make out little about the gulley from here, on "+
	     "account of the thick vegetation which grows in and "+
	     "around it.\n");

    add_item(({"vegetation", "plants", "low lying plants", "ferns",
		   "mosses"}),
	     "It is particular thick around here, and is even thicker "+
	     "in the gully. Bushes and low lying plants such as "+
	     "ferns and mosses are abundant.\n");
		 
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_33", "east", 0, 5);
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_24", "west", 0, 4);
}










