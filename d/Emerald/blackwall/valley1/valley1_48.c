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
    
    add_item(({"forest", "animals", "life", "birds", "squirrels",
		   "snakes"}),
	     "The forest is alive with life. The chatter of birds is "+
	     "without cease, squirrels scamper through the canopy overhead "+
	     "and small snakes slither to cover as they sense your "+
	     "your approach.\n");
   
    add_item(({"mountains", "blackwall", "blackwall mountains", "black rock"}),
	     "You can only get the occasional glimpse of the tall mountains "+
	     "of black rock which rise, not far off, to the northwest.\n");
	
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_47", "northwest", 0, 5);
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_49", "southeast", 0, 5);
}







