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
    set_short("Woodlands, near a moutain.");
    set_em_long("Dense woodlands near one of the southernmost mountains"+
		" of the Blackwall range. The woods abound with "+
		"a multiplicity of flora and fauna.\n");

    remove_item("sky");
    add_item(({"sky", "up", "canopy", "forest canopy"}),
	     "Your view of it is obscured by the forest canopy.\n"); 

    add_item(({"mountain", "southernmost mountain"}),
	     "To the northeast, a small mountain rises. Much of its "+
	     "upper reaches are composed of black cliffs, though "+
	     "the top of the mountain is gently rounded.\n");

    add_item(({"cliff", "black cliff", "cliffs", "black cliffs"}),
	     "Stretches of hundred or more metre tall cliffs "+
	     "of black rock dominate much of the mountainside.\n");

    add_item(({"plants", "animals", "flora", "fauna", "flota and fauna"}),
	     "The forest abounds with plants and animals of many "+
	     "kinds and descriptions. Some, such "+
	     "as the bloodsucking insects which seem paticularly "+
	     "prevalent in this part of the woods are unpleasant, "+
	     "however.\n");

    add_item(({"ground", "earth", "down", "soil", "bedrock",
		   "black bedrock"}),
	     "The soil cover here is quite thin in places and quite "+
	     "rocky. Exposed sections of black bedrock are not "+
	     "uncommon.\n");

    add_item(({"insects", "bloodsucking insects"}),
	     "Mosquitoes and tiny but vicious blackflies pester you "+
	     "constantly as you journey though the woods.\n");
   
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_26", "northwest", 0, 4);
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_36", "east", 0, 5);
}









