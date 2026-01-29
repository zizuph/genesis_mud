/* Woodlands south of the Blackwall mountains.

   Code (c) 1999 to Damian Horton - BKA Casimir.
*/
 
#pragma strict_types
#pragma save_binary 

#include "/d/Emerald/sys/paths.h"

inherit BLACKWALL_VALLEY1_DIR + "base_valley";

void
create_valley_room()
{
    set_short("Forest, below a mountain.");
    set_em_long("Dense woodlands, near one of the southernmost mountains"+
		"of the Blackwall range. Travel here is difficult, with "+
		"lake Telberin not far to the south, thick forest to "+
		"the east, and a small mountain to the north.\n");
    
    remove_item("sky");
    add_item(({"sky", "up", "canopy", "forest canopy"}),
	     "Your view of it is obscured by the forest canopy.\n"); 

    add_item(({"ground", "earth", "down", "soil", "bedrock",
		   "black bedrock"}),
	     "The soil cover here is quite thin in places and quite "+
	     "rocky. Exposed sections of black bedrock are not "+
	     "uncommon.\n");

    add_item(({"forest", "thick forest"}),
	     "A thick forest makes travel to the east seem exceedinly "+
	     "difficult.\n");

    add_item(({"lake telberin", "lake"}),
	     "Though you cannot see the lake from here, a cool breeze "+
	     "tinged with moisture makes it way through the forest from "+
	     "the south.\n");

    add_item(({"mountain", "north mountain"}),
	     "You are on the southern side of a small mountain. Though "+
	     "its slopes are dotted by perilous cliffs, the top appears "+
	     "to be be rounded, almost flattened. There is no reasonable "+
	     "means of ascending the mountain from here.\n");

    add_item(({"cliff", "black cliff", "cliffs", "black cliffs", 
		 "bare cliffs", "perilous cliffs"}),
	     "The lengthy stretches of cliffs serve to discourage any "+
	     "attempt at climbing the mountain, at least on this side.\n");
   
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_35", "west", 0, 4);
}












