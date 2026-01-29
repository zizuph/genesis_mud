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
		"blackwall mountains. Water cascades down the rocky "+
		"face of the northern side of the valley, coalescing into "+
		"a sizeable stream upon reaching the valley floor. "+
		"The stream flows westward, out of the "+
		"mountains. Boulders and expanses of exposed bedrock "+
		"leave little space for vegetation on the valley "+
		"floor. The valley steadily climbs to the northeast.\n");

    add_prop(ROOM_I_HIDE, 10); //little cover 

    set_river_room();

    remove_item("sky");
    add_item(({"sky"}),
	     "Much of the sky is obscured by the mountains which tower "+
	     "above either side of the valley. " + WEATHER_DESC_SKY + "\n");

    add_item(({"plants", "vegetation", "grasses", "moss", "bushes",
		   "black boulnders", "boulders"}),
	     "Some bushes have managed to find a foothold between "+
	     "the black boulders, while grasses grow wherever they "+
	     "may. In the damp recesses along the stream, patches of a "+
	     "deep green moss can be found.\n");

      add_item(({"water", "stream", "cascade", "sizeable stream"}),
	     "Crystalline flows of water bounce down the basaltic cliffs "+
	     "of the northern side of the valley. The water pools on the "+
	     "valley floor, forming a clear stream of icy cold water.\n");
 
    add_item(({"rocks", "rock"}),
	     "The mountains are made of a coal-black basalt.\n");
    
    add_item(({"mountains", "blackwall mountains", "cliff", "cliffs"}),
	"Mountains rise on either side of the valley. Jagged black cliffs "+
	"jut hundreds of metres skyward on the northern side of the valley. "+
	"Similiar cliffs mar the face of the southerly mountain as well, "+
	"though it is not nearly as imposing in height.\n");

    add_cmd_item("cliff", "climb",
		 "Climbing the cliffs would be dangerous, and it does not "+
		 "appear as if you will get anywhere by so doing.\n");
      
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_13", "northeast", 0, 4);
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_11", "west", 0, 3);
}

/* This sterile area has no particular smell to it, therefor the
   default valley function is masked with a blank one. */

public void
hook_smelled(string arg)
{
}

void
init()
{
    ::init();
    add_action(drink_from_stream, "drink");
}




