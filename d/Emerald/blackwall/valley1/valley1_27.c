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
    set_short("Base of a mountain.");
    set_em_long("At the foot of a mountain. To the west extend "+
		"the vast forests of Emerald while to the east, "+
		"the terrain becomes increasingly steep as it"+
		"ascends the base of the mountain. "+
		"The ground here is rocky, and does not support "+
		"the abundance of vegetation found at lower "+
		"elevations.\n");

    add_item(({"Blackwall", "Blackwall mountains", "mountains",
		 "blackwall", "blackwall mountains", "peaks", "range",
		 "Blackwall range"}),
	    "You are at the southern end of the Blackwall mountains. "+
	    "The peaks grow increasingly tall and impressive to the "+
	    "north while a lesser mountain rises up to the east.\n");

    add_item(({"ground", "earth", "down", "soil", "bedrock",
		   "black bedrock"}),
	     "The soil cover here is quite thin in places and quite "+
	     "rocky. Exposed sections of black bedrock are not "+
	     "uncommon.\n");

    add_item(({"mountain", "east mountain", "lesser peak", "peak",
		 "near mountain"}),
	     "You are at the foot of a small mountain. Much of it "+
	     "is composed of stark black cliffs. The top of the "+
	     "mountain is rounded by comparaison with most of the "+
	     "peaks in the range.\n");

    add_item(({"cliff", "black cliff", "cliffs", "black cliffs"}),
	     "Stretches of cliffs reaching hundreds of feet in height "+
	     "dominate much of the mountainside. At their base "+
	     "are massive accumulations of talus and debris.\n");

    add_item(({"talus", "debris", "accumulation of talus",
		 "accumulation of debris", "accumulation of "+
		 "talis and debris"}),
	     "At the base of most of the cliffs lie large slopes "+
	     "composed of boulders and other debris which fell "+
	     "from the mountainside over the centuries.\n");

    add_item(({"vegetation", "trees", "pines", "pine trees", 
		 "jack pines", "white pines", "grasses", "shrubs",
		 "moss"}),
	     "The landscape is dominated by various species of pine. "+
	     "Thin scraggly jack pines are the most abundant tree "+
	     "species while majestic white pines present the "+
	     "most discernable landmarks. Grasses, shrubs and moss "+
	     "also litter the ground, where it is not raw bedrock.\n");
 
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_26", "west", 0, 4);
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_37", "east", 0, 4);
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_28", "northeast", 0, 4);
}

/* Default smells for this room. */

public void
hook_smelled(string arg)
{
    if (!strlen(arg) || parse_command(arg, ({}), "[the] 'pines' / "+
	"'forest' / 'trees' / 'conifers'"))
    {
	write("The distinctive smell of pine needles permeates the air.\n");
	return;
    }   
}








