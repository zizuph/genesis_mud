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

    add_prop(ROOM_I_HIDE, 10); //little cover

    set_em_long("In a rocky valley in the southern portion of the "+
		"Blackwall mountains. Boulders and exposed bedrock "+
		"make travelling through this valley painful. "+
		"Relatively little vegetation has found an appropriate "+
		"foothold amongst the black rock. One can climb "+
		"higher into the valley to the east, or descend from "+
		"it to the southwest.\n");

    remove_item("sky");
    add_item(({"sky"}),
	     "Much of the sky is obscured by the mountains which tower "+
	     "above either side of the valley. " + WEATHER_DESC_SKY + "\n");

    add_item(({"plants", "vegetation", "grasses", "moss", "bushes",
		   "places", "dark places", "darkest places",
		   "moist places", "moistest places",
		   "darkest and moistest places", "foothold", "footholds"}),
	     "Some bushes have managed to find a foothold between "+
	     "the black boulders, while grasses grow wherever they "+
	     "may. Moss grows in the darkest and moisted places.\n");

    add_item(({"rocks", "rock", "boulders"}),
	     "The mountains are made of a coal-black basalt.\n");
    
    add_item(({"mountains", "blackwall mountains", "cliffs", "black cliffs",
		 "jagged black cliffs", "jagged cliffs", "mountain",
		 "southerly mountain"}),
	"Mountains rise on either side of the valley. Jagged black cliffs "+
	"jut hundreds of metres skyward on the northern side of the valley. "+
	"Similiar cliffs mar the face of the southerly mountain as well, "+
	"though it is not nearly as imposing in height.\n");

    add_cmd_item("cliff", "climb",
		 "Climbing the cliffs would be dangerous, and it does not "+
		 "appear as if you will get anywhere by so doing.\n");
      
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_14", "northeast", 0, 4);
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_12", "west", 0, 3);
}

/* This sterile area has no particular smell to it, therefor the
   default valley function is masked with a blank one. */

public void
hook_smelled(string arg)
{
}



