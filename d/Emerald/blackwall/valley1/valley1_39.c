/* Woodlands south of the Blackwall mountains.

   Code (c) 1999 to Damian Horton - BKA Casimir.
*/

#pragma strict_types
#pragma save_binary 

#include "/d/Emerald/sys/paths.h"
#include <stdproperties.h>

inherit BLACKWALL_VALLEY1_DIR + "base_valley.c";

void
create_valley_room()
{
    set_short("Top of a talus slope.");
    set_em_long("At the top of a talus slope, below a vast cliff. "+
		"Few trees grow between the boulders which make "+
		"up the ground under your feet, affording you an excellent "+
		"view to the north and west. The absance of trees also "+
		"facilitates gusts of strong breezes which combine with "+
		"the high elevation to make this place positively chilly by "+
		"comparaison with the forests to the west.\n");

    add_prop(ROOM_I_HIDE, 20); //little cover

    add_item(({"view", "landscape"}),
	     "You have an excellent view of the landscape to the "+
	     "west, and to the north. The mountain you are climbing "+
	     "towers above you to the east, while tree-covered ridges "+
	     "inhibit your view to the south.\n");

    add_item(({"west view", "west landscape", "western landscape"}),
	     "Spreading out to the west lies a sea of green - the "+
	     "forests of Emerald.\n");

    add_item(({"north view", "north landscape", "northern landscape",
		 "mountains", "blackwall mountains"}),
	     "The Blackwall mountains dominate your view to the north. "+
	     "The peaks seems to become increasingly tall and jagged with "+
	     "distance though the dominant mountain in the range, Mount "+
	     "Black, is not visible from your current vantage point.\n");
    
    add_item(({"forest", "forests", "sea", "sea of green",
		 "forests of emerald"}),
	     "Much of Emerald is covered in dense forest, such as that "+
	     "which extends as far as the eye can see, to the west.\n");
      
    add_item("mountain",
	     "You on the lower slopes of a small mountain. Its upper "+
	     "reaches are dominated by massive cliffs, making the ascent to "+
	     "its peak difficult, perhaps impossible.\n");
 
    add_item(({"cliff", "black cliff", "cliffs", "black cliffs",
		 "upper reaches"}),
	     "The cliff is composed of jagged black basalt. The "+
	     "sheer height of the cliff makes climbing it unthinkable.\n");

    add_item(({"boulders", "rocks", "loose rocks", "rocks and boulders",
		 "loose rocks and boulders", "talus", "talus slope",
		 "slope", "ground", "down", "debris", "pieces of debris",
		 "pieces"}),
	     "You stand at the top of tremendous pile of debris which "+
	     "fans out hundreds of metres from the face of the cliff. "+
	     "The debris is composed of progressivly larger pieces with "+
	     "distance from the cliff.\n");
	   
    add_cmd_item(({"cliff", "cliff face"}), ({"climb", "climb up",
						"climb up the"}),
       "You would never manage to climb a cliff of that height "+
       "without the aid of equipment!\n");

    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_40", "north", 0, 7);
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_38", "south", 0, 7);
}


/* This sterile area has no particular smell to it, therefor the
   default valley function is masked with a blank one. */

public void
hook_smelled(string arg)
{
}
 





