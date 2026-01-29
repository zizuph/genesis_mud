/* A valley in the southern Blackwall mountains.
   Code (c) 1999 to Damian Horton - BKA Casimir.
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
    set_short("A stony valley in the Blackwall mountains.");
    set_em_long("In a stony valley in the southern portion of the "+
		"Blackwall mountains. Loose stones cover much of "+
		"the valley floor, allowing only a scant vegetative "+
		"cover to subsist. Mountains flank both sides of the "+
		"valley.\n");

    set_highvalley_room();
 
    add_prop(ROOM_I_HIDE, 10); //little cover

    remove_item("sky");
    add_item(({"sky"}),
	     "Much of the sky is obscured by the mountains which tower "+
	     "above either side of the valley. " + WEATHER_DESC_SKY + "\n");

    add_item(({"plants", "vegetation", "bushes", "grass", "tufts",
		 "tufts of grass", "bush", "patches", "patches of moss",
		 "cover", "scant vegetative cover", "scant cover", 
		 "vegetative cover"}),
	     "Tufts of grass, patches of moss, and the occasional bush "+
	     "can be found in the valley.\n");
	    	     
    add_item(({"rocks", "rock", "boulders", "bedrock",
		 "exposed bedrock", "black rock"}),
	     "The mountains are made of a coal-black basalt.\n");

    add_item(({"stones", "loose stones", "floor", "ground", "down"}),
	     "Stones of all shapes and sizes litter the valley floor. They "+
	     "are composed of the same black rock as the surrounding "+
	     "mountains.\n");
    
    add_item(({"mountains", "surrouding mountains", "cliffs", "northern face",
		   "mountain", "lesser mountain", "jagged cliffs",
		   "black cliffs", "jagged black cliffs", "tall mountain"}),
	"Vast expanses of jagged black cliffs dominate the tall mountain "+
	"on the north side of the valley. A lesser mountain, though still "+
	"rugged, is to be found to the south.\n");

    add_cmd_item("cliff", "climb",
		 "Climbing the cliffs would be dangerous, and it does not "+
		 "appear as if you will get anywhere by so doing.\n");
      
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_17", "west", 0, 5);
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_42", "southeast", 0, 4);
}

/* This sterile area has no particular smell to it, therefor the
   default valley function is masked with a blank one. */

public void
hook_smelled(string arg)
{
}




