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
    set_short("Base of a cliff.");
    set_em_long("On the lower slopes of a small mountain. An immense "+
		"span of black cliff impedes any further ascent. "+
		"The ground is treacherous, consisting principally of "+
		"loose rocks and boulders. Travel along the cliff face is "+
		"thus difficult, but would appear to be possible in a "+
		"northerly direction. You can descend "+
		"from the mountain by heading west, and head towards a "+
		"seemingly endless expanse of forests.The greater expanse "+
		"of the Blackwall mountains arises to the north.\n");
    
    add_item(({"forest", "forests"}),
	    "Dense forest extends as far as the eye can see,");

      add_item(({"ground", "earth", "down", "soil", "bedrock",
		   "black bedrock"}),
	     "The soil cover here is quite thin in places and quite "+
	     "rocky. Exposed sections of black bedrock are not "+
	     "uncommon.\n");

    add_item("mountain",
	     "You on the lower slopes of a small mountain. Its upper "+
	     "reaches are dominated by massive cliffs, making the ascent to "+
	     "its peak difficult, perhaps impossible.\n");
 
    add_item(({"cliff", "black cliff", "cliffs", "black cliffs"}),
	     "The cliff is composed of jagged black basalt. The "+
	     "sheer height of the cliff makes climbing it unthinkable.\n");

    add_item(({"boulders", "rocks", "loose rocks", "rocks and boulders",
		 "loose rocks and boulders"}),
	     "Composed of the same black basalt as the cliffs, you infer "+
	     "that they have fallen from the cliffs.\n");
	   
    add_cmd_item(({"cliff", "cliff face"}), ({"climb", "climb up",
						"climb up the"}),
       "You would never manage to climb a cliff of that height "+
       "without the aid of equipment!\n");

    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_37", "west", 0, 4);
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_39", "north", 0, 7);
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


 





