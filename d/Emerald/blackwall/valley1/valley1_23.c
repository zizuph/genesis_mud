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
    set_short("Forest.");
    set_em_long("Immersed in the forests north of Telberin. The Blackwall "+
		"mountains lie not far to the north and to the east. There "+
		"appears to be a clearing to the immediat east.\n");

    remove_item("sky");
    add_item(({"sky", "up"}),
	     "Your view of it is frequently obscured by the forest canopy.\n");    

    add_item(({"forest", "woods", "woodlands", "trees"}),
	     "The forests of Emerald truly blossom with life. Inumerable "+
	     "species of plants and animals are to be found herein.\n");

    add_item(({"blackwall mountains", "mountains", "blackwall",
		   "peaks", "tallest peaks"}),
	     "Peering through the occasional break in the forest "+
	     "canopy, you are afforded a glimpse of the stark forms of "+
	     "Blackwall mountains as they clamber towards the heavens. "+
	     "The tallest peaks are to be found far to the north.\n");
    
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_22", "west", 0, 3);
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_24", "east", 0, 3);
}









