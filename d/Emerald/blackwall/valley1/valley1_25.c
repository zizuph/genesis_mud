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
    set_short("Light woods.");
    set_em_long("In light woodlands, at the base of "+
		"the Blackwall mountains. The terrain gently "+
		"slopes upwards from west to east as it "+
		"approaches a mountain.\n");
    
    remove_item("sky");
    add_item(({"sky", "up", "canopy", "forest canopy"}),
	     "Your view of it is obscured by the forest canopy.\n"); 

    add_item(({"Blackwall", "Blackwall mountains", "mountains",
		 "blackwall", "blackwall mountains", "peaks"}),
	    "Tall peaks of jagged black rock dominate the northern "+
	    "horizon while the terrain rises towards a lesser peak "+
	    "to the east.\n");

    add_item(({"mountain", "east mountain", "lesser peak", "peak"}),
	     "To the east rises a small mountain. The top of the "+
	     "mountain is somewhat flat, while considerable expanses "+
	     "of treacherous black cliff make its ascent seem "+
	     "improbable.\n");

    add_item(({"cliff", "black cliff", "cliffs", "black cliffs",
		   "treacherous cliff", "treacherous black cliff"}),
	     "You are too far from the cliffs to make out any details.\n");
 
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_24", "northwest", 0, 3);
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_26", "east", 0, 3);
}









