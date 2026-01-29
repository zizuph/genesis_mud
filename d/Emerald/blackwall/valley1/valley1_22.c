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
    set_short("In woodlands, near the Blackwall mountains.");
    set_em_long("In moderatly dense woodland, near the "+
		"Blackwall mountains. You are immersed in a sea of lush "+
		"green vegetation and assailed by a cacophony of sounds "+
		"originating from the activities of a diversity of "+ 
		"wildlife. The mountains loom to the east, while there "+
		"appears to be some sort of opening in the forest "+
		"to the northwest.\n");
    
    remove_item("sky");
    add_item(({"sky", "up", "canopy"}),
	     "Your view of it is obscured by the forest canopy.\n");

    add_item(({"wildlife", "sound", "cacophony", "birds", "mammals",
		   "small mammals", "insects", "noise", "noises",
		   "cacophony of sounds"}),
	     "Noisy critters, such as birds, small mammals and insects "+
	     "assail your ears from all corners of the forest.\n");
		
    add_item(({"forest", "woods", "woodlands", "trees", "vegetation",
		   "plants"}),
	     "The forests of Emerald truly blossom with life. Plants of "+
	     "every kind and description seem to grow in these woods.\n");

    add_item(({"blackwall mountains", "mountains", "blackwall"}),
	     "Peering through the occasional break in the forest "+
	     "canopy, you are afforded a glimpse of the stark forms of "+
	     "Blackwall mountains as they clamber towards the heavens. "+
	     "The tallest peaks are to be found far to the north.\n");
    
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_6", "northwest", 0, 3);
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_23", "east", 0, 3);
}




