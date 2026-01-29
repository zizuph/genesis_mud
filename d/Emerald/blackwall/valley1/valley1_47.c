/* A valley in the southern Blackwall mountains.
   Code (c) 2000 to Damian Horton - BKA Casimir.
*/
 
#pragma strict_types
#pragma save_binary 

#include "/d/Emerald/sys/paths.h"
#include <stdproperties.h>
#include "/d/Emerald/sys/weather.h"

inherit BLACKWALL_VALLEY1_DIR + "base_valley.c";

void
create_valley_room()
{
    ::create_valley_room();

    set_short("Sylvan forest.");
    set_em_long("Within a sylvan forest. Through the occasional break in "+
		"foliage, you can make out the forms of the blackwall "+
		"mountains which rise to the northwest.\n");
    
    remove_item("sky");
    add_item(({"sky", "up"}),
	     "Your view is frequently obscured by the forest canopy.\n");
    
    add_item(({"forest", "trees", "species", "species of tree", "oaks",
		   "elms", "majestic trees", "majestic oaks",
		   "majestic elms", "foliage"}),
	     "Many different species of tree grow in the forest, with "+
	     "majestic oaks and elms being predominant.\n");
   
    add_item(({"mountains", "blackwall", "blackwall mountains", "black rock"}),
	     "You can only get the occasional glimpse of the tall mountains "+
	     "of black rock which rise, not far off, to the northwest.\n");
	    	     
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_46", "northwest", 0, 4);
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_48", "southeast", 0, 4);
}







