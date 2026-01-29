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
    set_em_long("In light woods, at the foot of the Blackwall "+
		"mountains. The ground underfoot is somewhat "+
		"rocky, yet vegetation still surrounds you, as "+
		"does the incessant chatter of birds, and other "+
		"wildlife. A mountain looms directly to your "+
		"east and increasingly rocky terrain lies in that "+
		"direction. By heading in a southeasterly direction, "+
		"it may be possible to skirt the mountain's southern "+
		"flank, while heading west will lead you deeper "+
		"into the lush forests of Emerald.\n");

    remove_item("sky");
    add_item(({"sky", "up", "canopy", "forest canopy"}),
	     "Your view of it is obscured by the forest canopy.\n"); 

    add_item(({"ground", "earth", "down", "soil", "bedrock",
		   "black bedrock"}),
	     "The soil cover here is quite thin in places and quite "+
	     "rocky. Exposed sections of black bedrock are not "+
	     "uncommon.\n");
 
    add_item(({"Blackwall", "Blackwall mountains", "mountains",
		 "blackwall", "blackwall mountains", "peaks"}),
	    "You are at the southern end of the Blackwall mountains. "+
	    "The peaks grow increasingly tall and impressive to the "+
	    "north while you are at the foot of a lesser mountain "+
	    "which rises up to your east.\n");

    add_item(({"forest", "forests", "lush forests", "lust forest"}),
	     "To the west, a vast sea of green forest expands as far "+
	     "as the eye can see.\n");

    add_item(({"mountain", "east mountain", "lesser peak", "peak",
		 "near mountain", "lesser mountain"}),
	     "You are near the foot of a small mountain. Much of it "+
	     "is composed of stark black cliffs. The top of the "+
	     "mountain is rounded by comparaison with most of the "+
	     "peaks in the range.\n");

    add_item(({"cliff", "black cliff", "cliffs", "black cliffs"}),
	     "Stretches of hundred or more foot tall cliffs "+
	     "dominate much of the mountainside. At their base "+
	     "lie massive accumlations of talus and debris.\n");

    add_item(({"talus", "debris", "accumulation of talus",
		 "accumulation of debris", "accumulation of "+
		 "talis and debris"}),
	     "At the base of most of the cliffs lie large slopes "+
	     "composed of boulders and other debris which fell "+
	     "from the mountainside over the centuries.\n");
 
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_25", "west", 0, 3);
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_27", "east", 0, 3);
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_35", "southeast", 0, 3);
}









