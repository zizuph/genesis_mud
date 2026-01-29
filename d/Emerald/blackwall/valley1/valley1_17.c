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
    set_short("In a rocky valley at the southern end of the Blackwall "+
	      "mountains.\n");
    
    set_em_long("In a rocky valley in the southern portion of the "+
		"Blackwall mountains. Much of the valley floor is "+
		"covered by boulders and exposed bedrock and thus "+
		"little vegetation grows here.\n");
 
    add_prop(ROOM_I_HIDE, 10); //little cover

    remove_item("sky");
    add_item(({"sky"}),
	     "Much of the sky is obscured by the mountains which tower "+
	     "above either side of the valley. " + WEATHER_DESC_SKY + "\n");

    add_item(({"plants", "vegetation", "bushes", "grass"}),
	     "Bushes, grass, and patches of moss can be found in the "+
	     "valley, or hanging off of the cliffs which line its "+
	     "northern face.\n");
	    	     
    add_item(({"rocks", "rock", "boulders", "bedrock",
		   "exposed bedrock"}),
	     "The mountains are made of a coal-black basalt.\n");
    
    add_item(({"mountains", "surrouding mountains", "cliffs", "northern face",
		   "mountain", "lesser mountain", "jagged cliffs",
		   "black cliffs", "jagged black cliffs"}),
	"Vast expanses of jagged black cliffs dominate the tall mountain "+
	"on the north side of the valley. A lesser mountain, though still "+
	"rugged, is to be found to the south.\n");

    add_cmd_item("cliff", "climb",
		 "Climbing the cliffs would be dangerous, and it does not "+
		 "appear as if you will get anywhere by so doing.\n");
      
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_16", "southwest", 0, 5);
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_41", "east", 0, 5);
}

/* This sterile area has no particular smell to it, therefor the
   default valley function is masked with a blank one. */

public void
hook_smelled(string arg)
{
}




