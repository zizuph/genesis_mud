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
    set_short("A wooded valley in the Blackwall mountains.\n");
    set_em_long("Along a small river in a wooded valley at the edge "+
		"of the Blackwall mountains. The terrain becomes "+
		"more rocky, and less vegetated as one climbs into "+
		"the mountains.\n");

    set_river_room();

    add_item("sky",
	     "You are afforded a clear view of the sky thanks to the break "+
	     "in the forest afforded by the river. " + WEATHER_DESC_SKY 
	     + "\n");
		
    add_item(({"forest", "woods", "woodlands", "trees"}),
	     "The forest is relatively thin along the river, with an abundance "+
	     "of bushes growing upon its banks.\n");

    add_item(({"terrain", "transitional zone"}),
	"You are in a transitional zone between the forested lowlands and "+
	"and the rocky mountains.\n");

    add_item(({"river", "water"}),
	     "A swift-flowing river about 20 feet across. The river is deep and "+
	     "clear.\n");
    
    add_item(({"blackwall mountains", "mountains", "mountain", "two mountains",
		 "peak", "peaks", "stark black cliffs", "black cliffs",
		 "stark cliffs", "cliffs", "face", "rocky mountains"}),
	     "Two mountains loom directly to your west, one on either side "+
	     "of the river valley. The northern most one is the taller of the "+
	     "two, its jagged peak jutting skyward as if to lacerate the "+
	     "clouds. The southern one is much less impressive, standing "+
	     "not nearly so tall, and with a flattened top. Still, its face "+
	     "is marred by stark black cliffs, and it would be no easy conquest.\n");
    
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_7", "east", 0, 3);
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_5", "west", 0, 3);
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_22", "southeast", 0, 3);
}

void
init()
{
    ::init();
    add_action(drink_from_stream, "drink");
}




