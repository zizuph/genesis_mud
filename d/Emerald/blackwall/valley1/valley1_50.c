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
    set_em_long("Within a sylvan forest. The forest is alive with life, "+
		"perhaps too alive. Small forest animals seem to stop "+
		"whatever they are doing at your approach and instead "+
		"appear to be watching your every move. Worse still, "+
		"you cannot escape the feeling that the trees, too, "+
		"are somehow aware of your presence... A small "+
		"clearing or glade lies to the south.\n");

    add_item(({"clearing", "glade", "small clearing", "small glade"}),
	     "To the south, the forest thins out and you can make "+
	     "out what appears to be some sort of wooden structure.\n");

    add_item(({"structure", "wooden structure"}),
	     "You are too far from the structure to make out any details "+
	     "but whatever it is, it blends in with the surrounding "+
	     "forest.\n");
    
    add_item(({"animals", "small animals", "snakes", "birds", "squirrels",
		 "chipmunks"}),
	     "Squirrels, chipmunks, and even birds and snakes seem to "+
	     "stare at you as you pass near them.\n");

    add_item(({"trees", "oaks", "elms", "stately oaks", "stately elms",
		 "limbs", "major branch", "major branchs"}),
	     "The trees seem to be especially large and "+
	     "healthy. Many different kinds of trees grow in the forest, "+
	     "though stately oaks and elms predominate. The trees almost "+
	     "seem alive. From time to time, you believe you catch a "+
	     "glimpse of one of their limbs moving, though there is no "+
	     "appreciable wind, nor any animals large enough to "+
	     "disturb a major branch.\n");

    remove_item("sky");
    add_item(({"sky", "up"}),
	     "Your view is frequently obscured by the forest canopy.\n");
     	     
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_49", "north", 0, 5);
    add_exit(BLACKWALL_VALLEY1_DIR+ "encrypt_outer", "south", 0, 4);
}










