/* Woodlands south of the Blackwall mountains.

   Code (c) 1999 to Damian Horton - BKA Casimir.
*/
 
#pragma strict_types
#pragma save_binary 

#include "/d/Emerald/sys/paths.h"
#include "/d/Emerald/sys/weather.h"

inherit BLACKWALL_VALLEY1_DIR + "base_valley.c";

void
create_valley_room()
{
    set_short("Clearing.");
    set_em_long("In a small clearing in the forests north of Lake "+
		"Telberin. You are surrounded on all sides by masses of "+
		"green vegetation. The clearing affords a good view of "+
		"the Blackwall mountains. It seems plausible to leave "+
		"the clearing in any of three different directions. "+
		"Directly to your east, the terrain drops off steeply into "+
		"a gulley. To the southeast, the terrain gradually "+
		"slopes upwards, towards the base of the nearest "+
		"mountain. To the west, the forest continues "+
		"indefinitely.\n");

    remove_item("sky");
    add_item(({"sky", "up"}),
	     "You get a good view of it from the clearing. "
	     + WEATHER_DESC_SKY + "\n");
		
    add_item(({"forest", "woods", "woodlands", "clearing", "bushy clearing",
		   "vegetation", "masses", "masses of vegetation",
		   "masses of green vegetation"}),
	     "You are standing in a bushy clearing, encircled by a "+
	     "thick and diverse forest. Similar forests cover "+
	     "much of Emerald.\n"); 
    
    add_item(({"mountains", "blackwall", "blackwall mountains",
		   "spires", "stark spires", "majestic spires",
		   "stark yet majestic spires", "rock", "black rock",
		   "taller mountains"}),
	     "From the clearing, you get a good view of the stark, "+
	     "yet masjestic spires of black rock which make up the "+
	     "Blackwall mountains. The taller mountains rise up to "+
	     "the north, while a lesser mountain rises directly "+
	     "to the east.\n");

    add_item(({"lesser mountain", "east mountain", "mountain",
		   "near mountain", "nearest mountain"}),
	     "Heading east will lead you towards a small, "+
	     "flat-topped mountain rimmed with savage looking cliffs.\n");

    add_item(({"cliffs", "savage-looking cliffs", "savage cliffs"}),
	     "Towering cliffs of black rock dominate the sides of "+
	     "the nearest mountain.\n");
 
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_32", "east", 0, 3);
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_23", "west", 0, 3);
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_25", "southeast", 0, 3);
}









