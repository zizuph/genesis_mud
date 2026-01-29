/* A valley in the southern Blackwall mountains.
   Code (c) 1999 to Damian Horton - BKA Casimir.
*/
 
#pragma strict_types
#pragma save_binary 

#include "/d/Emerald/sys/paths.h"
#include <stdproperties.h>
#include "/d/Emerald/sys/weather.h"

inherit BLACKWALL_VALLEY1_DIR + "/base_valley.c";

void
create_valley_room()
{
    set_short("In a rocky valley at the southern end of the Blackwall "+
	      "mountains.\n");
    
    set_em_long("In a rocky valley in the southern portion of the "+
		"Blackwall mountains. Boulders and exposed bedrock line "+
		"the valley floor, allowing precious little vegetation "+
		"to grow.\n");

    add_prop(ROOM_I_HIDE, 10); //little cover

    set_highvalley_room();

    remove_item("sky");
    add_item(({"sky"}),
	     "Much of the sky is obscured by the mountains which tower "+
	     "above either side of the valley. " + WEATHER_DESC_SKY + "\n");

    add_item(({"plants", "vegetation", "bushes", "grass", "bush",
		   "scraggly bushes"}),
	     "Tufts of grass, and the occasional scraggly bush are "+
	     "all that seems to grow here. Vegetation appears to be "+
	     "more abundant higher up in the surrounding mountains.\n");
	    	     
    add_item(({"rocks", "rock", "boulders"}),
	     "The mountains are made of a coal-black basalt.\n");
    
    add_item(({"mountains", "surrounding mountains", "cliffs",
		   "lesser mountain", "rugged mountain", "south",
		   "south mountain"}),
	"Vast expanses of jagged black cliffs dominate the tall mountain "+
	"on the north side of the valley. A lesser mountain, though still "+
	"rugged, is to be found to the south.\n");

    add_cmd_item("cliff", "climb",
		 "Climbing the cliffs would be dangerous, and it does not "+
		 "appear as if you will get anywhere by so doing.\n");
      
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_17", "northeast", 0, 5);
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_14", "west", 0, 5);
}

/* This sterile area has no particular smell to it, therefor the
   default valley function is masked with a blank one. */

public void
hook_smelled(string arg)
{
}



