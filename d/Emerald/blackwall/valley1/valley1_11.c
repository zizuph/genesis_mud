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
		"Blackwall mountains. A swiftly flowing mountain stream "+
		"traverses the valley, caught between two mountains of "+
		"black rock. Little vegetation is to be found amongst "+
		"the boulders and outcrops of rock which make up the "+
		"valley floor.\n");

    set_river_room();

    remove_item("sky");
    add_item(({"sky"}),
	     "Much of the sky is obscured by the mountains which tower "+
	     "above either side of the valley. " + WEATHER_DESC_SKY + "\n");

    add_prop(ROOM_I_HIDE, 10); //little cover

    add_item(({"plants", "vegetation", "bushes", "grasses", "moss"}),
	     "Some bushes have managed to find a foothold between "+
	     "the black boulders, while grasses grow wherever they "+
	     "may. In the damp recesses along the stream, a deep "+
	     "green moss can be found.\n");

    add_item(({"river", "rapids", "water", "precipices", "rock", "stream",
		   "swift flowing stream"}),
	     "A swift flowing stream which bubbles and froths as it falls "+
	     "over short precipices and flows around protruding expanses "+
	     "of rock. The water is clear, but cold.\n");

    add_item(({"rocks", "rock", "boulders"}),
	     "The mountains are made of a coal-black basalt.\n");
    
    add_item(({"mountains", "blackwall mountains", "cliff", "cliffs",
		   "mountains of rock", "southerly mountain",
		   "northerly mountain"}),
	"Mountains rise on either side of the valley. Jagged black cliffs "+
	"jut hundreds of metres skyward on the northern side of the valley. "+
	"Similiar cliffs mar the face of the southerly mountain as well, "+
	"though it is not nearly as imposing in height.\n");

    add_cmd_item("cliff", "climb",
		 "Climbing the cliffs would be dangerous, and it does not "+
		 "appear as if you will get anywhere by so doing.\n");
      
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_12", "east", 0, 4);
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_10", "west", 0, 4);
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




